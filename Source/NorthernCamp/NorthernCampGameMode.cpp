// Copyright Epic Games, Inc. All Rights Reserved.

#include "NorthernCampGameMode.h"
#include "NorthernCampPlayerController.h"
#include "NorthernCampCharacter.h"
#include "UObject/ConstructorHelpers.h"


///////
// The game mode is handling the following:
// Time of day | Resources |
// 
///////
ANorthernCampGameMode::ANorthernCampGameMode()
{
	// use our custom PlayerController class

	

	
}

void ANorthernCampGameMode::AddResourceManager(UResourceManagerComponent* ResourceManager)
{
	if(ResourceManagerComps.Contains(ResourceManager))
	{
		return;
	}
	ResourceManagerComps.Add(ResourceManager);
}

