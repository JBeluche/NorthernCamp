// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CartBaseActor.generated.h"


enum class EResourceType : uint8;
UCLASS()
class NORTHERNCAMP_API ACartBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sex
	ACartBaseActor();

	TMap<EResourceType, int32> ResourcesStoredInCart;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* MeshComp;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	int32 StartingWater;

	//Public functions
	bool ExtractRersouce(EResourceType ResourceType, int32 Amount);
	bool CheckResourceAvailability(EResourceType ResourceType, int32 Amount);
	
	bool ReservePickupSpot(AActor* ActorAskingForSpot);
	
	TMap<UBoxComponent*, AActor*> PickupLocations;

protected:
	
	virtual void BeginPlay() override;


};
