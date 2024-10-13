// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IProtoBufMessage.generated.h"

/**
 * ProtoBuf IMessage 대용
 */
UCLASS()
class SAMPLE_API UIProtoBufMessage : public UObject
{
	GENERATED_BODY()
public:
	TArray<uint8> Data;
public:
	virtual void MergeForm(const TArray<uint8>& InData);
	virtual int CalculateSize() const;
	virtual const TArray<uint8>& ToByteArray() const;
};
