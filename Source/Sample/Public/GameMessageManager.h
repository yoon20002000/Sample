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
	TArray<TSharedPtr<GameMessage>> MessageArray;
	TArray<TSharedPtr<GameMessage>> NextMessageArray;
	static UGameMessageManager* Instance; 
	
public:
	static UGameMessageManager* GetInstance();
	void ClearAllMessages();
	void ExecuteMessage();
	void AddMessage(const TSharedPtr<GameMessage>& InMessage);
private:
	UGameMessageManager();
};
