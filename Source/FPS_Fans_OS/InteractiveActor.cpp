// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActor.h"

// Sets default values
AInteractiveActor::AInteractiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyCustomScene"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyCustomStaticMesh"));
	MyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyCustomParticleSystem"));
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyCustomBox"));
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MyCustomAudio"));

	//���Ӽ���ϵ����
	RootComponent = MyScene;
	MyMesh->SetupAttachment(MyScene);
	MyParticle->SetupAttachment(MyScene);
	MyBox->SetupAttachment(MyScene);
	MyAudio->SetupAttachment(MyBox);

	//������Դ��Ϊ��̬�;�̬
	//��̬���ط�Ϊ��̬������Դ�;�̬������Դ��(����д�ڹ��캯����)
	//��̬������Դ��
	static ConstructorHelpers::FObjectFinder<UStaticMesh>TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	MyMesh->SetStaticMesh(TempStaticMesh.Object); //����ģ��
	static ConstructorHelpers::FObjectFinder<UParticleSystem>TempParticleSystem(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	MyParticle->SetTemplate(TempParticleSystem.Object); //����������Ч
	static ConstructorHelpers::FObjectFinder<USoundWave>TempSoundWave(TEXT("/Script/Engine.SoundWave'/Game/StarterContent/Audio/Collapse01.Collapse01'"));
	MyAudio->SetSound(TempSoundWave.Object);

	//��̬������Դ�ࣺ
	static ConstructorHelpers::FClassFinder<AActor>TempMyActor(TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight_C'"));
	InteractiveActor = TempMyActor.Class;


	//��ײ����
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

	////��̬������Դ��Load
	//UStaticMesh* MyTempStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	//if (MyTempStaticMesh)
	//{
	//	MyMesh->SetStaticMesh(MyTempStaticMesh);
	//}
	////��̬������
	//UClass* MyTempClass = LoadClass<AActor>(this, TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_Effect_Steam.Blueprint_Effect_Steam_C'"));
	//if (MyTempClass)
	//{
	//	AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(MyTempClass, FVector::ZeroVector, FRotator::ZeroRotator);
	//}
	// 
	//�ص�������
	MyBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveActor::BeginOverlapFunction);
	MyBox->OnComponentEndOverlap.AddDynamic(this, &AInteractiveActor::EndOverlapFunction);
	//hit������
	MyBox->OnComponentHit.AddDynamic(this, &AInteractiveActor::HitFunction);

	//����box��С
	MyBox->SetBoxExtent(FVector(64, 64, 64));
}

// Called every frame
void AInteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//�ƶ���Local���������World�������
	FVector MyOffset = FVector(1, 0, 0);
	FHitResult HitResult;
	AddActorLocalOffset(MyOffset, false, &HitResult);
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

