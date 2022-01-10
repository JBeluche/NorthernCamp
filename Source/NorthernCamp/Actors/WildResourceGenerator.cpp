// Copyright Creating Mountains!


#include "NorthernCamp/Actors/WildResourceGenerator.h"

#include "NavigationSystem.h"
#include "WildResourceActorBase.h"
#include "Components/SphereComponent.h"

// Sets default values
AWildResourceGenerator::AWildResourceGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);

	ActionArea = CreateDefaultSubobject<USphereComponent>(TEXT("Action Area"));
	ActionArea->SetupAttachment(SceneComponent);

	
}

// Called when the game starts or when spawned
void AWildResourceGenerator::BeginPlay()
{
	Super::BeginPlay();


	UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation ResultLocation;

	if(NavigationSystem)
	{
		

	for (TPair<TSubclassOf<AWildResourceActorBase>, int32>& Pair : WildResourcesToSpawn)
	{
		for(int32 i = 0; i < Pair.Value; i++)
		{
			NavigationSystem->GetRandomReachablePointInRadius(GetActorLocation(), ActionArea->GetScaledSphereRadius(), ResultLocation);

			GetWorld()->SpawnActor(Pair.Key), ResultLocation, FRotator(0.0f,0.0f,0.0f);
		}
		
	}
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("Navugation system is not casting in wild resource generator "));
	}

	//Get the resources
	//How many per resource?
	
}

