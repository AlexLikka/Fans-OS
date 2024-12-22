// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPS_Fans_OSPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MainMenuWidget.h"
#include "QuitMenuWidget.h"
#include "Engine/LocalPlayer.h"

void AFPS_Fans_OSPlayerController::CreateMainMenuWidget()
{

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

void AFPS_Fans_OSPlayerController::DestroyMainMenuWidget()
{
	//销毁mainmenuwidget
	MainMenuWidget->RemoveFromParent();
	MainMenuWidget->Destruct();
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AFPS_Fans_OSPlayerController::CreateQuitMenuWidget()
{
	
	//直接创建QuitMenuWidget
	if (QuitMenuWidgetClass != nullptr)
	{
		SetPause(true);//游戏暂停
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;//显示鼠标
		QuitMenuWidget = CreateWidget<UQuitMenuWidget>(this, QuitMenuWidgetClass);
		QuitMenuWidget->AddToViewport();
	}

}

void AFPS_Fans_OSPlayerController::DestroyQuitMenuWidget()
{
	//销毁QuitMenuWidget
	QuitMenuWidget->RemoveFromParent();
	QuitMenuWidget->Destruct();
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AFPS_Fans_OSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreateMainMenuWidget();
	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	// 确保 QuitGame 已正确初始化并指向一个有效的 UInputAction
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// 绑定 QuitGame 操作映射
		EnhancedInputComponent->BindAction(QuitGame, ETriggerEvent::Triggered, this, &AFPS_Fans_OSPlayerController::CreateQuitMenuWidget);
	}
}