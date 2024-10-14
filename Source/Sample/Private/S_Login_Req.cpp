// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Login_Req.h"

void US_Login_Req::MergeFrom(const TArray<uint8>& Data)
{
	Super::MergeFrom(Data);
}

const FString US_Login_Req::GetMsgId()
{
	return Super::GetMsgId();
}

int32 US_Login_Req::CalculateSize()
{
	return Super::CalculateSize();
}

const TArray<uint8>& US_Login_Req::ToByteArray()
{
	return Super::ToByteArray();
}
