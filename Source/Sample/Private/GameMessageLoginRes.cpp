// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMessageLoginRes.h"


UGameMessageLoginRes::UGameMessageLoginRes() : LoginRes(NewObject<UC_Login_Res>())
{
}

bool UGameMessageLoginRes::Execute()
{
	// Set  Server Login
	return true;
}
