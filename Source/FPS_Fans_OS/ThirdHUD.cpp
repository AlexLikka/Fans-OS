// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ThirdHUD.h"
#include "HUD/HealthWidget.h"
#include "HUD/ExplUserWidget.h"
void AThirdHUD::CreateHealthWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (HealthWidgetClass != nullptr)
	{
		HealthWidgetInstance = CreateWidget<UHealthWidget>(PlayerController, HealthWidgetClass);
		HealthWidgetInstance -> AddToViewport();
	}
}

void AThirdHUD::CreateExpWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (ExpWidgetClass != nullptr)
	{
		ExpWidgetInstance = CreateWidget<UExplUserWidget>(PlayerController, ExpWidgetClass);
		ExpWidgetInstance->AddToViewport();
	}
}

void AThirdHUD::HideAll()
{
	if (HealthWidgetInstance != nullptr)
	{
		HealthWidgetInstance->SetVisibility(ESlateVisibility::Hidden);  // ���ؽ���widget
	}
	if (ExpWidgetInstance != nullptr)
	{
		ExpWidgetInstance->SetVisibility(ESlateVisibility::Hidden);  // ���ؾ���widget
	}
}

void AThirdHUD::ShowAll()
{
	if (HealthWidgetInstance != nullptr)
	{
		HealthWidgetInstance->SetVisibility(ESlateVisibility::Visible);  // ��ʾ����widget
	}
	if (ExpWidgetInstance != nullptr)
	{
		ExpWidgetInstance->SetVisibility(ESlateVisibility::Visible);  // ��ʾ����widget
	}
}


void AThirdHUD::UpdateHealth(float HealthPercent)
{
	if (HealthWidgetInstance != nullptr)
	{
		HealthWidgetInstance->UpdateHealthPercent(HealthPercent);
	}
}

void AThirdHUD::UpdateStamina(float StaminaPercent)
{
	if (HealthWidgetInstance)
	{
		HealthWidgetInstance->UpdateStaminaPercent(StaminaPercent);  // ����Stamina Widget�Ľ���
	}
}

void AThirdHUD::UpdateExpLevel(int CurrentLevel)
{
	if (ExpWidgetInstance)
	{
		ExpWidgetInstance->UpdateCurrentLevel(CurrentLevel);  // ���¾���ȼ�
	}
}

void AThirdHUD::UpdateCurrentExp(float CurrentExppercent)
{
	if (ExpWidgetInstance)
	{
		ExpWidgetInstance->UpdateCurrentExp(CurrentExppercent);  // ���¾���ٷֱ�
	}
		
}
