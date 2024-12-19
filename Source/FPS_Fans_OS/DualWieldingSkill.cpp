// Fill out your copyright notice in the Description page of Project Settings.


#include "DualWieldingSkill.h"

#include "FPS_Fans_OSCharacter.h"
#include "WeaponUtils.h"

UDualWieldingSkill::UDualWieldingSkill()
{
	SkillName = "DualWeapons";
	MaxCd = 60.0f;
	MaxDuration = 10.0f;
}

void UDualWieldingSkill::OnSkillApply(AFPS_Fans_OSCharacter* Character)
{
	int SecondaryWeaponId = Character->CurrentWeaponID == 0 ? 1 : 0;
    if (!Character->Weapons.IsValidIndex(SecondaryWeaponId)) // 如果要取用的副手武器不存在，则直接退出，技能取消执行
    {
    	UE_LOG(LogTemp, Warning, TEXT("SecondaryWeaponId : %d is out of bounds."), SecondaryWeaponId);
    	return;
    }
	Super::OnSkillApply(Character);
	
	AWeaponActor* SecondaryWeapon = Character->Weapons[SecondaryWeaponId];

	SecondaryWeapon->SetActorHiddenInGame(false);
	SecondaryWeapon->AttachToComponent(Character->GetMesh1P(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("SecondaryWeaponSocket"));

	// 设置 Spawn 参数，指定 Owner 为 Character
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Character;
	SpawnParams.Instigator = Character->GetInstigator(); // 可选，根据需求设置
	ACurrentWeapon* Weapon = GetWorld()->SpawnActor<ACurrentWeapon>(ACurrentWeapon::StaticClass(),
		SecondaryWeapon->GetActorLocation(),
		SecondaryWeapon->GetActorRotation(),
		SpawnParams);

	// 复制属性
	WeaponUtils::CopyWeaponProperties(SecondaryWeapon, Weapon);

	Character->CurrentSecondaryWeapon = Weapon;  // 存储 UCurrentWeapon 组件

	// 技能效果，将两把枪的弹药都布满
	Character->CurrentSecondaryWeapon->Ammo = Character->CurrentSecondaryWeapon->MaxAmmo;
	Character->CurrentWeapon->Ammo = Character->CurrentWeapon->MaxAmmo;
}

void UDualWieldingSkill::OnSkill(AFPS_Fans_OSCharacter* Character)
{
	Super::OnSkill(Character);

	// 技能持续期间，无限子弹
	Character->CurrentWeapon->Ammo = Character->CurrentWeapon->MaxAmmo;
	Character->CurrentSecondaryWeapon->Ammo = Character->CurrentSecondaryWeapon->MaxAmmo;
}

void UDualWieldingSkill::OnSkillEnd(AFPS_Fans_OSCharacter* Character)
{
	Super::OnSkillEnd(Character);
	
	ACurrentWeapon* CurrentSecondaryWeapon = Character->CurrentSecondaryWeapon;
	
	int SecondaryWeaponId = Character->CurrentWeaponID == 0 ? 1 : 0;
	AWeaponActor* SecondaryWeapon = Character->Weapons[SecondaryWeaponId];
	SecondaryWeapon->SetActorHiddenInGame(true);
	SecondaryWeapon->Ammo = CurrentSecondaryWeapon->Ammo;

	CurrentSecondaryWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	UE_LOG(LogTemp, Log, TEXT("Detached weapon: %s from character: %s"), 
		*CurrentSecondaryWeapon->GetName(), *Character->GetName());
	CurrentSecondaryWeapon->Destroy();

	Character->CurrentSecondaryWeapon = nullptr;
}
