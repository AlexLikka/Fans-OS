// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "InteractiveActor.generated.h"

UCLASS()
class FPS_FANS_OS_API AInteractiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
	class USceneComponent* MyScene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
	class UStaticMeshComponent* MyMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
	class UParticleSystemComponent* MyParticle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
	class UBoxComponent* MyBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
	class UAudioComponent* MyAudio;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyClass")
	TSubclassOf<AActor>InteractiveActor;

	UFUNCTION()
	void BeginOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void HitFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void MoveFunction();
	// 反向移动函数
	void ReverseMoveDirection();
private:
	FTimerHandle MoveTimerHandle; // 定时器句柄
	FVector MoveDirection;        // 移动方向
};
