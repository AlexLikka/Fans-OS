#pragma once

#include "CoreMinimal.h"
#include "FPS_Fans_OSCharacter.h"
#include "WeaponActor.h"  // 包含你的自定义类头文件
#include "Components/ActorComponent.h"
#include "CurrentWeapon.generated.h"

UCLASS(Blueprintable)
class FPS_FANS_OS_API ACurrentWeapon : public AWeaponActor  // 修改继承自 AWeaponActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ACurrentWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	static void SetCurrentWeapon(AFPS_Fans_OSCharacter* Character, AWeaponActor* NewWeapon, UWorld* World);
	// 射击方法，暴露给蓝图调用
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();
};
