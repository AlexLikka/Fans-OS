// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "FPS_Fans_OS/FPS_Fans_OSPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "MainMenuWidget.generated.h"

class UButton;
/**
 *
 */
UCLASS()
class FPS_FANS_OS_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	//������ʼ��Ϸ �˳���Ϸ
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>StartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>ExitButton;
protected:
	UFUNCTION()
	void OnStartClicked();
	UFUNCTION()
	void OnExitClicked();

};