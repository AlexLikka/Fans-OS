// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AItem::AItem(UTexture2D* const icon, const int32 guid, const int32 num, const bool mutex)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemIcon = icon;
	ItemGuid = guid;
	ItemNum = num;
	isUnique = mutex;
}

int32 AItem::GetGuid() const noexcept
{
	return ItemGuid;
}

bool AItem::IsMutex() const noexcept
{
	return isUnique;
}

int32 AItem::GetNum() const noexcept
{
	return ItemNum;
}

void AItem::SetNum(const int32 num) noexcept
{
	ItemNum = num;
}

bool AItem::operator==(const AItem& other) const noexcept
{
	return ItemGuid == other.ItemGuid;
}

bool AItem::operator<(const AItem& other) const noexcept
{
	return ItemGuid < other.ItemGuid;
}


// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

