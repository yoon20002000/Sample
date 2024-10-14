// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketNetworkManager.h"
#include "GameMessageManager.h"
#include "ProtoBufBase.h"
#include "SocketClient.h"
#include "SocketPacketHandler.h"
#include "SocketPacketHandlerAuth.h"
TObjectPtr<USocketNetworkManager> USocketNetworkManager::Instance = nullptr;

TObjectPtr<USocketNetworkManager> USocketNetworkManager::GetInstance()
{
	if(Instance == nullptr)
	{
		Instance = NewObject<USocketNetworkManager>();
		Instance->AddToRoot();
	}
	return Instance;
}

TObjectPtr<UGameMessage> USocketNetworkManager::FindPacketMessage(const EMsgId InMsgId)
{
	TObjectPtr<UGameMessage> Message = nullptr;

	for (const TObjectPtr<USocketPacketHandler> PacketHandler : PacketHandlersArray)
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

void USocketNetworkManager::AddHandler(const TObjectPtr<USocketPacketHandler>& InSocketPacketHandler)
{
	PacketHandlersArray.Add(InSocketPacketHandler);
}

void USocketNetworkManager::Connect(const EServerId InServerId) const
{
	const int32 Port = GetServerPortByID(InServerId);
	Connect(static_cast<int32>(InServerId), GServer_IP, Port);
}

void USocketNetworkManager::Connect(const FString& InIP, const int32 InPort) const
{
	const EServerId ServerId = GetServerIdByPort(InPort);
	Connect(static_cast<int32>(ServerId), InIP, InPort);
}

void USocketNetworkManager::Connect(const int32 InServerIndex, const FString& InIP, const int32 InPort) const
{
	const TObjectPtr<USocketClient> SocketClient = GetSocketClient(static_cast<EServerId>(InServerIndex));
	check(SocketClient);

	SocketClient->Connect(InIP, InPort);
}

void USocketNetworkManager::OnTick()
{
	for (TObjectPtr<USocketClient> SocketClient : SocketClientsArray)
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
	const TObjectPtr<USocketClient> SocketClient = GetSocketClient(InServerId);
	check(SocketClient);
	SocketClient->Close(InNetworkCloseReason);
}

void USocketNetworkManager::CloseAllNetworkSockets(const ENetworkCloseReason InNetworkCloseReason)
{
	for (TObjectPtr<USocketClient> SocketClient : SocketClientsArray)
	{
		if(SocketClient)
		{
			SocketClient->Close(InNetworkCloseReason);
		}
	}
}

bool USocketNetworkManager::IsConnectedServer(const EServerId InServerId) const
{
	const TObjectPtr<USocketClient> SocketClient = GetSocketClient(InServerId);
	
	return SocketClient->IsConnected();
}

void USocketNetworkManager::SendPacket(const EServerId InServerId, const TObjectPtr<UProtoBufBase>& InMessage) const
{
	const TObjectPtr<USocketClient> SocketClient = GetSocketClient(InServerId);

	const FString& PacketMsgId = InMessage->GetMsgId();
	const EMsgId MsgId = StringToEnum<EMsgId>(PacketMsgId);
	uint16 MsgIdBytes = static_cast<uint16>(MsgId);
	// Set big endian
	MsgIdBytes = NETWORK_ORDER16(MsgIdBytes);
	
	uint16 TotalPacketSize = InMessage->CalculateSize() + GPacket_Header_Size;
	// set big endian
	TotalPacketSize = NETWORK_ORDER16(TotalPacketSize);
	
	TArray<uint8> PacketBuffer;
	PacketBuffer.Reserve(TotalPacketSize + GPacket_Header_Size);
	
	const TArray<uint8> TotalPacketSizeBytes = ConvertSendBytes(TotalPacketSize);
	PacketBuffer.Append(TotalPacketSizeBytes);
	
	const TArray<uint8> SendMsgIdBytes = ConvertSendBytes(MsgIdBytes);
	PacketBuffer.Append(SendMsgIdBytes);
	
	PacketBuffer.Append(InMessage->ToByteArray());

	SocketClient->SendPacket(PacketBuffer);
}

void USocketNetworkManager::SendPacketWithConnectCheck(const EServerId InServerId, const TObjectPtr<UProtoBufBase>& InMessage) const
{
	const TObjectPtr<USocketClient> SocketClient = GetSocketClient(InServerId);
	
	if(SocketClient->IsConnected())
	{
		SendPacket(InServerId, InMessage);	
	}
	else
	{
		SocketClient->SetReserveMessage(InMessage);
		Connect(InServerId);
	}
}

void USocketNetworkManager::SendPacketWithExitCheck(const EServerId InServerId, const TObjectPtr<UProtoBufBase>& InMessage) const
{
	const TObjectPtr<USocketClient> SocketClient = GetSocketClient(InServerId);
	int32 Port = GetServerPortByID(InServerId);
	if(SocketClient->IsLogined())
	{
		Async(EAsyncExecution::Thread, [this, Port](){ExitNConnect(GServer_IP,Port);});
	}
}

USocketNetworkManager::USocketNetworkManager()
{
}

void USocketNetworkManager::CheckNetworkError()
{
	bool bIsSomeServerClosedByError = false;
	for (const TObjectPtr<USocketClient> SocketClient : SocketClientsArray)
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

TObjectPtr<USocketClient> USocketNetworkManager::GetSocketClient(const EServerId InServerId) const
{
	TObjectPtr<USocketClient> SocketClient = SocketClientsArray[static_cast<int32>(InServerId)];
	check(SocketClient);
	return SocketClient;
}

void USocketNetworkManager::ExitNConnect(const FString& InIP, const int32 InPort) const
{
	// Send Logout
	// Common.SendExit();
	EServerId ServerID = GetServerIdByPort(InPort);
	
	FTimerHandle WaitDisconnectHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitDisconnectHandle, [this, ServerID, InIP, InPort, &WaitDisconnectHandle]()
		{
			const TObjectPtr<USocketClient> SocketClient = GetSocketClient(ServerID);
			if (SocketClient && !SocketClient->IsConnected())
			{		
				GetWorld()->GetTimerManager().ClearTimer(WaitDisconnectHandle);
                         	
				Connect(InIP, InPort);
			}
		}, 0.1f, true);  
}

void USocketNetworkManager::BeginDestroy()
{
	UObject::BeginDestroy();

	for (const TObjectPtr<USocketClient> SocketClient : SocketClientsArray)
	{
		if(SocketClient == nullptr)
		{
			continue;
		}
		SocketClient->Close(ENetworkCloseReason::QuitGame);
	}
}

void USocketNetworkManager::Initialize()
{
	PacketHandlerAuth = NewObject<USocketPacketHandlerAuth>();
}

TArray<uint8> USocketNetworkManager::ConvertSendBytes(const uint16 InData)
{
	TArray<uint8> PacketBuffer;
	PacketBuffer.Reserve(2);
	PacketBuffer.Add(static_cast<uint8>(InData & 0xFF));
	PacketBuffer.Add(static_cast<uint8>((InData >> 8) & 0xFF));
	return PacketBuffer;
}
