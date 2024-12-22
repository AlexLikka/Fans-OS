// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "MyCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建碰撞组件
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionProfileName("Projectile");
	RootComponent = CollisionComponent;

	// 创建网格组件
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 确保碰撞由 CollisionComponent 处理

	// 创建移动组件
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->UpdatedComponent = RootComponent;
	ProjectileMovementComponent->InitialSpeed = 3000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;

	// 绑定碰撞事件
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetActor)
	{
		FVector Direction = (TargetActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FVector NewLocation = GetActorLocation() + Direction * ProjectileMovementComponent->MaxSpeed * DeltaTime;
		SetActorLocation(NewLocation);
	}

}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 检查指针是否有效
	if (!HitComp || !OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnHit: Invalid HitComp or OtherActor"));
		return; // 提前返回，避免使用无效指针
	}

	//if (OtherActor && OtherActor != this)
	//{
	//	// 尝试将命中的 Actor 转换为 AEnemy
	//	AMyCharacter* Enemy = Cast<AMyCharacter>(OtherActor);
	//	if (Enemy)
	//	{
	//		// 如果命中的是 AEnemy，则调用其自定义的 ApplyDamage 函数
	//		UE_LOG(LogTemp, Log, TEXT("Bullet hit Enemy: %s"), *Enemy->GetName());
	//		Enemy->ApplyDamage(DamageAmount);
	//		Destroy();
	//		return;
	//	}
	//	// 尝试将命中的Actor转化为ABullet
	//	ABullet* Bullet = Cast<ABullet>(OtherActor);
	//	if (Bullet)
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("Bullet hit Other Bullet: %s"), *Enemy->GetName());
	//		return;
	//	}
	//	// 如果不是上述类，则使用泛型的 ApplyDamage
	//	UE_LOG(LogTemp, Log, TEXT("Bullet hit OtherActor: %s"), *OtherActor->GetName());
	//	// UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, GetInstigatorController(), this, UDamageType::StaticClass());
	//	Destroy();
	//}

	if (!HitComp || !OtherActor || OtherActor == this) return;

	// 检查是否命中敌人
	AMyCharacter* HitEnemy = Cast<AMyCharacter>(OtherActor);
	if (HitEnemy)
	{
		UE_LOG(LogTemp, Log, TEXT("Bullet hit Enemy: %s"), *HitEnemy->GetName());
		HitEnemy->ApplyDamage(DamageAmount);  // 对敌人造成伤害
		Destroy();  // 子弹销毁
		return;
	}

	// 检查是否命中玩家
	AFPS_Fans_OSCharacter* HitPlayer = Cast<AFPS_Fans_OSCharacter>(OtherActor);
	if (HitPlayer)
	{
		UE_LOG(LogTemp, Log, TEXT("Bullet hit Player: %s"), *HitPlayer->GetName());
		HitPlayer->CurrentHealth -= DamageAmount;  // 对玩家扣血
		UE_LOG(LogTemp, Log, TEXT("Player's remaining health: %d"), HitPlayer->CurrentHealth);
		if (HitPlayer->CurrentHealth <= 0)
		{
			UE_LOG(LogTemp, Log, TEXT("Player is dead!"));
			// 可以在这里触发玩家死亡的逻辑，比如显示游戏结束界面
		}
		Destroy();  // 子弹销毁
		return;
	}

	// 如果命中的既不是敌人也不是玩家
	UE_LOG(LogTemp, Log, TEXT("Bullet hit other object: %s"), *OtherActor->GetName());
	Destroy();  // 子弹销毁
}

void ABullet::SetTarget(AActor* Target)
{
	TargetActor = Target;
}