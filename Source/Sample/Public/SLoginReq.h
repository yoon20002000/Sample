// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMessage.h"

enum class EServerId : uint8;
/**
 * 
 */
class SAMPLE_API SLoginReq final : public IMessage
{
private:
	EServerId ServerId;
public:
	SLoginReq(const EServerId InServerId);
	virtual ~SLoginReq() override;
	
	virtual void MergeFrom(const TArray<uint8>& InData) override;
	virtual const FString GetMsgId() override;
	virtual int32 CalculateSize() override;
	virtual const TArray<uint8>& ToByteArray() override;
};
