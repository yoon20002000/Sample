// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMessageManager.h"

UGameMessageManager::UGameMessageManager()
{
	MessageArray.Reserve(4);
	NextMessageArray.Reserve(4);
}

void UGameMessageManager::ClearMessages()
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

	for(const TWeakObjectPtr<UGameMessage> Message : MessageArray)
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

void UGameMessageManager::AddMessage(const TWeakObjectPtr<UGameMessage> InMessage)
{
	MessageArray.Add(InMessage);
}
