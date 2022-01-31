// Copyright Epic Games, Inc. All Rights Reserved.

#include "NorthernCampGameMode.h"

#include "EngineUtils.h"
#include "NorthernCampPlayerController.h"
#include "NorthernCampCharacter.h"
#include "UObject/ConstructorHelpers.h"


///////
// The game mode is handling the following:
// 
// 
///////
ANorthernCampGameMode::ANorthernCampGameMode()
{
	
	
	

	
}

void ANorthernCampGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("Game mode awakes"));

	if(GetWorld())
	{
		for (TActorIterator<ADayNightActorController> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
		{ 
			DayNightController = Cast<ADayNightActorController>(*ActorItr); 
		}
	
		for (TActorIterator<AResourceController> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
		{ 
			ResourceController = Cast<AResourceController>(*ActorItr);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game mode: I cantget the world!"));
	}
}

void ANorthernCampGameMode::AddResourceManager(UResourceManagerComponent* ResourceManager)
{
	if(ResourceManagerComps.Contains(ResourceManager))
	{
		return;
	}
	ResourceManagerComps.Add(ResourceManager);
}

