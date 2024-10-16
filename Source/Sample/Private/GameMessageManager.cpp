// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMessageManager.h"
UGameMessageManager* UGameMessageManager::Instance = nullptr;
UGameMessageManager::UGameMessageManager()
{
	MessageArray.Reserve(4);
	NextMessageArray.Reserve(4);
}

UGameMessageManager* UGameMessageManager::GetInstance()
{
	if(Instance == nullptr)
	{
		Instance = NewObject<UGameMessageManager>();
		Instance->AddToRoot();
	}
	return Instance;
}

void UGameMessageManager::ClearAllMessages()
{
	MessageArray.Empty();
	NextMessageArray.Empty();
}

void UGameMessageManager::ExecuteMessage()
{
	if(MessageArray.IsEmpty())
	{
		return;
	}

	for(const TSharedPtr<GameMessage> Message : MessageArray)
	{
		bool bIsProcessed = Message->Execute();

		if (!bIsProcessed)
		{
			UE_LOG(LogTemp, Error, TEXT("return is false : %s"), *GetEnumDisplayName(Message->GetMsgID()).ToString());
		}
	}

	MessageArray.Empty();
	MessageArray.Append(NextMessageArray);
	NextMessageArray.Empty();
}

void UGameMessageManager::AddMessage(const TSharedPtr<GameMessage>& InMessage)
{
	MessageArray.Add(InMessage);
}
