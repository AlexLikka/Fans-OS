// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"

void UDialogueWidget::NativeConstruct()
{
    Super::NativeConstruct();
    CurrentIndex = 0;

    // �󶨰�ť�¼�
    if (AcceptButton)
    {
        AcceptButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnAcceptButtonClicked);
        AcceptButton->SetVisibility(ESlateVisibility::Hidden); // ��ʼ����
    }

    if (RejectButton)
    {
        RejectButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnRejectButtonClicked);
        RejectButton->SetVisibility(ESlateVisibility::Hidden); // ��ʼ����
    }
}

void UDialogueWidget::InitializeDialogue(const TArray<FText>& InDialogueTexts)
{
    DialogueTexts = InDialogueTexts;
    CurrentIndex = 0;
    UpdateText();
    UpdateButtonVisibility();
}

void UDialogueWidget::ShowOnScreen()
{
    SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidget::HiddenOnScreen()
{
    SetVisibility(ESlateVisibility::Hidden);
    //CurrentIndex = 0;
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
        HiddenOnScreen(); // �ı�����������
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
    UpdateButtonVisibility();
}

void UDialogueWidget::UpdateButtonVisibility()
{
    if (CurrentIndex == 4) // ���Ի����� 5 ��ʱ����ʾ��ť
    {
        if (AcceptButton)
        {
            AcceptButton->SetVisibility(ESlateVisibility::Visible);
        }
        if (RejectButton)
        {
            RejectButton->SetVisibility(ESlateVisibility::Visible);
        }
    }
    else
    {
        if (AcceptButton)
        {
            AcceptButton->SetVisibility(ESlateVisibility::Hidden);
        }
        if (RejectButton)
        {
            RejectButton->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

FReply UDialogueWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) // ���������
    {
        // �л�����һ���ı�
        if (CurrentIndex + 1 < DialogueTexts.Num())
        {
            CurrentIndex++;
            UpdateText();
        }
        else
        {
            // �Ի����������ضԻ���
            HiddenOnScreen();

            // �ָ�����ģʽ����Ϸ
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

void UDialogueWidget::OnAcceptButtonClicked()
{
    CurrentIndex += 2; // ������������ 2 ���Ի�
    if (CurrentIndex < DialogueTexts.Num())
    {
        UpdateText();
    }
    else
    {
        HiddenOnScreen();
    }
}

void UDialogueWidget::OnRejectButtonClicked()
{
    CurrentIndex += 1; // ������������ 2 ���Ի�
    if (CurrentIndex < DialogueTexts.Num())
    {
        UpdateText();
    }
    else
    {
        HiddenOnScreen();
    }
}
