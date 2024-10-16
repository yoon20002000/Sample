// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SocketNetworkManager.h"
#include "UObject/NoExportTypes.h"
#include "SocketPacketHandler.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SAMPLE_API USocketPacketHandler : public UObject
{
	GENERATED_BODY()
public:
	USocketPacketHandler()
	{
		USocketNetworkManager::GetInstance()->AddHandler(this);
	}
	virtual  TSharedPtr<GameMessage> FindPacketMessage(const EMsgId InMsgId) PURE_VIRTUAL(USocketPacketHandler::FindPacketMessage, return nullptr;);
};
