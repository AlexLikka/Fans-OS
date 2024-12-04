// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class FPS_FANS_OS_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* MeshComponent;

	// 以下是对武器的基础属性的定义
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName Name;  // 这个武器的名字
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int MaxAmmo;  // 这把武器一个弹夹能容纳的最大子弹数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int Damage;  // 武器的伤害值
	// 子弹类，用于生成子弹
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABullet> BulletClass;
	// 射击音效
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USoundBase* FireSound;
	// 枪口Socket名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = TEXT("MuzzleSocket");
};
