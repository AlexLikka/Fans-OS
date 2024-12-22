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
	void UpdateHealth(float HealthPercent);//��������ֵ
	void UpdateStamina(float StaminaPercent);//��������
	void UpdateExpLevel(int CurrentLevel);//���¾������ٷֱ�
	void UpdateCurrentExp(float  CurrentExppercent);//���¾�����

};
