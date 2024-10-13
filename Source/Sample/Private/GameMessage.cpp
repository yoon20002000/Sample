// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMessage.h"

void UGameMessage::SetData(const TArray<uint8>& InData)
{
	if(const TScriptInterface<IProtoBufMessage> Response = GetProtoBufRes())
	{
		Response->MergeFrom(InData);
	}
}
