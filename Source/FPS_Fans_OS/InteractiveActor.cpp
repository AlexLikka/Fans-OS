// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActor.h"

// Sets default values
AInteractiveActor::AInteractiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveDirection = FVector(1, 0, 0);

	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyCustomScene"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyCustomStaticMesh"));
	MyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyCustomParticleSystem"));
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyCustomBox"));
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MyCustomAudio"));

	//父子级关系设置
	RootComponent = MyScene;
	MyMesh->SetupAttachment(MyScene);
	MyParticle->SetupAttachment(MyScene);
	MyBox->SetupAttachment(MyScene);
	MyAudio->SetupAttachment(MyBox);

	//加载资源分为动态和静态
	//静态加载分为静态加载资源和静态加载资源类(必须写在构造函数内)
	//静态加载资源：
	static ConstructorHelpers::FObjectFinder<UStaticMesh>TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	MyMesh->SetStaticMesh(TempStaticMesh.Object); //设置模型
	static ConstructorHelpers::FObjectFinder<UParticleSystem>TempParticleSystem(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	MyParticle->SetTemplate(TempParticleSystem.Object); //设置粒子特效
	static ConstructorHelpers::FObjectFinder<USoundWave>TempSoundWave(TEXT("/Script/Engine.SoundWave'/Game/StarterContent/Audio/Collapse01.Collapse01'"));
	MyAudio->SetSound(TempSoundWave.Object);

	//静态加载资源类：
	static ConstructorHelpers::FClassFinder<AActor>TempMyActor(TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight_C'"));
	InteractiveActor = TempMyActor.Class;


	//碰撞设置
	MyBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MyBox->SetCollisionObjectType(ECC_WorldDynamic);
	MyBox->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
	if (MyParticle)
	{
		MyParticle->Deactivate();
	}
	if (InteractiveActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("MyActorCreated!"));
	}

	////动态加载资源：Load
	//UStaticMesh* MyTempStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	//if (MyTempStaticMesh)
	//{
	//	MyMesh->SetStaticMesh(MyTempStaticMesh);
	//}
	////动态加载类
	//UClass* MyTempClass = LoadClass<AActor>(this, TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_Effect_Steam.Blueprint_Effect_Steam_C'"));
	//if (MyTempClass)
	//{
	//	AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(MyTempClass, FVector::ZeroVector, FRotator::ZeroRotator);
	//}
	// 
	//重叠代理绑定
	MyBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveActor::BeginOverlapFunction);
	MyBox->OnComponentEndOverlap.AddDynamic(this, &AInteractiveActor::EndOverlapFunction);
	//hit代理绑定
	MyBox->OnComponentHit.AddDynamic(this, &AInteractiveActor::HitFunction);

	//设置box大小
	MyBox->SetBoxExtent(FVector(64, 64, 64));

	GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &AInteractiveActor::ReverseMoveDirection, 3.0f, true);
}

// Called every frame
void AInteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveFunction();
}

void AInteractiveActor::BeginOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("hit"));
	MyParticle->Activate();
}

void AInteractiveActor::EndOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("Over"));
	MyParticle->Deactivate();
}

void AInteractiveActor::HitFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("Hit"));
}

void AInteractiveActor::MoveFunction()
{
	//移动：Local相对自身，World相对世界
	FHitResult HitResult;
	AddActorLocalOffset(MoveDirection, false, &HitResult);
}

void AInteractiveActor::ReverseMoveDirection()
{
	MoveDirection *= -1;

	//// 打印当前移动方向（用于调试）
	//UE_LOG(LogTemp, Warning, TEXT("Move Direction Reversed: %s"), *MoveDirection.ToString());
}

