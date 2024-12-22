// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ExplUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
void UExplUserWidget::UpdateCurrentExp(float CurrentExppercent)
{
	if (CurrentExpBar) {
		CurrentExpBar->SetPercent(CurrentExppercent);
	}
}

void UExplUserWidget::UpdateCurrentLevel(int CurrentLevel)
{
    if (CurrentExpTextBlock)
    {
        // 直接将整数转为FText
        FText LevelText = FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevel));

        // 设置文本框的文本为等级
        CurrentExpTextBlock->SetText(LevelText);
    }
}
