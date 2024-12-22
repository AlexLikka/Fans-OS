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
        // ֱ�ӽ�����תΪFText
        FText LevelText = FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevel));

        // �����ı�����ı�Ϊ�ȼ�
        CurrentExpTextBlock->SetText(LevelText);
    }
}
