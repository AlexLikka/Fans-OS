// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DropItem.h" 
#include "WeaponActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "FPS_Fans_OSCharacter.h"
#include "WeaponActor.h"
#include "MyCharacter.generated.h"

class ACurrentWeapon;

UCLASS()
class FPS_FANS_OS_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* EnemyMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;


	/// 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class UStaticMeshComponent* WeaponSocketMesh;



	///


	/** 自定义伤害处理函数 */
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplyDamage(float DamageAmount);

	// 生命值，编辑时可修改
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float CurrentHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float MaxHealth = 100;

	// 敌人的名字
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FName Name = "enemy";

	// 骨骼网格体组件，编辑时可指定骨骼网格体
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	USkeletalMeshComponent* SkeletalMeshComponent;

	// 枚举掉落物的静态网格体类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TArray<TSubclassOf<AActor>> DropItemBlueprintClasses;

	// 敌人死亡时玩家获得的经验
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int Exp = 10;


	// 敌人死亡时调用的方法
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void Dead();
	void Fire();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame


	virtual void Tick(float DeltaTime) override;

	// 掉落物生成的函数
	void SpawnDropItems();

	// 触发死亡动画或其他逻辑
	void TriggerDeathAnimation();

	// 更新角色的杀敌任务
	void UpdateKillingEnemyTask();

	// 给予玩家经验
	void UpdatePlayerExp();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABullet> BulletClass;  // 子弹类

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void FireAtPlayer(AFPS_Fans_OSCharacter* TargetPlayer);  // 对玩家开火


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USoundBase* FireSound;


private:
	bool IsDead();


};
	