// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainMenuWidget.h"
#include "Components/Button.h"
//#include "Game/MainMenuController.h" //�����Ҫ�����˵�����Ϊ�����Ŀ�����
#include <Game/ThirdPlayerController.h>
#include <Kismet/GameplayStatics.h>
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
	AThirdPlayerController* PlayerController = Cast<AThirdPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr) {
		//Hide
		PlayerController->DestoryMainMenuWidget();
		//��ʾHUD
		PlayerController->ShowHUD();
	}
	
}

void UMainMenuWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);//�˳�
}
