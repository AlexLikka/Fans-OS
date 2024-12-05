// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrentWeapon.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "WeaponUtils.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"

// Sets default values for this component's properties
ACurrentWeapon::ACurrentWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;
	
}


// Called when the game starts
void ACurrentWeapon::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
		if (CameraManager)
		{
			DefaultFOV = CameraManager->GetFOVAngle();
		}
	}
	
}


void ACurrentWeapon::SetCurrentWeapon(AFPS_Fans_OSCharacter* Character, AWeaponActor* NewWeapon, UWorld* World)
{
	// 确保 NewWeapon 不为空
	if (!NewWeapon || !Character) return;
	

	// 将武器附加到玩家的骨架上
	NewWeapon->AttachToComponent(Character->GetMesh1P(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket"));
	// 设置 Spawn 参数，指定 Owner 为 Character
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Character;
	SpawnParams.Instigator = Character->GetInstigator(); // 可选，根据需求设置
	ACurrentWeapon* Weapon = World->SpawnActor<ACurrentWeapon>(ACurrentWeapon::StaticClass(),
		NewWeapon->GetActorLocation(),
		NewWeapon->GetActorRotation(),
		SpawnParams);
	// UE_LOG(LogTemp, Log, TEXT("BeforeWeaponOwnerActor: %s"), * (Weapon->GetOwner() ? Weapon->GetOwner()->GetName() : TEXT("None")));
	// 复制属性
	WeaponUtils::CopyWeaponProperties(NewWeapon, Weapon);
	Weapon->Ammo = Weapon->MaxAmmo;  // 设置弹夹中的子弹数
	// 更新玩家当前持有的武器
	// UE_LOG(LogTemp, Log, TEXT("WeaponOwnerActor: %s"), * (Weapon->GetOwner() ? Weapon->GetOwner()->GetName() : TEXT("None")));
	Character->CurrentWeapon = Weapon;  // 存储 UCurrentWeapon 组件
	
}

void ACurrentWeapon::Fire()
{
	// 弹夹打空的情况下不允许再开火
	if (Ammo <= 0)
	{
		return;
	}
	// 检查子弹类是否设置
	if (!BulletClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("BulletClass is not set in %s"), *GetName());
		return;
	}

	// 获取拥有者，假设是玩家角色
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentWeapon has no owner!"));
		return;
	}

	// 尝试将拥有者转换为角色类
	AFPS_Fans_OSCharacter* Character = Cast<AFPS_Fans_OSCharacter>(OwnerActor);
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is not of type AFPS_Fans_OSCharacter"));
		return;
	}

	// 获取角色的相机组件
	UCameraComponent* CameraComponent = Character->GetFirstPersonCameraComponent(); // 确保这个函数存在
	if (!CameraComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character has no FirstPersonCameraComponent"));
		return;
	}

	// 获取相机的位置和朝向
	FVector CameraLocation = CameraComponent->GetComponentLocation();
	FRotator CameraRotation = CameraComponent->GetComponentRotation();
	FVector ForwardVector = CameraRotation.Vector();

	// 计算子弹的生成位置（相机位置向前偏移一定距离，避免与角色发生碰撞）
	FVector SpawnLocation = CameraLocation + ForwardVector * 100.0f; // 根据需要调整偏移量

	// 设置生成参数
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerActor;
	SpawnParams.Instigator = Character->GetInstigator();

	// 生成子弹
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, CameraRotation, SpawnParams);
	Bullet->DamageAmount = Damage;
	if (Bullet)
	{
		UE_LOG(LogTemp, Log, TEXT("Bullet spawned: %s"), *Bullet->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Bullet."));
	}

	// 播放射击音效
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, CameraLocation);
	}

	// 扣除当前子弹
	Ammo-=1;
}

void ACurrentWeapon::Reload()
{
	int ToReloadAmmo = MaxAmmo - Ammo;
	AFPS_Fans_OSCharacter* Player =  Cast<AFPS_Fans_OSCharacter>(GetOwner());
	if (Player)
	{
		Player->TotalAmmo -= ToReloadAmmo;
		if (Player->TotalAmmo <= 0)
		{
			ToReloadAmmo += Player->TotalAmmo;
			Player->TotalAmmo = 0;
		}
	}
	Ammo += ToReloadAmmo;
}

void ACurrentWeapon::StartAiming()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	// 获取玩家角色
	AFPS_Fans_OSCharacter* PlayerCharacter = Cast<AFPS_Fans_OSCharacter>(PlayerController->GetPawn());
	if (!PlayerCharacter) return;

	// 创建并显示瞄准UI
	if (ZoomedCrosshairWidgetClass)
	{
		CurrentZoomedCrosshair = CreateWidget<UUserWidget>(PlayerController, ZoomedCrosshairWidgetClass);
		if (CurrentZoomedCrosshair)
		{
			CurrentZoomedCrosshair->AddToViewport();
		}
	}
	
	// 根据放大倍率计算目标 FOV
	ZoomFactor = DefaultFOV / ZoomMultiplier;
	// 使用定时器平滑调整FOV
	GetWorld()->GetTimerManager().SetTimer(ZoomTimerHandle, this, &ACurrentWeapon::ZoomIn, 0.01f, true);

}

void ACurrentWeapon::ZoomIn()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	float CurrentFOV = PlayerController->PlayerCameraManager->GetFOVAngle();
	float NewFOV = FMath::FInterpTo(CurrentFOV, ZoomFactor, GetWorld()->GetDeltaSeconds(), ZoomSpeed);
	PlayerController->PlayerCameraManager->SetFOV(NewFOV);
		
	if (FMath::Abs(NewFOV - ZoomFactor) < 0.1f)
	{
		PlayerController->PlayerCameraManager->SetFOV(ZoomFactor);
		GetWorld()->GetTimerManager().ClearTimer(ZoomTimerHandle);
	}
}

void ACurrentWeapon::CancelAiming()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	// 获取玩家角色
	AFPS_Fans_OSCharacter* PlayerCharacter = Cast<AFPS_Fans_OSCharacter>(PlayerController->GetPawn());
	if (!PlayerCharacter) return;

	// 移除瞄准UI
	if (CurrentZoomedCrosshair)
	{
		CurrentZoomedCrosshair->RemoveFromParent();
		CurrentZoomedCrosshair = nullptr;
	}

	// 使用定时器平滑恢复FOV
	GetWorld()->GetTimerManager().SetTimer(ZoomTimerHandle, this, &ACurrentWeapon::ZoomOut, 0.01f, true);

}

void ACurrentWeapon::ZoomOut()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	float CurrentFOV = PlayerController->PlayerCameraManager->GetFOVAngle();
	float NewFOV = FMath::FInterpTo(CurrentFOV, DefaultFOV, GetWorld()->GetDeltaSeconds(), ZoomSpeed);
	PlayerController->PlayerCameraManager->SetFOV(NewFOV);

	if (FMath::Abs(NewFOV - DefaultFOV) < 0.1f)
	{
		PlayerController->PlayerCameraManager->SetFOV(DefaultFOV);
		GetWorld()->GetTimerManager().ClearTimer(ZoomTimerHandle);
	}
}