// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Backpack.h"
#include "WeaponActor.h"
#include "SkillComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "FPS_Fans_OSCharacter.generated.h"

class USkillComponent;
class UTaskComponent;
class ACurrentWeapon;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

// // 声明一个动态委托，用于背包打开关闭的事件
// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackpackToggle);

UCLASS(config=Game)
class AFPS_Fans_OSCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
public:
	AFPS_Fans_OSCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicInformation")
	int CurrentHealth = 100;  // 当前生命值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicInformation")
	int MaxHealth = 100;  // 当前生命值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicInformation")
	float CurrentStamina = 100; // 体力值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicInformation")
	float MaxStamina = 100; // 体力值
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerActionStatus")
	bool IsSpring = false;  // 现在是否在疾跑
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerActionStatus")
	bool IsChangingWeapon = false;  // 现在是否正在更换武器
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicStatus")
	bool CanMove = true; // 现在是否可以移动
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicStatus")
	bool CanSpring = true; // 现在是否可以疾跑
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicStatus")
	bool CanFire = false; // 现在是否可以开火

	// 背包组件
	// 声明 TSubclassOf<UBackpack> 变量，允许在蓝图中选择绑定的 Backpack 类（这个是背包组件的主体对象）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Backpack")
	TSubclassOf<UBackpack> BackpackClass;
	// 声明 TSubclassOf<UUserWidget> 变量，允许在蓝图中选择绑定的BackpackUI类（这个是背包组件对象的BackpackUIClass属性）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Backpack")
	TSubclassOf<UUserWidget> BackpackUI;
	// 声明一个指向当前实例化的背包对象的指针
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Backpack")
	UBackpack* Backpack;

	// 手持物品组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="CurrentWeapon")
	ACurrentWeapon* CurrentWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="CurrentWeapon")
	ACurrentWeapon* CurrentSecondaryWeapon;

	// 快捷切换装备槽
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapons")
	TArray<AWeaponActor*> Weapons;  // 武器槽中的所有武器
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapons")
	int CurrentWeaponID=-1;  // 当前武器的ID，指是几号位的武器

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AmmoInfo")
	int TotalAmmo = 180; // 人物目前持有的剩余子弹量

	// 任务列表
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TaskList")
	TSubclassOf<UTaskComponent> TaskListClass; // 绑定的任务列表C++类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TaskList")
	UTaskComponent* TaskList; // TaskList指针

	// 角色技能组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skills")
	TSubclassOf<USkillComponent> SkillClass; // 绑定的技能组件C++类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skills")
	USkillComponent* SkillComponent;  // Skill组件指针

	// 角色升级系统
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EXP")
	int CurrentLevel = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EXP")
	int32 CurrentExp = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EXP")
	int64 NextLevelRequireExp = 100;
	
private:
	void LevelUp();
};

