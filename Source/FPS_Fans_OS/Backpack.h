// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/ActorComponent.h"
#include "Backpack.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_FANS_OS_API UBackpack : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBackpack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Backpack Action")
	void OpenBackpackUI();  // 打开背包UI
	UFUNCTION(BlueprintCallable, Category = "Backpack Action")
	void CloseBackpackUI();  // 关闭~
	UFUNCTION(BlueprintCallable, Category = "Backpack Action")
	void AddItemToBackpack(AItem* Item);  // 将一件物品添加进背包
	

	// 背包UI的类
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BackpackUIClass;

	// 指向现在正在打开的背包UI类，如果为空则说明现在没有打开背包UI
	UPROPERTY()
	UUserWidget* BackpackUIInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsBackpackOpening = false;
	
};
