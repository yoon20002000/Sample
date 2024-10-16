// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGameMessage.h"

class FCLoginRes;
/**
 * 
 */
class SAMPLE_API FGameMessageLoginRes final : public FGameMessage
{
public:
	FGameMessageLoginRes();
	virtual ~FGameMessageLoginRes() override;

	virtual bool Execute() override;
};
