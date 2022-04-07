// Copyright Creating Mountains!


#include "NorthernCamp/Characters/Components/VitalsComponentBase.h"

// Sets default values for this component's properties
UVitalsComponentBase::UVitalsComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UVitalsComponentBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}

float UVitalsComponentBase::GetHealth()
{
	return CurrentHealth;
}

void UVitalsComponentBase::LoseHealth(float HealthLost)
{
	CurrentHealth = CurrentHealth - HealthLost;
	//UE_LOG(LogTemp, Error, TEXT("%s lost %f health, current health: %f"), *GetOwner()->GetName(), HealthLost, CurrentHealth);

	if(CurrentHealth <= ShouldDieAt)
	{
		DeathHandler();
	}
}

void UVitalsComponentBase::DeathHandler()
{
	GetOwner()->Destroy();
}
