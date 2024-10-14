// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProtoBufBase.h"
#include "C_Login_Res.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API UC_Login_Res : public UProtoBufBase
{
	GENERATED_BODY()
public:
	virtual void MergeFrom(const TArray<uint8>& Data) override ;
	virtual const FString GetMsgId() override ;
	virtual int32 CalculateSize() override ;
	virtual const TArray<uint8>& ToByteArray() override ;
};
