// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SleepingSpot.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NORTHERNCAMP_API USleepingSpot : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USleepingSpot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


		
};
