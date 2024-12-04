// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_Fans_OSGameMode.h"
#include "FPS_Fans_OSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPS_Fans_OSGameMode::AFPS_Fans_OSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
