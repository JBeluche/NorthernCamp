// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/Actors/BuildingBaseActor.h"

// Sets default values
ABuildingBaseActor::ABuildingBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	BuildingActionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Action radius"));
	ResourceManagerComp = CreateDefaultSubobject<UResourceManagerComponent>(TEXT("Resource Manager"));
	
	BuildingActionRadius->SetupAttachment(RootComponent);
	AddOwnedComponent(ResourceManagerComp);

}

// Called when the game starts or when spawned
void ABuildingBaseActor::BeginPlay()
{
	Super::BeginPlay();
	

	ResourcesStoredInBuilding.Add(EResourceType::Water, StartingWater);
	/*
	for (auto& Elem : ResourcesStoredInBuilding)
	{
		if(Elem.Key == EResourceType::Water && Elem.Value >= 1)
		{
			ResourcesStoredInBuilding.Emplace(Elem.Key, (Elem.Value - 1));
			UE_LOG(LogTemp, Warning, TEXT("KEY: %f | VALUE: %i"), Elem.Key, Elem.Value);
			break;
		}
	}*/

	
}

bool ABuildingBaseActor::ExtractRersouce(EResourceType ResourceType, int32 Amount)
{
	for (const TPair<EResourceType, int32>& Pair : ResourcesStoredInBuilding)
	{
		if(Pair.Key == ResourceType && Pair.Value >= Amount)
		{
			ResourcesStoredInBuilding.Emplace(Pair.Key, (Pair.Value - Amount));
			UE_LOG(LogTemp, Warning, TEXT("Took water from building, current water: %i"), Pair.Value);
			
			return true;
			break;
		}
	}
	
	return false;
}

bool ABuildingBaseActor::CheckResourceAvailability(EResourceType ResourceType, int32 Amount)
{
	for (const TPair<EResourceType, int32>& Pair : ResourcesStoredInBuilding)
	{
		if(Pair.Key == ResourceType && Pair.Value >= Amount)
		{
			return true;
		}
	}
	return false;
}

