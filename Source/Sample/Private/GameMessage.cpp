// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMessage.h"

#include "IMessage.h"

GameMessage::GameMessage()
{
}

GameMessage::~GameMessage()
{
	
}

void GameMessage::SetData(const TArray<uint8>& InData)
{
	ResMessage->MergeFrom(InData);
}
