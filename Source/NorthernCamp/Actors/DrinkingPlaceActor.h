// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/ResourceManagerComponent.h"
#include "GameFramework/Actor.h"
#include "DrinkingPlaceActor.generated.h"

UCLASS()
class NORTHERNCAMP_API ADrinkingPlaceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Drinking place is just a place where you can get unlimited water. 
	
	ADrinkingPlaceActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;


	//Public functions
	bool PickupWater();

	//Public Variables
	UResourceManagerComponent* ResourceManagerComp;

protected:

	virtual void BeginPlay() override;


};
