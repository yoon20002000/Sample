// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMessageLoginRes.h"


UGameMessageLoginRes::UGameMessageLoginRes() : LoginRes(CreateDefaultSubobject<UC_Login_Res>(TEXT("Root")))
{
}

bool UGameMessageLoginRes::Execute()
{
	// Set  Server Login
	return true;
}
