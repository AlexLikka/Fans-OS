// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_Fans_OSCharacter.h"
#include "FPS_Fans_OSProjectile.h"
#include "Blueprint/UserWidget.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "SkillComponent.h"
#include "TaskComponent.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AFPS_Fans_OSCharacter

AFPS_Fans_OSCharacter::AFPS_Fans_OSCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AFPS_Fans_OSCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	// 初始化背包类
	if (BackpackClass)
	{
		// 实例化背包类
		Backpack = NewObject<UBackpack>(this, BackpackClass);
		if (Backpack)
		{
			// 将 APlayer 的 BackpackUI 绑定到 Backpack 组件的 BackpackUIClass
			Backpack->RegisterComponent();
			Backpack->BackpackUIClass = BackpackUI;
		}
	}
	// 初始化任务列表类
	if (TaskListClass)
	{
		// 实例化任务列表
		TaskList = NewObject<UTaskComponent>(this, TaskListClass);
		if (TaskList)
		{
			// ...
			TaskList->RegisterComponent();
			TaskList->AddTask("Kill enemy1", 2, "Nothing");  // 随便添加一个任务，用作测试
		}
	}
	// 初始化角色技能组件类
	if (SkillClass)
	{
		// 实例化技能组件
		SkillComponent = NewObject<USkillComponent>(this, SkillClass);
		if (SkillComponent)
		{
			// ...
			// 将组件注册到角色的组件系统中
			SkillComponent->RegisterComponent();
		}
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AFPS_Fans_OSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPS_Fans_OSCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPS_Fans_OSCharacter::Look);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AFPS_Fans_OSCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPS_Fans_OSCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFPS_Fans_OSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 检查是否正在疾跑
	if (IsSpring)
	{
		// 体力消耗
		CurrentStamina -= DeltaTime * 10.0f;  // 体力消耗速度，随你需求调整
		if (CurrentStamina < 0.0f)
		{
			CurrentStamina = 0.0f;  // 防止体力变成负数
		}
	}
	else
	{
		// 体力恢复
		CurrentStamina += DeltaTime * 10.0f;  // 体力恢复速度
		if (CurrentStamina >= MaxStamina)
		{
			CurrentStamina = MaxStamina;  // 防止体力超过最大值
		}
	}

	// 如果体力耗尽，无法疾跑
	if (CurrentStamina <= 0.0f)
	{
		IsSpring = false;  // 取消疾跑
		CanSpring = false;  // 禁止疾跑
	}
	if (CurrentStamina >= 100.0f)
	{
		CanSpring = true;
	}

	if (CurrentExp >= NextLevelRequireExp)
	{
		LevelUp();
	}
}

void AFPS_Fans_OSCharacter::LevelUp()
{
	CurrentLevel++;
	CurrentExp -= NextLevelRequireExp;
	NextLevelRequireExp = 100*CurrentLevel;
	MaxHealth += 10;
	CurrentHealth += 10;
	MaxStamina += 1;
	CurrentStamina+= 1;
}