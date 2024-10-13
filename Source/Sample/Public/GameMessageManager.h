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
	TArray<TWeakObjectPtr<UGameMessage>> MessageArray;
	UPROPERTY()
	TArray<TWeakObjectPtr<UGameMessage>> NextMessageArray;

public:
	UGameMessageManager();
	void ClearMessages();
	void ExecuteMessage();
	void AddMessage(const TWeakObjectPtr<UGameMessage> InMessage);
};
