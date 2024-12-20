// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
//#include "Interface/HealthInterface.h"//
#include "newProjectCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

//class UHealthComponent;//1

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AnewProjectCharacter : public ACharacter 
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UCameraComponent>FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UInputMappingContext >DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UInputAction> LookAction;

public:
	AnewProjectCharacter();
	virtual void Tick(float DeltaTime) override;


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicInformation")
	int CurrentHealth = 100;  // ��ǰ����ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicInformation")
	int MaxHealth = 100;  // ��ǰ����ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicInformation")
	float CurrentStamina = 100; // ����ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicInformation")
	float MaxStamina = 100; // ����ֵ

	// ��ɫ����ϵͳ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EXP")
	int CurrentLevel = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EXP")
	int32 CurrentExp = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EXP")
	int64 NextLevelRequireExp = 100;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//����������
	void Death_Implementation() ;
	void Damage_Implementation() ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerActionStatus")
	bool IsSpring = false;  // �����Ƿ��ڼ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicStatus")
	bool CanMove = true; // �����Ƿ�����ƶ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBasicStatus")
	bool CanSpring = true; // �����Ƿ���Լ���


	//���ڽ�ɫ��������ֵ
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	float GetStaminaPercent() const;
	UFUNCTION(BlueprintCallable, Category = "Exp")
	float GetExpPercent() const;
	UFUNCTION(BlueprintCallable, Category = "Exp")
	int GetCurrentLevel() const;
private:
	void LevelUp();
};

