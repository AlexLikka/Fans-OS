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
	UFUNCTION(BlueprintCallable, Category = "WeaponAction")
	void Fire();  // 开火动作

	UFUNCTION(BlueprintCallable, Category = "WeaponAction")
	void Reload();  // 换弹动作

	UFUNCTION(BlueprintCallable, Category = "WeaponAction")
	void StartAiming();  // 开镜动作
	UFUNCTION()
	void ZoomIn();  // 开镜处理函数

	UFUNCTION(BlueprintCallable, Category = "WeaponAction")
	void CancelAiming();  // 取消开镜动作
	UFUNCTION()
	void ZoomOut();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CurrentWeaponInfo")
	int Ammo; // 当前弹夹的剩余弹药量

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurrentWeaponInfo")
	bool IsReloading = false; // 当前是否正在执行换弹动作
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurrentWeaponInfo")
	bool IsFiring = false; // 当前是否在开火状态
	
private:
	// 开镜关镜动画参数
	float DefaultFOV = 90.0f; // 假设默认FOV为90
	FTimerHandle ZoomTimerHandle;
	float ZoomSpeed = 2.0f; // 插值速度
};
