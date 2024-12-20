// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionNPCActor.h"

AMissionNPCActor::AMissionNPCActor()
{
	DialogueTexts = {
		FText::FromString(TEXT("Oi!Come here!")),
		FText::FromString(TEXT("I think you might be interested in this.")),
		FText::FromString(TEXT("There are 2 enemies out there.")),
		FText::FromString(TEXT("I would appreciate it if you could send them to heaven.")),
		FText::FromString(TEXT("I know you can do it right?")),
		FText::FromString(TEXT("Alright.")),
		FText::FromString(TEXT("That's great!")),
	};
	
}
