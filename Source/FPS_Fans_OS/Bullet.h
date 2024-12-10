// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class FPS_FANS_OS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 子弹的碰撞组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* CollisionComponent;

	// 子弹的静态网格组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* BulletMesh;

	// 子弹移动组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	// 伤害值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageAmount;

	// 碰撞时的处理
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
