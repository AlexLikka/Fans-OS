// Copyright Epic Games, Inc. All Rights Reserved.

#include "newProjectCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <Game/ThirdPlayerController.h>

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AnewProjectCharacter

AnewProjectCharacter::AnewProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	//// 初始化血量组件
	//HealthComponent = CreateDefaultSubobject<UHealthComponent>("HP");//3
	// 启用Tick
	PrimaryActorTick.bCanEverTick = true;

}

void AnewProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	//初始化更新血条
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("AnewProjectCharacter::BeginPlay()"));//
	AThirdPlayerController* PlayerController = Cast< AThirdPlayerController>(GetController());
	if (PlayerController != nullptr) {
		PlayerController->UpdataHealthPercent(GetHealthPercent());
		PlayerController->UpdateStaminaPercent(GetStaminaPercent());  // 更新体力百分比
		PlayerController->UpdateCurrentExp(GetExpPercent());  // 更新经验条、经验等级
		PlayerController->UpdateCurrentLevel(GetCurrentLevel());  // 更新经验条、经验等级
	}

}

void AnewProjectCharacter::Death_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("Death"));//演示
	
	AThirdPlayerController* PlayerController = Cast<AThirdPlayerController>(GetController());
	if (PlayerController != nullptr) {
		PlayerController->ShowRestartWidget();
	}
}

void AnewProjectCharacter::Damage_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Damage"));//演示
	//在被攻击的时候更新显示血条
	AThirdPlayerController* PlayerController = Cast< AThirdPlayerController>(GetController());
	if (PlayerController != nullptr) {
		PlayerController->UpdataHealthPercent(GetHealthPercent());
	}
}



void  AnewProjectCharacter::LevelUp()
{
	CurrentLevel++;
	CurrentExp -= NextLevelRequireExp;
	NextLevelRequireExp = 100 * CurrentLevel;
	MaxHealth += 10;
	CurrentHealth += 10;
	MaxStamina += 1;
	CurrentStamina += 1;
}

float AnewProjectCharacter::GetHealthPercent() const
{
	return CurrentHealth*1.0f/MaxHealth;
}

float AnewProjectCharacter::GetStaminaPercent() const
{
	return CurrentStamina / MaxStamina;  // 返回体力的百分比
}

float AnewProjectCharacter::GetExpPercent() const
{
	return (CurrentExp*1.0f)/ NextLevelRequireExp;  // 返回如今拥有的经验值与升到下一级经验值的比值
}

int AnewProjectCharacter::GetCurrentLevel() const
{
	return CurrentLevel;
}



void AnewProjectCharacter::Tick(float DeltaTime)
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
	// 更新体力进度条
	AThirdPlayerController* PlayerController = Cast<AThirdPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdataHealthPercent(GetHealthPercent());
		PlayerController->UpdateStaminaPercent(GetStaminaPercent());  // 更新体力百分比
		PlayerController->UpdateCurrentExp(GetExpPercent());  // 更新经验条、经验等级
		PlayerController->UpdateCurrentLevel(GetCurrentLevel());  // 更新经验条、经验等级
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AnewProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AnewProjectCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AnewProjectCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AnewProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AnewProjectCharacter::Look(const FInputActionValue& Value)
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
