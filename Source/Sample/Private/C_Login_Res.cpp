// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Login_Res.h"

void UC_Login_Res::MergeFrom(const TArray<uint8>& Data)
{
	// bytes convert
	Bytes = Data;
}

const FString UC_Login_Res::GetMsgId()
{
	return FString(TEXT("CLOGINRES"));
}

int32 UC_Login_Res::CalculateSize()
{
	return Super::CalculateSize();
}

const TArray<uint8>& UC_Login_Res::ToByteArray()
{
	return Super::ToByteArray();
}
