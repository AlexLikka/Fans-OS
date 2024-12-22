// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPS_Fans_OSPlayerController.generated.h"

class UQuitMenuWidget;
class UMainMenuWidget;
class UInputMappingContext;

/**
 *
 */
UCLASS()
class FPS_FANS_OS_API AFPS_Fans_OSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void CreateMainMenuWidget();
	void DestroyMainMenuWidget();
	void CreateQuitMenuWidget();
	void DestroyQuitMenuWidget();
	//MainMenuwidget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenuWidget>MainMenuWidgetClass;
	//UQuitMenuwidget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuitMenuWidget>QuitMenuWidgetClass;
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QuitGame;  // 引用输入动作数据资产


	UPROPERTY()
	TObjectPtr<UMainMenuWidget>MainMenuWidget;

	UPROPERTY()
	TObjectPtr<UQuitMenuWidget>QuitMenuWidget;
	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
};
