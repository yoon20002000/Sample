// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketNetworkManager.h"

#include "GameMessageManager.h"
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

void USocketNetworkManager::Connect(const EServerId InServerId)
{
	const int32 Port = GetConnectServerPortByID(InServerId);
	Connect(static_cast<int32>(InServerId), GServer_IP, Port);
}

void USocketNetworkManager::Connect(const FString& InIP, const int32 InPort)
{
	const EServerId ServerId = GetConnectServerIdByPort(InPort);
	Connect(static_cast<int32>(ServerId), InIP, InPort);
}

void USocketNetworkManager::Connect(const int32 InServerIndex, const FString& InIP, const int32 InPort)
{
	USocketClient* SocketClient = SocketClientsArray[InServerIndex];
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

void USocketNetworkManager::CloseNetwork(EServerId InServerId, ENetworkCloseReason InNetworkCloseReason)
{
	USocketClient* SocketClient = SocketClientsArray[static_cast<int32>(InServerId)];
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
	const USocketClient* SocketClient = SocketClientsArray[static_cast<int32>(InServerId)];
	check(SocketClient);
	return SocketClient->IsConnected();
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
