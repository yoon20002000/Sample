// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketNetworkManager.h"

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

void USocketNetworkManager::AddHandler(USocketPacketHandler* SocketPacketHandler)
{
	PacketHandlersArray.Add(SocketPacketHandler);
}

USocketNetworkManager::USocketNetworkManager()
{
}
