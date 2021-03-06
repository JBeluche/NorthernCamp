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


class ACharacterSettler;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components" )
	TArray<UClass*> SpawnableClasses;
	
	//Functions
	ARaidingBoatActor* SpawnBoat();

	
	void SpawnRaiders(TArray<TSubclassOf<AActor>> RaidersClassToSpawn);
	ACharacterBase* SpawnCharacter(TSubclassOf<AActor> CharactersToSpawn);
	
	bool CanSpawn(UClass* ClassToCheck);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	TSubclassOf<AActor> BoatBlueprintClass;

	UWorld* World;

	TArray<ACharacterBase*> SpawnedRaiders;

};
