// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VitalsComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NORTHERNCAMP_API UVitalsComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVitalsComponentBase();

protected:
	// Called when the game starts

	virtual void BeginPlay() override;

	//Variables
	float CurrentHealth;
	float MaxHealth = 100.0f;
	float ShouldDieAt = 0.0f;
	
	
	

public:
	//Functions
	float GetHealth();
	void LoseHealth(float HealthLost);
	void DeathHandler();
	
		
};
