// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent.h"
#include "FPS_Fans_OSCharacter.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (Duration > 0.0f) // 在技能持续期间，CD不冷却
	{
		Duration -= DeltaTime;
		AFPS_Fans_OSCharacter* Player = Cast<AFPS_Fans_OSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		OnSkill(Player); // 技能持续期间，每Tick执行该函数
		if (Duration < 0.0f)
		{
			// 技能结束后，调用一次技能结束函数
			Duration = 0.0f;
			OnSkillEnd(Player);
		}
		return;
	}
	if (Cd > 0.0f)
	{
		Cd -= DeltaTime; // 减去本帧经过的时间
		if (Cd < 0.0f)
		{
			Cd = 0.0f; // 防止冷却时间为负值
		}
		UE_LOG(LogTemp, Log, TEXT("当前CD：%f"), Cd);
	}
}

void USkillComponent::OnSkillApply(AFPS_Fans_OSCharacter* Character)
{
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character is null"));
		return;
	}
	Cd = MaxCd; // 让技能进入CD
	Duration = MaxDuration; // 进入技能持续状态
}

void USkillComponent::OnSkill(AFPS_Fans_OSCharacter* Character)
{
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character is null"));
		return;
	}
}

void USkillComponent::OnSkillEnd(AFPS_Fans_OSCharacter* Character)
{
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character is null"));
		return;
	}
}

bool USkillComponent::CanUseSkillNow()
{
	return Cd == 0;
}

float USkillComponent::GetCd()
{
	return Cd;
}

