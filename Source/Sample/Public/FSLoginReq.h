// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMessage.h"

enum class EServerId : uint8;
/**
 * 
 */
class SAMPLE_API FSLoginReq final : public IMessage
{
private:
	EServerId ServerId;
public:
	FSLoginReq(const EServerId InServerId);
	virtual ~FSLoginReq() override;
	
	virtual void MergeFrom(const TArray<uint8>& InData) override;
	virtual const FString GetMsgId() override;
	virtual int32 CalculateSize() override;
	virtual const TArray<uint8>& ToByteArray() override;
};
