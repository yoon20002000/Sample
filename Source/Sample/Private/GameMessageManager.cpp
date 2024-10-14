// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMessageManager.h"
TObjectPtr<UGameMessageManager> UGameMessageManager::Instance = nullptr;
UGameMessageManager::UGameMessageManager()
{
	MessageArray.Reserve(4);
	NextMessageArray.Reserve(4);
}

TObjectPtr<UGameMessageManager> UGameMessageManager::GetInstance()
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

	for(const TObjectPtr<UGameMessage> Message : MessageArray)
	{
		bool bIsProcessed = Message->Execute();

		if (!bIsProcessed)
		{
			UE_LOG(LogTemp, Error, TEXT("return is false : %s"), *Message->GetClass()->GetName());
		}
	}

	MessageArray.Empty();
	MessageArray.Append(NextMessageArray);
	NextMessageArray.Empty();
}

void UGameMessageManager::AddMessage(const TObjectPtr<UGameMessage>& InMessage)
{
	MessageArray.Add(InMessage);
}
