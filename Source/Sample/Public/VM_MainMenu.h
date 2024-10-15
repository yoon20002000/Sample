// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "VM_MainMenu.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SAMPLE_API UVM_MainMenu : public UMVVMViewModelBase
{
	GENERATED_BODY()
private:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FString ServerIp;
public:
	UFUNCTION(BlueprintCallable)
	void ConnectServer();

	void SetServerIp(const FString& InServerIp)
	{
		if(UE_MVVM_SET_PROPERTY_VALUE(ServerIp,InServerIp))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(ServerIp);
		}
	}
	FString GetServerIp() const
	{
		return ServerIp;
	}
};
