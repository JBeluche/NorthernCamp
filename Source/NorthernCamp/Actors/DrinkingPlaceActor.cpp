// Copyright Creating Mountains!


#include "NorthernCamp/Actors/DrinkingPlaceActor.h"

// Sets default values
ADrinkingPlaceActor::ADrinkingPlaceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	ResourceManagerComp = CreateDefaultSubobject<UResourceManagerComponent>(TEXT("Resource Manager"));

	

}

// Called when the game starts or when spawned
void ADrinkingPlaceActor::BeginPlay()
{
	Super::BeginPlay();

	ResourceManagerComp->AddEndlessResource(EResourceType::Water);

	
}



