// Fill out your copyright notice in the Description page of Project Settings.


#include "QuitMenuWidget.h"

void UQuitMenuWidget::NativeOnInitialized()
{
	//³õÊ¼»¯
	Super::NativeOnInitialized();
	if (ContinueButton != nullptr)
	{
		ContinueButton->OnClicked.AddDynamic(this, &UQuitMenuWidget::OnContinueClicked);
	}
	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this, &UQuitMenuWidget::OnExitClicked);
	}
}

void UQuitMenuWidget::OnContinueClicked()
{
	AFPS_Fans_OSPlayerController* PlayerController = Cast<AFPS_Fans_OSPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr) {
		//Hide
		PlayerController->DestroyQuitMenuWidget();
	}

}

void UQuitMenuWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);//ÍË³ö
}