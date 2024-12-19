// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"

void UDialogueWidget::NativeConstruct()
{
    Super::NativeConstruct();
    CurrentIndex = 0;
}

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
    if (!IsInViewport())
    {
        UE_LOG(LogTemp, Warning, TEXT("Widget is not added to the viewport."));
        return;
    }

    UTextBlock* TextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("DialogueText")));
    if (TextBlock)
    {
        if (DialogueTexts.IsValidIndex(CurrentIndex))
        {
            TextBlock->SetText(DialogueTexts[CurrentIndex]);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("DialogueText widget not found or is not a TextBlock!"));
    }
}

FReply UDialogueWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) // 检测左键点击
    {
        // 切换到下一条文本
        if (CurrentIndex + 1 < DialogueTexts.Num())
        {
            CurrentIndex++;
            UpdateText();
        }
        else
        {
            // 对话结束，隐藏对话框
            HiddenOnScreen();

            // 恢复输入模式到游戏
            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                FInputModeGameOnly InputMode;
                PlayerController->SetInputMode(InputMode);
                PlayerController->bShowMouseCursor = false;
            }
        }
        return FReply::Handled();
    }
    return FReply::Unhandled();
}