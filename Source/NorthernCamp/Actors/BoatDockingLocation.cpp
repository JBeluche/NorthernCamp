// Copyright Creating Mountains!


#include "NorthernCamp/Actors/BoatDockingLocation.h"

// Sets default values
ABoatDockingLocation::ABoatDockingLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box for visuals"));
	BoxComponent->SetupAttachment(SceneComponent);
	

}

// Called when the game starts or when spawned
void ABoatDockingLocation::BeginPlay()
{
	Super::BeginPlay();
	
}


