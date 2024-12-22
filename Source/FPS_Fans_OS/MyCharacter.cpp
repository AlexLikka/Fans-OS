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
	//	FireAtPlayer(TargetPlayer); // ��ʱ�������
	//}
	
}

void AMyCharacter::Fire() {
	AActor* OwnerActor = GetOwner();
	FVector SoundLocation; // ��������λ��

	if (OwnerActor)
	{
		AMyCharacter* Character = Cast<AMyCharacter>(OwnerActor);
		if (Character)
		{
			SoundLocation = Character->GetActorLocation(); // ʹ�ý�ɫλ����Ϊ��������λ��
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Character cast failed! OwnerActor is not an AMyCharacter."));
			SoundLocation = GetActorLocation(); // ���ת��ʧ�ܣ���ʹ�õ�ǰActor��λ��
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OwnerActor is null!"));
		SoundLocation = GetActorLocation(); // ���û��Owner����ʹ�õ�ǰActor��λ��
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

	// ����ҽ�ɫת��ΪAFPS_Fans_OSCharacter
	AFPS_Fans_OSCharacter* FPSCharacter = Cast<AFPS_Fans_OSCharacter>(PlayerCharacter);
	if (!FPSCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter is not of type AFPS_Fans_OSCharacter! Actual type: %s"), *PlayerCharacter->GetClass()->GetName());
		return;
	}

	// ȷ���ӵ�����λ�úͷ���
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;  // �ӵ��ӵ���λ������
	FRotator SpawnRotation = (FPSCharacter->GetActorLocation() - SpawnLocation).Rotation();  // ָ�����
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;


	

	// �����ӵ�
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
	// ���Ը��»�ɱ����
	UpdateKillingEnemyTask();

	// ���ɵ�����
	SpawnDropItems();

	// ������Ҿ���
	UpdatePlayerExp();

	// �������������������߼�
	TriggerDeathAnimation();

	// ���ٵ��˽�ɫ
	Destroy();

}

bool AMyCharacter::IsDead()
{
	return CurrentHealth <= 0;
}
// ���ɵ�����ķ���
void AMyCharacter::SpawnDropItems()
{
	if (DropItemBlueprintClasses.Num() == 0) return;

	// ��ȡ���˵�ǰλ��
	FVector EnemyLocation = GetActorLocation();

	// Ϊÿ���������������λ��
	for (int32 i = 0; i < DropItemBlueprintClasses.Num(); i++)
	{
		// ��ȡ��ǰ���������ͼ��
		TSubclassOf<AActor> ItemBlueprintClass = DropItemBlueprintClasses.IsValidIndex(i) ? DropItemBlueprintClasses[i] : nullptr;

		if (ItemBlueprintClass)
		{
			// �ڵ���λ�ø������һ����
			FVector2D RandomOffset = FMath::RandPointInCircle(100.0f); // 200�ǰ뾶�����Ը����������
			FVector2D SpawnLocation2D = FVector2D(EnemyLocation.X + RandomOffset.X, EnemyLocation.Y + RandomOffset.Y);

			// ����ADropItem����
			ADropItem* DropItem = GetWorld()->SpawnActor<ADropItem>(ADropItem::StaticClass(), EnemyLocation, FRotator::ZeroRotator);
			if (DropItem)
			{
				// ���� SpawnDropItemOnGround �������ɵ�����
				DropItem->ItemBlueprintClass = ItemBlueprintClass;  // ������ͼ��
				DropItem->SpawnDropItemOnGround(GetWorld(), SpawnLocation2D);  // ���ɵ�����
			}
		}
	}
}

// �������������������߼�
void AMyCharacter::TriggerDeathAnimation()
{
	// ���������������������Ĵ��룬�������������߼�
	// ���粥�������������������
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

