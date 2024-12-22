// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class NEWPROJECT_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//UI组件 绑定到HealthBar变量上
	//绑定的血量进度条
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	//体力进度条
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar>StaminaBar;

	//更新血量百分比
	void UpdateHealthPercent(float HealthPercent);
	//更新体力百分比
	void UpdateStaminaPercent(float StaminaPercent);
};
