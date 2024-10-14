// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_Login_Res.h"
#include "GameMessage.h"
#include "GameMessageLoginRes.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API UGameMessageLoginRes : public UGameMessage
{
	GENERATED_BODY()
protected:
 	UPROPERTY(Transient)
	TObjectPtr<UC_Login_Res> LoginRes ;
public:
	UGameMessageLoginRes();
	virtual TScriptInterface<IProtoBufMessage> GetProtoBufRes() override
	{
		return TScriptInterface<UC_Login_Res>(LoginRes);
	}
	virtual bool Execute() override;
};
