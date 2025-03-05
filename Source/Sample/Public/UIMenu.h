// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIMenu.generated.h"

class UVM_Menu;
/**
 * 
 */
UCLASS()
class SAMPLE_API UUIMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UButton>  ConnectServerButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UMultiLineEditableTextBox> IPTextBox;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<UVM_Menu> VM_Menu2;
public:
	UFUNCTION()
	void OnClickedConnectServerButton();
	virtual bool Initialize() override;
};
