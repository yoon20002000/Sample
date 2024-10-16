// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "VM_Menu.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SAMPLE_API UVM_Menu : public UMVVMViewModelBase
{
	GENERATED_BODY()
private:
	const FText DefaultText = FText::FromString(TEXT("Server not connected..."));
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter,Setter, meta=(AllowPrivateAccess=true))
	FText ServerIp = DefaultText;

public:
	void SetServerIp(const FText& InServerIp)
	{
		if(InServerIp.IsEmpty())
		{
			return;
		}
		
		if(UE_MVVM_SET_PROPERTY_VALUE(ServerIp, InServerIp))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(IsVisibleConnectButton);
		}
	}
	FText GetServerIp() const
	{
		return ServerIp;
	}
	UFUNCTION(BlueprintPure,FieldNotify)
	bool IsVisibleConnectButton() const
	{
		return ServerIp.EqualTo(DefaultText);
	}
};
