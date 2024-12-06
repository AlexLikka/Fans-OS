// Fill out your copyright notice in the Description page of Project Settings.


#include "Backpack.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h" // 需要引用 PlayerController 类
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBackpack::UBackpack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBackpack::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBackpack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBackpack::OpenBackpackUI()
{
	// 如果 UI 类已经设置且实例不存在，则加载并显示 UI
	if (BackpackUIClass && !BackpackUIInstance)
	{
		// 获取玩家控制器（或是游戏中的其他 UI 管理对象）
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			// 创建 UI 实例并将其添加到视口
			BackpackUIInstance = CreateWidget<UUserWidget>(PlayerController, BackpackUIClass);
			if (BackpackUIInstance)
			{
				BackpackUIInstance->AddToViewport();
			}
		}
	}
}

void UBackpack::CloseBackpackUI()
{
	if (BackpackUIInstance)
	{
		// 从视口中移除UI
		BackpackUIInstance->RemoveFromParent();

		// 清除UI实例引用
		BackpackUIInstance = nullptr;
	}
}

void UBackpack::AddItemToBackpack(AItem* Item)
{
}

