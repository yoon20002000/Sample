// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SocketPacketHandler.h"
#include "SocketPacketHandlerAuth.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API USocketPacketHandlerAuth : public USocketPacketHandler
{
	GENERATED_BODY()
public:
	virtual UGameMessage* FindPacketMessage(const EMsgId InMsgId) override;
	
};
