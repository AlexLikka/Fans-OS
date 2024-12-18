// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskComponent.h"

// Sets default values for this component's properties
UTaskComponent::UTaskComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTaskComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTaskComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTaskComponent::AddTask(const FString& TaskName, int32 TaskGoal, const FString& TaskReward)
{
	if (TaskName.IsEmpty() || TaskGoal <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Task Parameters for '%s'"), *TaskName);
		return;
	}

	FTask NewTask;
	NewTask.TaskName = TaskName;
	NewTask.TaskGoal = TaskGoal;
	NewTask.TaskReward = TaskReward;
	NewTask.CurrentProgress = 0;

	TaskList.Add(NewTask);

	UE_LOG(LogTemp, Log, TEXT("Task '%s' added with goal: %d, reward: %s"), *TaskName, TaskGoal, *TaskReward);
}

void UTaskComponent::UpdateTask(const FString& TaskName, const int32 ProgressIncrement)
{
	for (FTask& Task : TaskList)
	{
		if (Task.TaskName == TaskName)
		{
			Task.CurrentProgress+=ProgressIncrement;

			if (Task.CurrentProgress >= Task.TaskGoal)
			{
				FinishTask(TaskName);
			}
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Task '%s' not found"), *TaskName);
}

void UTaskComponent::FinishTask(const FString& TaskName)
{
	for (int32 i = 0; i < TaskList.Num(); ++i)
	{
		if (TaskList[i].TaskName == TaskName)
		{
			// 处理奖励逻辑
			FString Reward = TaskList[i].TaskReward;
			UE_LOG(LogTemp, Log, TEXT("Task '%s' completed! Reward: %s"), *TaskName, *Reward);

			// 从任务列表移除
			TaskList.RemoveAt(i);
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Task '%s' not found in FinishTask"), *TaskName);
}

