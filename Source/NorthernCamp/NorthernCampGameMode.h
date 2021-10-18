// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DirectionalLight.h"
#include "GameFramework/GameModeBase.h"
#include "NorthernCampGameMode.generated.h"

UCLASS(minimalapi)
class ANorthernCampGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANorthernCampGameMode();


	uint8 CurrentDayTime;
	uint8 DaysInGame;


	
	//Current time
	//
	//Time speed for 24 hour cycle
		//Sun always sets at 10 and goes up at 6

	//Sun rotation needs to be calculated. 

	//100
	//Every minutes
		//The sun needs to change
		//The character stats need to depleet.

	//Timer for the day time. every half second.

	
};



