// Fill out your copyright notice in the Description page of Project Settings.


#include "SLoginReq.h"

SLoginReq::SLoginReq(const EServerId InServerId) : ServerId(InServerId)
{
}

SLoginReq::~SLoginReq()
{
}

void SLoginReq::MergeFrom(const TArray<uint8>& InData)
{
	Bytes = InData;
}

int32 SLoginReq::CalculateSize()
{
	return Bytes.Num();
}

const TArray<uint8>& SLoginReq::ToByteArray()
{
	return Bytes;
}

const FString SLoginReq::GetMsgId()
{
	return TEXT("SLoginReq");
}
