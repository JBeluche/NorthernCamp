// Copyright Creating Mountains!


#include "NorthernCamp/Actors/WildResourceActorBase.h"

// Sets default values
AWildResourceActorBase::AWildResourceActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);
	
}

// Called when the game starts or when spawned
void AWildResourceActorBase::BeginPlay()
{
	Super::BeginPlay();

	
}



