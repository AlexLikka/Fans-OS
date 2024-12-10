// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponActor.h"
#include "CurrentWeapon.h"

/**
 * 
 */
class FPS_FANS_OS_API WeaponUtils
{
public:
	WeaponUtils();
	~WeaponUtils();

	/**
	 * 复制源武器的属性到目标武器
	 * @param Source 源武器对象（AWeaponActor*）
	 * @param Dest 目标武器对象（ACurrentWeapon*）
	 */
	static void CopyWeaponProperties(AWeaponActor* Source, ACurrentWeapon* Dest);
};
