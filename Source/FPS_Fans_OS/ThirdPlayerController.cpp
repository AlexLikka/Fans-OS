// Fill out your copyright notice in the Description page of Project Settings.
 

#include "Game/ThirdPlayerController.h"
#include "HUD/RestartWidget.h"
#include "HUD/HealthWidget.h"
#include <HUD/ThirdHUD.h>
void AThirdPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//只有在角色被攻击的时候才需要更新血条 即damage_implementation()
	//最开始就需要创建血条
	/*if (HealthWidgetClass != nullptr) {
		HealthWidget = CreateWidget<UHealthWidget>(this, HealthWidgetClass);
		HealthWidget->AddToViewport();
	}*/
	//换成HUD整体实现
	ThirdHUD = Cast<AThirdHUD>(GetHUD());
	if (ThirdHUD != nullptr) {
		ThirdHUD->CreateHealthWidget();
		ThirdHUD->CreateExpWidget();
	}
	ShowMainMenuWidget();


}

void AThirdPlayerController::ShowRestartWidget()
{
	//隐藏HUD
	HideHUD();
	//其实是直接创建
	if (RestartWidgetClass != nullptr)
	{
		SetPause(true);//游戏暂停
		SetInputMode(FInputModeUIOnly());

		bShowMouseCursor = true;//显示鼠标
		RestartWidget = CreateWidget<URestartWidget>(this, RestartWidgetClass);
		RestartWidget->AddToViewport();//弹窗可以不写在HUD中 
	}
}

void AThirdPlayerController::HideRestartWidget()
{
	//其实是直接销毁 命名不太好
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AThirdPlayerController::ShowMainMenuWidget()
{
	//隐藏HUD
	HideHUD();
	//直接创建mainmenuwidget
	if (MainMenuWidgetClass != nullptr)
	{
		SetPause(true);//游戏暂停
		SetInputMode(FInputModeUIOnly());

		bShowMouseCursor = true;//显示鼠标
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetClass);
		MainMenuWidget->AddToViewport();
	}
}

void AThirdPlayerController::DestoryMainMenuWidget()
{
	//销毁mainmenuwidget
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
		ThirdHUD->UpdateStamina(StaminaPercent);  // 更新体力进度条
	}
}


void AThirdPlayerController::UpdateCurrentExp(float CurrentExppercent)
{
	if (ThirdHUD != nullptr)
	{
		ThirdHUD->UpdateCurrentExp(CurrentExppercent);  // 更新体力进度条
	}
}

void AThirdPlayerController::UpdateCurrentLevel(int CurrentLevel)
{
	if (ThirdHUD != nullptr)
	{
		ThirdHUD->UpdateExpLevel(CurrentLevel);  // 更新体力进度条
	}
}



