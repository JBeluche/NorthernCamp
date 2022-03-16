// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BoatDockingLocation.generated.h"

UCLASS()
class NORTHERNCAMP_API ABoatDockingLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoatDockingLocation();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxComponent;

};
