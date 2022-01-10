// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorkingSpot.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NORTHERNCAMP_API UWorkingSpot : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWorkingSpot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
