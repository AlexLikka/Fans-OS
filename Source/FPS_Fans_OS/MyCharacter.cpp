// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "FPS_Fans_OSCharacter.h"
#include "TaskComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponSocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponSocketMesh"));
	WeaponSocketMesh->SetupAttachment(GetMesh(), "WeaponSocket");



}

void AMyCharacter::ApplyDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	//if (AFPS_Fans_OSCharacter* TargetPlayer = Cast<AFPS_Fans_OSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	//{
	//	FireAtPlayer(TargetPlayer); // 定时攻击玩家
	//}
	
}

void AMyCharacter::Fire() {
	AActor* OwnerActor = GetOwner();
	FVector SoundLocation; // 声音播放位置

	if (OwnerActor)
	{
		AMyCharacter* Character = Cast<AMyCharacter>(OwnerActor);
		if (Character)
		{
			SoundLocation = Character->GetActorLocation(); // 使用角色位置作为声音播放位置
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Character cast failed! OwnerActor is not an AMyCharacter."));
			SoundLocation = GetActorLocation(); // 如果转换失败，则使用当前Actor的位置
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OwnerActor is null!"));
		SoundLocation = GetActorLocation(); // 如果没有Owner，则使用当前Actor的位置
	}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, SoundLocation);
		UE_LOG(LogTemp, Log, TEXT("Playing FireSound at location: %s"), *SoundLocation.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FireSound is not set!"));
	}
}

void AMyCharacter::FireAtPlayer(AFPS_Fans_OSCharacter* TargetPlayer)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerCharacter found in the world!"));
		return;
	}

	// 将玩家角色转换为AFPS_Fans_OSCharacter
	AFPS_Fans_OSCharacter* FPSCharacter = Cast<AFPS_Fans_OSCharacter>(PlayerCharacter);
	if (!FPSCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter is not of type AFPS_Fans_OSCharacter! Actual type: %s"), *PlayerCharacter->GetClass()->GetName());
		return;
	}

	// 确定子弹生成位置和方向
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;  // 子弹从敌人位置生成
	FRotator SpawnRotation = (FPSCharacter->GetActorLocation() - SpawnLocation).Rotation();  // 指向玩家
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;


	

	// 生成子弹
	if (!BulletClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("BulletClass not set!"));
		return;
	}

	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams);

	UE_LOG(LogTemp, Log, TEXT("SpawnLocation: %s, SpawnRotation: %s"), *SpawnLocation.ToString(), *SpawnRotation.ToString());
	if (Bullet&&Bullet->num>=0)
	{
		UE_LOG(LogTemp, Log, TEXT("Bullet fired at player!"));
		Bullet->num -= 1;
		FPSCharacter->CurrentHealth -= 1;



		Fire();


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn bullet!"));
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsDead())
	{
		Dead();
	}
}
void AMyCharacter::Dead()
{
	// 尝试更新击杀任务
	UpdateKillingEnemyTask();

	// 生成掉落物
	SpawnDropItems();

	// 给予玩家经验
	UpdatePlayerExp();

	// 触发死亡动画或其他逻辑
	TriggerDeathAnimation();

	// 销毁敌人角色
	Destroy();

}

bool AMyCharacter::IsDead()
{
	return CurrentHealth <= 0;
}
// 生成掉落物的方法
void AMyCharacter::SpawnDropItems()
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
void AMyCharacter::TriggerDeathAnimation()
{
	// 在这里可以添加死亡动画的代码，或者其他死亡逻辑
	// 比如播放死亡动画、掉落物等
}

void AMyCharacter::UpdateKillingEnemyTask()
{
	AFPS_Fans_OSCharacter* Character = Cast<AFPS_Fans_OSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Character)
	{
		FString TaskName = FString::Printf(TEXT("Kill %s"), *Name.ToString());
		Character->TaskList->UpdateTask(TaskName, 1);
	}
}

void AMyCharacter::UpdatePlayerExp()
{
	AFPS_Fans_OSCharacter* Character = Cast<AFPS_Fans_OSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Character)
	{
		Character->CurrentExp += Exp;
	}
}

