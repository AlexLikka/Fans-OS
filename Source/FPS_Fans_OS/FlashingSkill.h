// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillComponent.h"
#include "FlashingSkill.generated.h"

/**
 * 
 */
UCLASS()
class FPS_FANS_OS_API UFlashingSkill : public USkillComponent
{
	GENERATED_BODY()

public:
	UFlashingSkill();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FlashSkillInfo")
	float FlashDistance = 100.0f;
	
	virtual void OnSkillApply(AFPS_Fans_OSCharacter* Character) override;  // 实现闪现逻辑（这里设置为向前闪现100m
	// 闪现技能不需要技能期间和技能结束后的处理
};
