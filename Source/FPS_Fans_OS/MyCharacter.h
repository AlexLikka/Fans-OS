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


	/** �Զ����˺������� */
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplyDamage(float DamageAmount);

	// ����ֵ���༭ʱ���޸�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float CurrentHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float MaxHealth = 100;

	// ���˵�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FName Name = "enemy";

	// ����������������༭ʱ��ָ������������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	USkeletalMeshComponent* SkeletalMeshComponent;

	// ö�ٵ�����ľ�̬����������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TArray<TSubclassOf<AActor>> DropItemBlueprintClasses;

	// ��������ʱ��һ�õľ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int Exp = 10;


	// ��������ʱ���õķ���
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void Dead();
	void Fire();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame


	virtual void Tick(float DeltaTime) override;

	// ���������ɵĺ���
	void SpawnDropItems();

	// �������������������߼�
	void TriggerDeathAnimation();

	// ���½�ɫ��ɱ������
	void UpdateKillingEnemyTask();

	// ������Ҿ���
	void UpdatePlayerExp();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABullet> BulletClass;  // �ӵ���

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void FireAtPlayer(AFPS_Fans_OSCharacter* TargetPlayer);  // ����ҿ���


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USoundBase* FireSound;


private:
	bool IsDead();


};
	