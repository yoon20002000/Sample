// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMessage.h"

/**
 * 
 */
class SAMPLE_API FCLoginRes : public IMessage
{
public:
	FCLoginRes();
	virtual ~FCLoginRes() override;
	virtual void MergeFrom(const TArray<uint8>& InData) override;
	virtual const FString GetMsgId() override;
	virtual int32 CalculateSize() override;
	virtual const TArray<uint8>& ToByteArray() override;
};
