// Copyright Creating Mountains!


#include "NorthernCamp/Actors/Components/SleepingSpot.h"

// Sets default values for this component's properties
USleepingSpot::USleepingSpot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USleepingSpot::BeginPlay()
{
	Super::BeginPlay();

	// ...
}