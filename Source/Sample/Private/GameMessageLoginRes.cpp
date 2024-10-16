// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMessageLoginRes.h"

#include "CLoginRes.h"

GameMessageLoginRes::GameMessageLoginRes() 
{
	ResMessage = MakeShareable(new CLoginRes());
}

GameMessageLoginRes::~GameMessageLoginRes()
{
}

bool GameMessageLoginRes::Execute()
{
	// do something
	return true;
}
