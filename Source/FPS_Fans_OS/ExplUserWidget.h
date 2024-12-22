// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExplUserWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class NEWPROJECT_API UExplUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//UI��� �󶨵�CurrentExpBar������
	//�󶨵ľ��������
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> CurrentExpBar;
	// �󶨾����ı���
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentExpTextBlock;

	//���¾������ٷֱ�
	void UpdateCurrentExp(float  CurrentExppercent);
	//���¾���ȼ�
	void UpdateCurrentLevel(int CurrentLevel);

};
