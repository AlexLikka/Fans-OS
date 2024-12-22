// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

void UMainMenuWidget::NativeOnInitialized()
{
	//��ʼ��
	Super::NativeOnInitialized();
	if (StartButton != nullptr)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClicked);
	}
	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitClicked);
	}
}

void UMainMenuWidget::OnStartClicked()
{

	// ������Ϸ��ʼ
	AFPS_Fans_OSPlayerController* PlayerController = Cast<AFPS_Fans_OSPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr) {
		//Hide
		PlayerController->DestroyMainMenuWidget();
		////��ʾHUD
		//PlayerController->ShowHUD();
	}

}

void UMainMenuWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);//�˳�
}