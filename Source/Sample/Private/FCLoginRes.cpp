// Fill out your copyright notice in the Description page of Project Settings.


#include "FCLoginRes.h"

FCLoginRes::FCLoginRes()
{
}

FCLoginRes::~FCLoginRes()
{
}

void FCLoginRes::MergeFrom(const TArray<uint8>& InData)
{
	Bytes = InData;
}

const FString FCLoginRes::GetMsgId()
{
	return TEXT("CLoginRes");
}

int32 FCLoginRes::CalculateSize()
{
	return Bytes.Num();
}

const TArray<uint8>& FCLoginRes::ToByteArray()
{
	return Bytes;
}
