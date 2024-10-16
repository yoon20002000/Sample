// Fill out your copyright notice in the Description page of Project Settings.


#include "FGameMessageLoginRes.h"

#include "FCLoginRes.h"

FGameMessageLoginRes::FGameMessageLoginRes() 
{
	ResMessage = MakeShareable(new FCLoginRes());
}

FGameMessageLoginRes::~FGameMessageLoginRes()
{
}

bool FGameMessageLoginRes::Execute()
{
	// do something
	return true;
}
