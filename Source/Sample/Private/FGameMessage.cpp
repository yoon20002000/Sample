// Fill out your copyright notice in the Description page of Project Settings.


#include "FGameMessage.h"

#include "IMessage.h"

FGameMessage::FGameMessage()
{
}

FGameMessage::~FGameMessage()
{
}

void FGameMessage::SetData(const TArray<uint8>& InData)
{
	ResMessage->MergeFrom(InData);
}
