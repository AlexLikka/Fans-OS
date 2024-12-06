#include "DropItem.h"
#include "FPS_Fans_OSCharacter.h"
#include "CurrentWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ADropItem::ADropItem()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	
	// 初始化静态网格组件作为根组件
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;  // 设置静态网格组件为根组件
	
	// 初始化触发器组件
	PickupTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PickupTrigger"));
	PickupTrigger->SetupAttachment(RootComponent);  // 将触发器附加到根组件
	PickupTrigger->SetCapsuleRadius(50.0f);  // 设置触发器的半径
	PickupTrigger->SetCapsuleHalfHeight(100.0f);  // 设置触发器的高度
	PickupTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADropItem::OnPlayerEnterTrigger);  // 绑定触发器事件
}

// Called when the game starts or when spawned
void ADropItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADropItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Spawn掉落物的方法，接收x, y坐标并找到地面的z坐标
void ADropItem::SpawnDropItemOnGround(UWorld* World, FVector2D Location2D)
{
	if (!World) return;

	// 射线检测
	FVector StartLocation = FVector(Location2D.X, Location2D.Y, 10000.0f);
	FVector EndLocation = FVector(Location2D.X, Location2D.Y, -10000.0f);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	// 发射射线
	bool bHit = World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		// 找到碰撞的地面位置，返回z坐标
		FVector GroundLocation = HitResult.Location;

		// 创建掉落物并放置到地面
		ADropItem* DropItem = World->SpawnActor<ADropItem>(ADropItem::StaticClass(), GroundLocation, FRotator::ZeroRotator);
		if (DropItem)
		{
			// 使用 ItemBlueprintClass 生成掉落物的外表 Actor
			ItemActor = World->SpawnActor<AActor>(ItemBlueprintClass, GroundLocation, FRotator::ZeroRotator);
			if (ItemActor)
			{
				// 将生成的 ItemActor 附加到 ADropItem 上
				ItemActor->AttachToActor(DropItem, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}
}

// 玩家进入触发器时的回调
void ADropItem::OnPlayerEnterTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 确保是玩家角色
	if (OtherActor && OtherActor->IsA(AFPS_Fans_OSCharacter::StaticClass())) 
	{
		// 捡起掉落物
		Pickup();
	}
}

// 捡起掉落物
void ADropItem::Pickup()
{
	// 在这里你可以实现捡起逻辑：
	// - 你可以将掉落物添加到玩家的背包中
	// - 或者将其从世界中删除，模拟捡起的动作
	
	// 先解绑触发器事件，防止多次触发
	PickupTrigger->OnComponentBeginOverlap.RemoveDynamic(this, &ADropItem::OnPlayerEnterTrigger);
	AFPS_Fans_OSCharacter* Player = Cast<AFPS_Fans_OSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Player)
	{
		Player->Backpack->AddItemToBackpack(this);  // 将掉落物拾取到背包中（该方法暂未实现）
		
		// 以下是在背包系统未完成的情况下使用的临时代码
		// 生成武器实例，从蓝图类生成
		AWeaponActor* NewWeaponActor = GetWorld()->SpawnActor<AWeaponActor>(ItemBlueprintClass, GetActorLocation(), GetActorRotation());
		if (NewWeaponActor)
		{
			Player->Weapons.Add(NewWeaponActor);
			ACurrentWeapon::ChangeCurrentWeapon(Player, Player->CurrentWeaponID+1);
		}
	}
	// 销毁掉落物（模型）
	Destroy();
	// 销毁掉落物外观模型（ItemActor）
	if (ItemActor)
	{
		ItemActor->Destroy();
	}
}
