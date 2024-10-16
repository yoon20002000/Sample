// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SAMPLE_API IMessage
{
public:
	TArray<uint8> Bytes;
public:
	IMessage();
	virtual ~IMessage();
public:
	virtual void MergeFrom(const TArray<uint8>& InData) = 0;
	virtual const FString GetMsgId() = 0;
	virtual int32 CalculateSize() = 0;
	virtual const TArray<uint8>& ToByteArray() = 0;
};
