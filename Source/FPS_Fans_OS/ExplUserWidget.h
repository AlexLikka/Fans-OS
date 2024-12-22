// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExplUserWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class NEWPROJECT_API UExplUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//UI组件 绑定到CurrentExpBar变量上
	//绑定的经验进度条
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> CurrentExpBar;
	// 绑定经验文本框
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentExpTextBlock;

	//更新经验条百分比
	void UpdateCurrentExp(float  CurrentExppercent);
	//更新经验等级
	void UpdateCurrentLevel(int CurrentLevel);

};
