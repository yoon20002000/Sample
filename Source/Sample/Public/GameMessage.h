// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkDefines.h"
#include "ProtoBufMessage.h"
#include "GameMessage.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SAMPLE_API UGameMessage : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	EMsgId MsgID = EMsgId::None;
public:
	EMsgId GetMsgID() const { return MsgID; }
	void SetMsgID(const EMsgId InMsgId) { MsgID = InMsgId; }
	virtual void SetData(const TArray<uint8>& InData);
	virtual bool Execute() PURE_VIRTUAL(UGameMessage::Execute, return true;);
	virtual TScriptInterface<IProtoBufMessage> GetProtoBufRes() PURE_VIRTUAL(UGameMessage::GetProtoBufRes, return nullptr ;);
};
