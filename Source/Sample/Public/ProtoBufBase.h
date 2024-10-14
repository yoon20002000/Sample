// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProtoBufMessage.h"
#include "ProtoBufBase.generated.h"

/**
 * ProtoBuf 대체
 */
UCLASS(Abstract)
class SAMPLE_API UProtoBufBase : public UObject, public IProtoBufMessage
{
	GENERATED_BODY()
protected:
	TArray<uint8> Bytes;
public:
	UProtoBufBase();
	virtual void MergeFrom(const TArray<uint8>& Data) override PURE_VIRTUAL(UProtoBufBase::MergeFrom,);
	virtual const FString GetMsgId() override PURE_VIRTUAL(UProtoBufBase::MergeFrom, return FString(""););
	virtual int32 CalculateSize() override PURE_VIRTUAL(UProtoBufBase::CalculateSize, return 0;);
	virtual const TArray<uint8>& ToByteArray() override PURE_VIRTUAL(UProtoBufBase::CalculateSize, return Bytes;); 
};
