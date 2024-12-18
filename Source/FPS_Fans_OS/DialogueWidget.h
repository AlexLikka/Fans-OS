// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAP_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    // ��ʼ�������������ı�����
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void InitializeDialogue(const TArray<FText>& InDialogueTexts);

    // ��ʾ�Ի���
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void ShowOnScreen();

    // ���ضԻ���
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void HiddenOnScreen();

    // ��ת����һ���ı�
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void OnNextText();

private:
    // �ı�����
    TArray<FText> DialogueTexts;

    // ��ǰ�ı�����
    int32 CurrentIndex;

    // ������ʾ���ı�
    void UpdateText();
};
