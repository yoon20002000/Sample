// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProtoBufBase.h"
#include "S_Login_Req.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API US_Login_Req : public UProtoBufBase
{
	GENERATED_BODY()
public:
	UPROPERTY(Transient)
	uint64 AccIdx ;
public:
	virtual void MergeFrom(const TArray<uint8>& Data) override ;
	virtual const FString GetMsgId() override;
	virtual int32 CalculateSize() override ;
	virtual const TArray<uint8>& ToByteArray() override ;
};
