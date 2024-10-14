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
	UPROPERTY()
	TArray<UGameMessage*> MessageArray;
	UPROPERTY()
	TArray<UGameMessage*> NextMessageArray;
	static UGameMessageManager* Instance; 
	
public:
	static TObjectPtr<UGameMessageManager> GetInstance();
	void ClearAllMessages();
	void ExecuteMessage();
	void AddMessage(const TObjectPtr<UGameMessage>& InMessage);
private:
	UGameMessageManager();
};
