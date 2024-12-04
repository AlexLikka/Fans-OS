// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropItem.generated.h"

class UCapsuleComponent;

UCLASS()
class FPS_FANS_OS_API ADropItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropItem();

	// 设置蓝图类作为掉落物的外表
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DropItem")
	TSubclassOf<AActor> ItemBlueprintClass;

	// 生成掉落物的方法，接受x, y坐标，并根据地面自动调整z坐标
	// UFUNCTION(BlueprintCallable, Category = "DropItem")
	void SpawnDropItemOnGround(UWorld* World, FVector2D Location2D);


	// 捡起掉落物
	UFUNCTION(BlueprintCallable, Category = "DropItem")
	void Pickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 玩家进入触发器时的回调
	UFUNCTION()
	void OnPlayerEnterTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// 掉落物的静态网格组件（用作显示物品的外观）
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	// 设置触发器组件
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* PickupTrigger;

	// 用于保存外观模型的Actor
	UPROPERTY(VisibleAnywhere)
	AActor* ItemActor;
};
