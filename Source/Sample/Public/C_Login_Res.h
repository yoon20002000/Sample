// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProtoBufMessage.h"
#include "UObject/NoExportTypes.h"
#include "C_Login_Res.generated.h"

/**
 * ProtoBuf 대체
 */
UCLASS()
class SAMPLE_API UC_Login_Res : public UObject, public IProtoBufMessage
{
	GENERATED_BODY()
public:
	virtual void MergeFrom(const TArray<uint8>& Data) override;
};
