// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * ProtoBuf 대체 Class
 */
class SAMPLE_API IMessage
{
public:
	IMessage();
	virtual ~IMessage();
	virtual void MergeForm(const TArray<uint8>& InDatas) = 0;
	virtual int CalculateSize() = 0;
	virtual TArray<uint8> Calculate() = 0;
	
};
