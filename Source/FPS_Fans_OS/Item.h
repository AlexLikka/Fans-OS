// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class FPS_FANS_OS_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	// Sets default values for this actor's properties
	AItem(UTexture2D* icon, int32 guid, int32 num = 1, bool mutex = false);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 物品的Guid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemGuid;

	// 道具名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemName;

	// 道具图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* ItemIcon;

	// 物品数量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemNum;

	// 是否互斥，true不允许堆叠，false允许堆叠
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool isUnique;

	

	int32 GetGuid() const noexcept; // 获取物品的Guid
	bool IsMutex() const noexcept; // 获取物品是否互斥
	int32 GetNum() const noexcept; // 获取物品数量
	void SetNum(int32 num) noexcept; // 设置物品数量

	bool operator==(const AItem& other) const noexcept; // 重载==
	bool operator<(const AItem& other) const noexcept; // 重载<
};
