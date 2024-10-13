// Fill out your copyright notice in the Description page of Project Settings.


#include "IProtoBufMessage.h"

void UIProtoBufMessage::MergeForm(const TArray<uint8>& InData)
{
}

int UIProtoBufMessage::CalculateSize() const
{
	return 0;
}

const TArray<uint8>& UIProtoBufMessage::ToByteArray() const
{
	return Data;
}
