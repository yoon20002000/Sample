// Fill out your copyright notice in the Description page of Project Settings.


#include "CLoginRes.h"

CLoginRes::CLoginRes()
{
}

CLoginRes::~CLoginRes()
{
}

void CLoginRes::MergeFrom(const TArray<uint8>& InData)
{
	Bytes = InData;
}

const FString CLoginRes::GetMsgId()
{
	return TEXT("CLoginRes");
}

int32 CLoginRes::CalculateSize()
{
	return Bytes.Num();
}

const TArray<uint8>& CLoginRes::ToByteArray()
{
	return Bytes;
}
