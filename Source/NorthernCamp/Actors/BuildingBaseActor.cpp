// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/Actors/BuildingBaseActor.h"

#include "Components/SleepingSpot.h"
#include "Components/WorkingSpot.h"
#include "NorthernCamp/Characters/CharacterSettler.h"

// Sets default values
ABuildingBaseActor::ABuildingBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ResourceManagerComp = CreateDefaultSubobject<UResourceManagerComponent>(TEXT("Resource Manager"));

}

// Called when the game starts or when spawned
void ABuildingBaseActor::BeginPlay()
{
	Super::BeginPlay();

	//ResourceManagerComp->AddStorage(FName("Main Storage"), EResourceType::All, 200);

	
	TInlineComponentArray<USleepingSpot*> SlepingSpotscomponents;
	TInlineComponentArray<UWorkingSpot*> WorkingSpotscomponents;
	GetComponents(WorkingSpotscomponents);
	GetComponents(SlepingSpotscomponents);

	for (auto CompIt = SlepingSpotscomponents.CreateConstIterator(); CompIt; ++CompIt)
	{
		SleepingSpots.Emplace(Cast<USleepingSpot>(*CompIt), nullptr);
	}

	for (USleepingSpot* CompIt :  SlepingSpotscomponents)
	{
		SleepingSpots.Emplace(Cast<USleepingSpot>(CompIt), nullptr);
	}
	for (UWorkingSpot* CompIt :  WorkingSpotscomponents)
	{
		WorkingSpots.Emplace(Cast<UWorkingSpot>(CompIt), nullptr);
	}
}

USleepingSpot* ABuildingBaseActor::AddInhabitant(ACharacter* Settler)
{
	for (TPair<USleepingSpot*, ACharacter*>& Pair : SleepingSpots)
	{
		if(Pair.Value == nullptr)
		{
			SleepingSpots.Emplace(Pair.Key, Settler);
			return Pair.Key;
		}
	}
	return nullptr;
}
void ABuildingBaseActor::RemoveInhabitant(ACharacter* Settler)
{
	for (TPair<USleepingSpot*, ACharacter*>& Pair : SleepingSpots)
	{
		if(Pair.Value == Settler)
		{
			SleepingSpots.Emplace(Pair.Key, nullptr);
			
		}
	}
}

TArray<USleepingSpot*> ABuildingBaseActor::GetFreeSleepingSpots()
{
	TArray<USleepingSpot*> FreeSleepingSpots;
	
	for (TPair<USleepingSpot*, ACharacter*>& Pair : SleepingSpots)
	{
		if(Pair.Value == nullptr)
		{
			FreeSleepingSpots.Add(Pair.Key);
		}
	}

	return FreeSleepingSpots;
}


void ABuildingBaseActor::RemoveWorker(ACharacterSettler* Settler)
{
	for (TPair<UWorkingSpot*, ACharacterSettler*>& Pair : WorkingSpots)
	{
		if(Pair.Value == Settler)
		{
			WorkingSpots.Emplace(Pair.Key, nullptr);
		}
	}
}

UWorkingSpot* ABuildingBaseActor::AddWorker(ACharacterSettler* Settler)
{
	for (TPair<UWorkingSpot*, ACharacterSettler*>& Pair : WorkingSpots)
	{
		if(Pair.Value == nullptr)
		{
			WorkingSpots.Emplace(Pair.Key, nullptr);
			return Pair.Key;
		}
	}
	return nullptr;

}

TArray<UWorkingSpot*> ABuildingBaseActor::GetFreeWorkingSpot()
{
	TArray<UWorkingSpot*> FreeWorkingSpots;
	
	for (TPair<UWorkingSpot*, ACharacterSettler*>& Pair : WorkingSpots)
	{
		if(Pair.Value == nullptr)
		{
			FreeWorkingSpots.Add(Pair.Key);
		}
	}

	return FreeWorkingSpots;
}

