// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMessageBase.h"
#include "IProtoBufMessage.h"
#include "NetworkDefines.h"
#include "GameMessage.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API UGameMessage : public UObject, public IGameMessageBase
{
	GENERATED_BODY()
public:
	EMsgId MsgID;
protected:
	UIProtoBufMessage Response;
public:
	virtual void SetData(const TArray<uint8>& InData) override;
	virtual bool Execute() override;
};
