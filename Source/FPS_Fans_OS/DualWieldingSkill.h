// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillComponent.h"
#include "DualWieldingSkill.generated.h"

/**
 * 
 */
UCLASS()
class FPS_FANS_OS_API UDualWieldingSkill : public USkillComponent
{
	GENERATED_BODY()

public:
	UDualWieldingSkill();
	
	virtual void OnSkillApply(AFPS_Fans_OSCharacter* Character) override;
	virtual void OnSkill(AFPS_Fans_OSCharacter* Character) override;
	virtual void OnSkillEnd(AFPS_Fans_OSCharacter* Character) override;
};
