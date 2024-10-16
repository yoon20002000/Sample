// Fill out your copyright notice in the Description page of Project Settings.


#include "FSLoginReq.h"

FSLoginReq::FSLoginReq(const EServerId InServerId) : ServerId(InServerId)
{
}

FSLoginReq::~FSLoginReq()
{
}

void FSLoginReq::MergeFrom(const TArray<uint8>& InData)
{
	Bytes = InData;
}

int32 FSLoginReq::CalculateSize()
{
	return Bytes.Num();
}

const TArray<uint8>& FSLoginReq::ToByteArray()
{
	return Bytes;
}

const FString FSLoginReq::GetMsgId()
{
	return TEXT("SLoginReq");
}
