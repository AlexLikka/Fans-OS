// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashingSkill.h"
#include "FPS_Fans_OSCharacter.h"

UFlashingSkill::UFlashingSkill()
{
	SkillName = "Flashing";
	MaxCd = 10.0f;
	MaxDuration = 0.0f;
}

void UFlashingSkill::OnSkillApply(AFPS_Fans_OSCharacter* Character)
{
	Super::OnSkillApply(Character);
	
	const float BlinkDistance = FlashDistance * 10; // (单位是厘米,所以乘以10)
	
	// 获取角色的朝向
	FVector ForwardVector = Character->GetActorForwardVector();

	// 计算闪现的目标点
	FVector StartLocation = Character->GetActorLocation();
	FVector EndLocation = StartLocation + ForwardVector * BlinkDistance;

	// 射线检测（从角色当前位置到目标位置）
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Character); // 忽略自身

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		StartLocation, 
		EndLocation, 
		ECC_Visibility, 
		QueryParams
	);

	FVector FinalLocation = EndLocation; // 默认目标位置为计算的目标点

	if (bHit)
	{
		// 如果检测到障碍物，将目标位置设置为障碍物前一点
		FinalLocation = HitResult.ImpactPoint - ForwardVector * 10.0f; // 留10厘米缓冲
		UE_LOG(LogTemp, Log, TEXT("Hit obstacle, adjusting location to: %s"), *FinalLocation.ToString());
	}

	// 更新角色的位置
	Character->SetActorLocation(FinalLocation, false, nullptr, ETeleportType::TeleportPhysics);

	// 调试绘制（可选）
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 2.0f);
	if (bHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 12, FColor::Red, false, 2.0f);
	}
}
