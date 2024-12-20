// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainMenuWidget.h"
#include "Components/Button.h"
//#include "Game/MainMenuController.h" //如果需要将主菜单设置为单独的控制器
#include <Game/ThirdPlayerController.h>
#include <Kismet/GameplayStatics.h>
void UMainMenuWidget::NativeOnInitialized()
{	
	//初始化
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
	
	// 触发游戏开始
	AThirdPlayerController* PlayerController = Cast<AThirdPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr) {
		//Hide
		PlayerController->DestoryMainMenuWidget();
		//显示HUD
		PlayerController->ShowHUD();
	}
	
}

void UMainMenuWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);//退出
}
