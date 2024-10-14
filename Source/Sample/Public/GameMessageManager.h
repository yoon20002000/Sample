// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMessage.h"
#include "UObject/NoExportTypes.h"
#include "GameMessageManager.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API UGameMessageManager : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY(Transient)
	TArray<UGameMessage*> MessageArray;
	UPROPERTY(Transient)
	TArray<UGameMessage*> NextMessageArray;
	static UGameMessageManager* Instance; 
	
public:
	static UGameMessageManager* GetInstance();
	void ClearAllMessages();
	void ExecuteMessage();
	void AddMessage(const TObjectPtr<UGameMessage>& InMessage);
private:
	UGameMessageManager();
};
