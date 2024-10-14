// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketNetworkManager.h"

#include "GameMessageManager.h"
#include "ProtoBufBase.h"
#include "SocketPacketHandler.h"
USocketNetworkManager* USocketNetworkManager::Instance = nullptr;

USocketNetworkManager* USocketNetworkManager::GetInstance()
{
	if(Instance == nullptr)
	{
		Instance = NewObject<USocketNetworkManager>();
		Instance->AddToRoot();
	}
	return Instance;
}

UGameMessage* USocketNetworkManager::FindPacketMessage(const EMsgId InMsgId)
{
	UGameMessage* Message = nullptr;

	for (USocketPacketHandler* PacketHandler : PacketHandlersArray)
	{
		Message = PacketHandler->FindPacketMessage(InMsgId);
		if(Message != nullptr)
		{
			Message->SetMsgID(InMsgId);
			break;
		}
	}
	
	return Message;
}

void USocketNetworkManager::AddHandler(USocketPacketHandler* InSocketPacketHandler)
{
	PacketHandlersArray.Add(InSocketPacketHandler);
}

void USocketNetworkManager::Connect(const EServerId InServerId) const
{
	const int32 Port = GetConnectServerPortByID(InServerId);
	Connect(static_cast<int32>(InServerId), GServer_IP, Port);
}

void USocketNetworkManager::Connect(const FString& InIP, const int32 InPort) const
{
	const EServerId ServerId = GetConnectServerIdByPort(InPort);
	Connect(static_cast<int32>(ServerId), InIP, InPort);
}

void USocketNetworkManager::Connect(const int32 InServerIndex, const FString& InIP, const int32 InPort) const
{
	USocketClient* SocketClient = GetSocketClient(static_cast<EServerId>(InServerIndex));
	check(SocketClient);

	SocketClient->Connect(InIP, InPort);
}

void USocketNetworkManager::OnTick()
{
	for (USocketClient* SocketClient : SocketClientsArray)
	{
		if(SocketClient == nullptr || SocketClient->IsConnected() == false)
		{
			continue;
		}

		if(SocketClient->Dispatch() == false)
		{
			const EServerId ConnectedServerId = SocketClient->GetConnectedServerId();
			UE_LOG(LogTemp, Log,TEXT("Socket Server %s is dispatch failed!!"), *GetEnumDisplayName(ConnectedServerId).ToString());
		}

		CheckNetworkError();
	}
}

void USocketNetworkManager::CloseNetwork(EServerId InServerId, ENetworkCloseReason InNetworkCloseReason) const
{
	USocketClient* SocketClient = GetSocketClient(InServerId);
	check(SocketClient);
	SocketClient->Close(InNetworkCloseReason);
}

void USocketNetworkManager::CloseAllNetworkSockets(const ENetworkCloseReason InNetworkCloseReason)
{
	for (USocketClient* SocketClient : SocketClientsArray)
	{
		if(SocketClient)
		{
			SocketClient->Close(InNetworkCloseReason);
		}
	}
}

bool USocketNetworkManager::IsConnectedServer(const EServerId InServerId) const
{
	const USocketClient* SocketClient = GetSocketClient(InServerId);
	
	return SocketClient->IsConnected();
}

void USocketNetworkManager::SendPacket(const EServerId InServerId, UProtoBufBase* InMessage)
{
	const USocketClient* SocketClient = GetSocketClient(InServerId);

	const FString& PacketMsgId = InMessage->GetMsgId();
	const EMsgId MsgId = StringToEnum<EMsgId>(PacketMsgId);
	uint16 MsgIdBytes = static_cast<uint16>(MsgId);

	
	uint16 MessageSize = InMessage->CalculateSize() + GPacket_Header_Size;

	
	TArray<uint8> PacketBuffer;
	PacketBuffer.Reserve(MessageSize + GPacket_Header_Size);

	uint8* Pivot = PacketBuffer.GetData();
	// packet size
	// Set big endian
	// MessageSize = MessageSize << sizeof(uint16) / 2 |  MessageSize >> sizeof(uint16) / 2 ;
	PacketBuffer.Append(Pivot,NETWORK_ORDER16(MsgIdBytes));
	Pivot += GPacket_Packet_Size;
	// msg id
	// set big endian
	PacketBuffer.Append(Pivot,NETWORK_ORDER16(MessageSize));
	Pivot += GPacket_Msg_Size;
	
	
	
}

void USocketNetworkManager::SendPacketWithConnectCheck(const EServerId InServerId, UProtoBufBase* InMessage)
{
	const USocketClient* SocketClient = GetSocketClient(InServerId);
	
	if(SocketClient->IsConnected())
	{
		SendPacket(InServerId, InMessage);	
	}
	else
	{
		
	}
}

USocketNetworkManager::USocketNetworkManager()
{
}

void USocketNetworkManager::CheckNetworkError()
{
	bool bIsSomeServerClosedByError = false;
	for (USocketClient* SocketClient : SocketClientsArray)
	{
		if(SocketClient->IsConnected() == false && SocketClient->GetNetworkCloseReason() != ENetworkCloseReason::None)
		{
			bIsSomeServerClosedByError = true;
			FString ServerName =  GetEnumDisplayName(SocketClient->GetConnectedServerId()).ToString();
			FString CloseReason = GetEnumDisplayName(SocketClient->GetNetworkCloseReason()).ToString();
			ErrorMsgsArray.Add(
				FString::Format(TEXT("{0} has a score of {1}."), {ServerName, CloseReason}));
		}
	}
	if(bIsSomeServerClosedByError)
	{
		UGameMessageManager::GetInstance()->ClearAllMessages();
		
		CloseAllNetworkSockets(ENetworkCloseReason::SomeServerError);
	}
}

USocketClient* USocketNetworkManager::GetSocketClient(const EServerId InServerId) const
{
	USocketClient* SocketClient = SocketClientsArray[static_cast<int32>(InServerId)];
	check(SocketClient);
	return SocketClient;
}
