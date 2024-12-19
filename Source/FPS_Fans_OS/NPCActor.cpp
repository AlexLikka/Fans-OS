// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCActor.h"

ANPCActor::ANPCActor()
{
	DialogueTexts = {
		FText::FromString(TEXT("Hello, my friend")),
		FText::FromString(TEXT("How are you today?")),
		FText::FromString(TEXT("Bye!"))
	};
}

void ANPCActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPCActor::BeginPlay()
{
	Super::BeginPlay();

	// 创建并绑定对话框UI
	// 检查是否有绑定的对话框蓝图类
	if (DialogueWidgetClass)
	{
		// 使用蓝图类创建对话框实例
		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
		if (DialogueWidget)
		{
			DialogueWidget->AddToViewport();
			DialogueWidget->HiddenOnScreen(); // 初始隐藏
			DialogueWidget->InitializeDialogue(DialogueTexts); // 初始化对话内容
			UE_LOG(LogTemp, Log, TEXT("DialogueWidget created successfully."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueWidgetClass is not set!"));
	}
}

void ANPCActor::BeginOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MoveDirection = FVector(0.0f, 0.0f, 0.0f);
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, TEXT("NPC: Hello!"));
	ShowDialogue();
}

void ANPCActor::EndOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	MoveDirection = FVector(1.0f, 0.0f, 0.0f);
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, TEXT("NPC: Bye!!"));
	HideDialogue();
}

void ANPCActor::HitFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	MoveDirection = FVector(0.0f, 0.0f, 0.0f);
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, TEXT("NPC: Hello!"));
	ShowDialogue();
}

void ANPCActor::MoveFunction()
{
	//移动：Local相对自身，World相对世界
	FHitResult HitResult;
	AddActorLocalOffset(MoveDirection, false, &HitResult);
}

void ANPCActor::ShowDialogue()
{
	if (DialogueWidget)
	{
		DialogueWidget->ShowOnScreen();
		// 启用鼠标并设置输入模式
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(DialogueWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void ANPCActor::HideDialogue()
{
	if (DialogueWidget)
	{
		DialogueWidget->HiddenOnScreen();
	}
}