// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCActor.h"

void ANPCActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPCActor::BeginOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MoveDirection = FVector(0.0f, 0.0f, 0.0f);
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, TEXT("NPC: Hello!"));

}

void ANPCActor::EndOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	MoveDirection = FVector(1.0f, 0.0f, 0.0f);
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, TEXT("NPC: Bye!!"));
}

void ANPCActor::HitFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	MoveDirection = FVector(0.0f, 0.0f, 0.0f);
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, TEXT("NPC: Hello!"));
}

void ANPCActor::MoveFunction()
{
	//移动：Local相对自身，World相对世界
	FHitResult HitResult;
	AddActorLocalOffset(MoveDirection, false, &HitResult);
}
