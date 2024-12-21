// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Enemy.h"
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
	
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
					UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 检查指针是否有效
	if (!HitComp || !OtherActor || !OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnHit: Invalid HitComp, OtherActor, or OtherComp"));
		return; // 提前返回，避免使用无效指针
	}
	
	if (OtherActor && OtherActor != this)
	{
		// 尝试将命中的 Actor 转换为 AEnemy
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		if (Enemy)
		{
			// 如果命中的是 AEnemy，则调用其自定义的 ApplyDamage 函数
			UE_LOG(LogTemp, Log, TEXT("Bullet hit Enemy: %s"), *Enemy->GetName());
			Enemy->ApplyDamage(DamageAmount);
			Destroy();
			return;
		}
		// 尝试将命中的Actor转化为ABullet
		ABullet* Bullet = Cast<ABullet>(OtherActor);
		if (Bullet)
		{
			UE_LOG(LogTemp, Log, TEXT("Bullet hit Other Bullet: %s"), *Enemy->GetName());
			return;
		}
		// 如果不是上述类，则使用泛型的 ApplyDamage
		UE_LOG(LogTemp, Log, TEXT("Bullet hit OtherActor: %s"), *OtherActor->GetName());
		// UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, GetInstigatorController(), this, UDamageType::StaticClass());
		if (this)
			Destroy();
	}
}