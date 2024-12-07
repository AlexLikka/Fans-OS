// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponUtils.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"

WeaponUtils::WeaponUtils()
{
}

WeaponUtils::~WeaponUtils()
{
}

void WeaponUtils::CopyWeaponProperties(AWeaponActor* Source, ACurrentWeapon* Dest)
{
	if (!Source || !Dest)
	{
		UE_LOG(LogTemp, Warning, TEXT("CopyWeaponProperties: Source or Dest is null."));
		return;
	}

	// 获取基类（AWeaponActor）的 UClass
	UClass* BaseClass = AWeaponActor::StaticClass();

	// 遍历基类中的所有属性，包括继承的属性
	for (TFieldIterator<FProperty> PropIt(BaseClass, EFieldIteratorFlags::IncludeSuper); PropIt; ++PropIt)
	{
		FProperty* SourceProperty = *PropIt;

		// 排除 Owner 属性
		if (SourceProperty->GetName() == "Owner" || SourceProperty->GetName() == "MeshComponent")
		{
			continue;
		}

		// 在目标类中查找同名属性
		FProperty* DestProperty = Dest->GetClass()->FindPropertyByName(SourceProperty->GetFName());

		// 检查目标属性是否存在且类型相同
		if (DestProperty && DestProperty->SameType(SourceProperty))
		{
			// 获取源属性的值指针
			void* SourceValuePtr = SourceProperty->ContainerPtrToValuePtr<void>(Source);
			// 获取目标属性的值指针
			void* DestValuePtr = DestProperty->ContainerPtrToValuePtr<void>(Dest);

			// 复制属性值
			DestProperty->CopyCompleteValue(DestValuePtr, SourceValuePtr);
		}
		else
		{
			if (!DestProperty)
			{
				UE_LOG(LogTemp, Warning, TEXT("Property %s not found in destination class."), *SourceProperty->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Property %s type mismatch between source and destination."), *SourceProperty->GetName());
			}
		}
	}

	// 手动复制 Mesh 相关属性到 CurrentWeaponMesh
	if (Source->MeshComponent && Dest->CurrentWeaponMesh)
	{
		USkeletalMesh* SourceMesh = Source->MeshComponent->GetSkeletalMeshAsset();
		if (SourceMesh)
		{
			Dest->CurrentWeaponMesh->SetSkeletalMesh(SourceMesh);
			UE_LOG(LogTemp, Log, TEXT("CopyWeaponProperties: Set SkeletalMesh %s to Destination Weapon %s"), *SourceMesh->GetName(), *Dest->GetName());
		}

		// 复制材料
		for (int32 i = 0; i < Source->MeshComponent->GetNumMaterials(); ++i)
		{
			UMaterialInterface* Material = Source->MeshComponent->GetMaterial(i);
			if (Material && Dest->CurrentWeaponMesh->GetNumMaterials() > i)
			{
				Dest->CurrentWeaponMesh->SetMaterial(i, Material);
				UE_LOG(LogTemp, Log, TEXT("CopyWeaponProperties: Set Material %s on Destination Weapon %s"), *Material->GetName(), *Dest->GetName());
			}
		}
	}
}