// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BytesBuffer.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API UBytesBuffer : public UObject
{
	GENERATED_BODY()
public:
	int32 Tail;
	int16 PacketSize;
public:
	UBytesBuffer();

	void AddData(const TArray<uint8>& InData);
	
};
