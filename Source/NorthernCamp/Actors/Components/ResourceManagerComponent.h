// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NORTHERNCAMP_API UResourceManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


		
};
