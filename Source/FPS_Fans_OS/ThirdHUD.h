// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ThirdHUD.generated.h"


class UHealthWidget;
class UStaminaWidget;
class UExplUserWidget;
/**
 * 
 */
UCLASS()
class NEWPROJECT_API AThirdHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UHealthWidget>HealthWidgetClass;
	UPROPERTY()
	TObjectPtr<UHealthWidget>HealthWidgetInstance;

	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UExplUserWidget>ExpWidgetClass;
	UPROPERTY()
	TObjectPtr<UExplUserWidget>ExpWidgetInstance;


	//UPROPERTY(EditDefaultsOnly, Category = "HUD")
	//TSubclassOf<UStaminaWidget>StaminaWidgetClass;
	//UPROPERTY()
	//TObjectPtr<UStaminaWidget>StaminaWidgetInstance;

	void CreateHealthWidget();
	void CreateExpWidget();
	void HideAll();
	void ShowAll();
	void UpdateHealth(float HealthPercent);//更新生命值
	void UpdateStamina(float StaminaPercent);//更新体力
	void UpdateExpLevel(int CurrentLevel);//更新经验条百分比
	void UpdateCurrentExp(float  CurrentExppercent);//更新经验条

};
