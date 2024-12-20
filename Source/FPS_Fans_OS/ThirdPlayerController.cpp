// Fill out your copyright notice in the Description page of Project Settings.
 

#include "Game/ThirdPlayerController.h"
#include "HUD/RestartWidget.h"
#include "HUD/HealthWidget.h"
#include <HUD/ThirdHUD.h>
void AThirdPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//ֻ���ڽ�ɫ��������ʱ�����Ҫ����Ѫ�� ��damage_implementation()
	//�ʼ����Ҫ����Ѫ��
	/*if (HealthWidgetClass != nullptr) {
		HealthWidget = CreateWidget<UHealthWidget>(this, HealthWidgetClass);
		HealthWidget->AddToViewport();
	}*/
	//����HUD����ʵ��
	ThirdHUD = Cast<AThirdHUD>(GetHUD());
	if (ThirdHUD != nullptr) {
		ThirdHUD->CreateHealthWidget();
		ThirdHUD->CreateExpWidget();
	}
	ShowMainMenuWidget();


}

void AThirdPlayerController::ShowRestartWidget()
{
	//����HUD
	HideHUD();
	//��ʵ��ֱ�Ӵ���
	if (RestartWidgetClass != nullptr)
	{
		SetPause(true);//��Ϸ��ͣ
		SetInputMode(FInputModeUIOnly());

		bShowMouseCursor = true;//��ʾ���
		RestartWidget = CreateWidget<URestartWidget>(this, RestartWidgetClass);
		RestartWidget->AddToViewport();//�������Բ�д��HUD�� 
	}
}

void AThirdPlayerController::HideRestartWidget()
{
	//��ʵ��ֱ������ ������̫��
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AThirdPlayerController::ShowMainMenuWidget()
{
	//����HUD
	HideHUD();
	//ֱ�Ӵ���mainmenuwidget
	if (MainMenuWidgetClass != nullptr)
	{
		SetPause(true);//��Ϸ��ͣ
		SetInputMode(FInputModeUIOnly());

		bShowMouseCursor = true;//��ʾ���
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetClass);
		MainMenuWidget->AddToViewport();
	}
}

void AThirdPlayerController::DestoryMainMenuWidget()
{
	//����mainmenuwidget
	MainMenuWidget->RemoveFromParent();
	MainMenuWidget->Destruct();
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AThirdPlayerController::CreatHUD()
{
	ThirdHUD = Cast<AThirdHUD>(GetHUD());
	if (ThirdHUD != nullptr) {
		ThirdHUD->CreateHealthWidget();
	}
}

void AThirdPlayerController::HideHUD()
{
	if (ThirdHUD != nullptr)
	{
		ThirdHUD->HideAll();
	}
}

void AThirdPlayerController::ShowHUD()
{
	
	if (ThirdHUD != nullptr)
	{
		ThirdHUD->ShowAll();
	}
}



void AThirdPlayerController::UpdataHealthPercent(float HealthPercent)
{
	//if (HealthWidget != nullptr) {
	//	HealthWidget->UpdateHealthPercent(HealthPercent);
	//}
	if (ThirdHUD != nullptr) {
		ThirdHUD->UpdateHealth(HealthPercent);
	}
}

void AThirdPlayerController::UpdateStaminaPercent(float StaminaPercent)
{
	if (ThirdHUD != nullptr)
	{
		ThirdHUD->UpdateStamina(StaminaPercent);  // ��������������
	}
}


void AThirdPlayerController::UpdateCurrentExp(float CurrentExppercent)
{
	if (ThirdHUD != nullptr)
	{
		ThirdHUD->UpdateCurrentExp(CurrentExppercent);  // ��������������
	}
}

void AThirdPlayerController::UpdateCurrentLevel(int CurrentLevel)
{
	if (ThirdHUD != nullptr)
	{
		ThirdHUD->UpdateExpLevel(CurrentLevel);  // ��������������
	}
}



