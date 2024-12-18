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
    // 初始化函数，接受文本数组
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void InitializeDialogue(const TArray<FText>& InDialogueTexts);

    // 显示对话框
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void ShowOnScreen();

    // 隐藏对话框
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void HiddenOnScreen();

    // 跳转到下一条文本
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void OnNextText();

private:
    // 文本数组
    TArray<FText> DialogueTexts;

    // 当前文本索引
    int32 CurrentIndex;

    // 更新显示的文本
    void UpdateText();
};
