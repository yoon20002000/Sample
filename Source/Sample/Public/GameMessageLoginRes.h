// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMessage.h"

class CLoginRes;
/**
 * 
 */
class SAMPLE_API GameMessageLoginRes final : public GameMessage
{
public:
	GameMessageLoginRes();
	virtual ~GameMessageLoginRes() override;

	virtual bool Execute() override;
};
