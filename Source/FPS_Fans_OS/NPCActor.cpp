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

	// �������󶨶Ի���UI
	// ����Ƿ��а󶨵ĶԻ�����ͼ��
	if (DialogueWidgetClass)
	{
		// ʹ����ͼ�ഴ���Ի���ʵ��
		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
		if (DialogueWidget)
		{
			DialogueWidget->AddToViewport();
			DialogueWidget->HiddenOnScreen(); // ��ʼ����
			DialogueWidget->InitializeDialogue(DialogueTexts); // ��ʼ���Ի�����
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
	//�ƶ���Local�������World�������
	FHitResult HitResult;
	AddActorLocalOffset(MoveDirection, false, &HitResult);
}

void ANPCActor::ShowDialogue()
{
	if (DialogueWidget)
	{
		DialogueWidget->ShowOnScreen();
		// ������겢��������ģʽ
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