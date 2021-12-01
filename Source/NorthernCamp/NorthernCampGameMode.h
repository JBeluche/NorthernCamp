// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/ResourceManagerComponent.h"

#include "GameFramework/GameModeBase.h"
#include "NorthernCampGameMode.generated.h"

UCLASS(minimalapi)
class ANorthernCampGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANorthernCampGameMode();

	void AddResourceManager(UResourceManagerComponent* ResourceManager);
	TArray<UResourceManagerComponent*> ResourceManagerComps;





	
};



