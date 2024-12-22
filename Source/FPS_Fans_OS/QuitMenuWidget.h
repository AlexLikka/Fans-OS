// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "FPS_Fans_OS\FPS_Fans_OSPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "QuitMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class FPS_FANS_OS_API UQuitMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	//包括继续游戏 退出游戏
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>ContinueButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>ExitButton;
protected:
	UFUNCTION()
	void OnContinueClicked();
	UFUNCTION()
	void OnExitClicked();

};
