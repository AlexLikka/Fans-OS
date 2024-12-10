// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemy::ApplyDamage(float DamageAmount)
{
	Health -= DamageAmount;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsDead())
	{
		Dead();
	}
}

// 当敌人死亡时调用的函数
void AEnemy::Dead()
{
	// 生成掉落物
	SpawnDropItems();

	// 触发死亡动画或其他逻辑
	TriggerDeathAnimation();

	// 销毁敌人角色
	Destroy();
	
}

bool AEnemy::IsDead()
{
	return Health <= 0;
}

// 生成掉落物的方法
void AEnemy::SpawnDropItems()
{
	if (DropItemBlueprintClasses.Num() == 0) return;

	// 获取敌人当前位置
	FVector EnemyLocation = GetActorLocation();

	// 为每个掉落物生成随机位置
	for (int32 i = 0; i < DropItemBlueprintClasses.Num(); i++)
	{
		// 获取当前掉落物的蓝图类
		TSubclassOf<AActor> ItemBlueprintClass = DropItemBlueprintClasses.IsValidIndex(i) ? DropItemBlueprintClasses[i] : nullptr;

		if (ItemBlueprintClass)
		{
			// 在敌人位置附近随机一个点
			FVector2D RandomOffset = FMath::RandPointInCircle(100.0f); // 200是半径，可以根据需求调整
			FVector2D SpawnLocation2D = FVector2D(EnemyLocation.X + RandomOffset.X, EnemyLocation.Y + RandomOffset.Y);

			// 创建ADropItem对象
			ADropItem* DropItem = GetWorld()->SpawnActor<ADropItem>(ADropItem::StaticClass(), EnemyLocation, FRotator::ZeroRotator);
			if (DropItem)
			{
				// 调用 SpawnDropItemOnGround 方法生成掉落物
				DropItem->ItemBlueprintClass = ItemBlueprintClass;  // 设置蓝图类
				DropItem->SpawnDropItemOnGround(GetWorld(), SpawnLocation2D);  // 生成掉落物
			}
		}
	}
}

// 触发死亡动画或其他逻辑
void AEnemy::TriggerDeathAnimation()
{
	// 在这里可以添加死亡动画的代码，或者其他死亡逻辑
	// 比如播放死亡动画、掉落物等
}