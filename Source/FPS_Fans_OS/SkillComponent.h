// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

class AFPS_Fans_OSCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ,Blueprintable)
class FPS_FANS_OS_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	float Cd; // 技能cd
	float Duration; // 技能当前剩余持续时间

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SkillInfo")
	FName SkillName = "Skill1"; // 技能名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SkillInfo")
	float MaxCd = 10.0f; // 技能总CD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SkillInfo")
	float MaxDuration = 0.0f; // 技能持续时间
	// 技能图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInfo")
	UTexture2D* SkillIcon;  // 蓝图中绑定的图标

	UFUNCTION(BlueprintCallable, Category="OnSkillApply")
	virtual void OnSkillApply(AFPS_Fans_OSCharacter* Character); // 技能触发时的逻辑
	UFUNCTION(BlueprintCallable, Category="OnSkill")
	virtual void OnSkill(AFPS_Fans_OSCharacter* Character); // 技能持续期间的逻辑
	UFUNCTION(BlueprintCallable, Category="OnSkillEnd")
	virtual void OnSkillEnd(AFPS_Fans_OSCharacter* Character); // 技能结束时的逻辑

	UFUNCTION(BlueprintCallable, Category="SkillStatus")
	bool CanUseSkillNow(); // 判断当前能否使用技能

	UFUNCTION(BlueprintCallable)
	float GetCd();
};

