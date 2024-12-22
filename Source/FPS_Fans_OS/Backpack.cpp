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

int32 UBackpack::FindItem(const AItem* Item) const noexcept
{
	if (Item == nullptr)
	{
		return -1;
	}
	int32 index = 0;
	while (index < Items.Num())
	{
		if (Item->GetGuid() == Items[index]->GetGuid())
		{
			return index;
		}
	}
	return -1;
}


// Called every frame
void UBackpack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBackpack::AddItemToBackpack(AItem* Item)
{
	Item = Item->Clone();
	if (Item == nullptr || Capacity <= Items.Num())
	{
		return false;
	}
	Items.Add(Item);
	return true;
}

void UBackpack::DeleteItemFromBackpack(const AItem* const Item)
{
	if (Item == nullptr)
	{
		return;
	}
	const int32 index = FindItem(Item);
	if (index < 0)
	{
		return; // 未找到，直接返回
	}
	Items.RemoveAt(index); // 找到则删除
}

void UBackpack::ReduceItemFromBackpack(const AItem* const Item)
{
	if (Item == nullptr)
	{
		return;
	}
	const int32 index = FindItem(Item);
	if (index < 0)
	{
		return; // 未找到，直接返回
	}
	AItem* const item = Items[index];
	if (Item->GetNum() >= item->GetNum())
	{
		Items.RemoveAt(index);
		return;
	}
	item->SetNum(item->GetNum() - Item->GetNum());
}

