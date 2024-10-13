// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMessage.h"

#include "UObject/NoExportTypes.h"
#include "SocketNetworkManager.generated.h"

/**
 * 
 */
class USocketPacketHandler;
UCLASS()
class SAMPLE_API USocketNetworkManager : public UObject
{
	GENERATED_BODY()
private:
	static USocketNetworkManager* Instance;
	UPROPERTY()
	TArray<USocketPacketHandler*> PacketHandlersArray;
	
public:
	static USocketNetworkManager* GetInstance();
	UGameMessage* FindPacketMessage(EMsgId InMsgId);
	void AddHandler(USocketPacketHandler* SocketPacketHandler);

private:
	USocketNetworkManager();
};
