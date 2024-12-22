// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <HUD/RestartWidget.h>
#include <HUD/MainMenuWidget.h>
#include "ThirdPlayerController.generated.h"

class UMainMenuWidget;
class URestartWidget;
class UHealthWidget;
class AThirdHUD;
/**
 * 
 */
UCLASS()
class NEWPROJECT_API AThirdPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URestartWidget>RestartWidgetClass;	

	//Health
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHealthWidget>HealthWidgetClass;

	//MainMenuwidget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenuWidget>MainMenuWidgetClass;

	void ShowRestartWidget();
	void HideRestartWidget();
	void ShowMainMenuWidget();
	void DestoryMainMenuWidget();
	void CreatHUD();
	void HideHUD();
	void ShowHUD();
	//更新健康
	void UpdataHealthPercent(float HealthPercent);
	//更新体力
	void UpdateStaminaPercent(float StaminaPercent);
	//更新经验条百分比
	void UpdateCurrentExp(float CurrentExppercent);
	//更新经验等级
	void UpdateCurrentLevel(int CurrentLevel);

protected:
	virtual void BeginPlay()override;
private:
	UPROPERTY()
	TObjectPtr<URestartWidget>RestartWidget;

	UPROPERTY()
	TObjectPtr<UHealthWidget>HealthWidget;

	UPROPERTY()
	TObjectPtr<UMainMenuWidget>MainMenuWidget;

	UPROPERTY()
	TObjectPtr<AThirdHUD> ThirdHUD;
};
