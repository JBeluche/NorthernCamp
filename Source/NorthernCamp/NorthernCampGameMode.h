// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/ResourceManagerComponent.h"
#include "Controllers/DayNightActorController.h"

#include "GameFramework/GameModeBase.h"
#include "NorthernCampGameMode.generated.h"

class AResourceController;
UCLASS(minimalapi)
class ANorthernCampGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANorthernCampGameMode();

	void AddResourceManager(UResourceManagerComponent* ResourceManager);
	TArray<UResourceManagerComponent*> ResourceManagerComps;

	AResourceController* ResourceController;
	ADayNightActorController* DayNightController;


protected:
	virtual void BeginPlay() override;

	
};



