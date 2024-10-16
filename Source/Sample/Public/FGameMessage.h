// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkDefines.h"

class IMessage;
/**
 * 
 */
class SAMPLE_API FGameMessage
{
protected:
	EMsgId MsgID = EMsgId::None;
	TSharedPtr<IMessage> ResMessage; 
public:
	FGameMessage();
	virtual ~FGameMessage();
	
	EMsgId GetMsgID() const { return MsgID; }
	void SetMsgID(const EMsgId InMsgId) { MsgID = InMsgId; }
	virtual void SetData(const TArray<uint8>& InData);
	virtual bool Execute() = 0;
};
