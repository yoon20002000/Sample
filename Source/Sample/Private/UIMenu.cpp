// Fill out your copyright notice in the Description page of Project Settings.


#include "UIMenu.h"

#include "MVVMGameSubsystem.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"

void UUIMenu::OnClickedConnectServerButton()
{
	FText IP = IPTextBox->GetText();

	UMVVMViewModelCollectionObject* Collection = GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>()->GetViewModelCollection();

	//Collection->AddViewModelInstance(this,VM_Menu2);
	// vm 가져와서 setserverip 호출 해야됨.
	
}

bool UUIMenu::Initialize()
{
	if (const bool bIsInitialized = Super::Initialize(); bIsInitialized == false)
	{
		return false;
	}

	ConnectServerButton->OnClicked.AddDynamic(this, &UUIMenu::OnClickedConnectServerButton);

	
	return true;
}
