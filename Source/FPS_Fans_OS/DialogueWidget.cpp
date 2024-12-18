// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"

void UDialogueWidget::InitializeDialogue(const TArray<FText>& InDialogueTexts)
{
    DialogueTexts = InDialogueTexts;
    CurrentIndex = 0;
    UpdateText();
}

void UDialogueWidget::ShowOnScreen()
{
    SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidget::HiddenOnScreen()
{
    SetVisibility(ESlateVisibility::Hidden);
}

void UDialogueWidget::OnNextText()
{
    if (DialogueTexts.IsValidIndex(CurrentIndex + 1))
    {
        ++CurrentIndex;
        UpdateText();
    }
    else
    {
        HiddenOnScreen(); // 文本结束后隐藏
    }
}

void UDialogueWidget::UpdateText()
{
    /*UTextBlock* TextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("DialogueText")));
    if (TextBlock && DialogueTexts.IsValidIndex(CurrentIndex))
    {
        TextBlock->SetText(DialogueTexts[CurrentIndex]);
    }*/
}