// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "DialogueWidget.h"
#include "NPCActor.generated.h"

class UDialogueWidget;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class MAP_API ANPCActor : public AInteractiveActor
{
	GENERATED_BODY()
public:
	ANPCActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void BeginOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void EndOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	virtual void HitFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void MoveFunction() override;
	// 显示对话框
	void ShowDialogue();
	// 隐藏对话框
	void HideDialogue();
	UPROPERTY()
	UDialogueWidget* DialogueWidget;
	// 对话UI组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DialogueTexts")
	TArray<FText> DialogueTexts;
};
