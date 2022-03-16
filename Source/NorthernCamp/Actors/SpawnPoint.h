// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "BoatDockingLocation.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "NorthernCamp/AIController/AIControllerBase.h"
#include "NorthernCamp/Characters/CharacterBase.h"
#include "NorthernCamp/Controllers/RaidController.h"
#include "NorthernCamp/Pawns/RaidingBoatActor.h"
#include "SpawnPoint.generated.h"


UCLASS()
class NORTHERNCAMP_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* BoatDockingSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	bool bIsBoatSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components" )
	TArray<EFactions> AllowedFactions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components" )
	int32 MaxPeopleToSpawn;
	
	//Functions
	ARaidingBoatActor* SpawnBoat();

	
	void SpawnRaiders(TArray<TSubclassOf<class ACharacterBase>> RaidersClassToSpawn);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	TSubclassOf<class ARaidingBoatActor> BoatBlueprint;

	UWorld* World;
	TArray<ACharacterBase*> SpawnedRaiders;

};
