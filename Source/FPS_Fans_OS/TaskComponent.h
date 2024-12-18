// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TaskComponent.generated.h"

USTRUCT(BlueprintType)
struct FTask
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Task")
	FString TaskName;  // 任务名称

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Task")
	int32 TaskGoal;  // 任务总目标

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Task")
	int32 CurrentProgress;  // 任务当前进度

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Task")
	FString TaskReward;  // 任务奖励

	FTask()
		: TaskName(TEXT("")),
		  TaskGoal(0),
		  CurrentProgress(0),
		  TaskReward(TEXT("")) {}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_FANS_OS_API UTaskComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTaskComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<FTask> TaskList; // 任务列表

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 添加任务接口
	UFUNCTION(BlueprintCallable, Category = "Task")
	void AddTask(const FString& TaskName, int32 TaskGoal, const FString& TaskReward);

	// 更新任务进度接口（仅限 C++）
	void UpdateTask(const FString& TaskName, const int32 ProgressIncrement);

	// 完成任务方法
	UFUNCTION(BlueprintCallable, Category = "Task")
	void FinishTask(const FString& TaskName);
};
