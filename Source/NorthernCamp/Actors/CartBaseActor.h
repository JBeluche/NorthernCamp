// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/ResourceManagerComponent.h"
#include "GameFramework/Actor.h"
#include "CartBaseActor.generated.h"


class ACharacterSettler;
enum class EResourceType : uint8;
UCLASS()
class NORTHERNCAMP_API ACartBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sex
	ACartBaseActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* MeshComp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	int32 StartingFood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	int32 StartingWater;

	//Public functions
	bool ExtractRersouce(EResourceType ResourceType, int32 Amount);
	bool CheckResourceAvailability(EResourceType ResourceType, int32 Amount);
	
	UBoxComponent* ReservePickupSpot(ACharacterSettler* CharacterAskingForSpot);
	UBoxComponent* FindReservedPickupSpot(ACharacterSettler* CharacterAskingForSpot);
	UBoxComponent* FreePickupSpot(ACharacterSettler* CharacterAskingForSpot);

	TMap<UBoxComponent*, AActor*> PickupLocations;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UResourceManagerComponent* ResourceManagerComp;

protected:
	
	virtual void BeginPlay() override;


};
