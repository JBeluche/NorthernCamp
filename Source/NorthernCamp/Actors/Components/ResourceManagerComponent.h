// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "ResourcesPickupSpot.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "ResourceManagerComponent.generated.h"

enum class EResourceType : uint8 
{
	None UMETA(DisplayName = "None"),
	Water UMETA(DisplayName = "Water"),
	Food UMETA(DisplayName = "Food"),
	
};

USTRUCT()
struct FResourceNeedStruct
{
	GENERATED_BODY()

	EResourceType ResourceType = EResourceType::None;
	int32 Amount = 0;
	//int32 Urgency = 0;
};


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

	
	TMap<EResourceType, int32> ResourcesInStorage;
	TMap<EResourceType, int32> CurrentResourceNeeded;
	TArray<EResourceType> EndlessResourceList;
	//TArray<FResourceNeedStruct> CurrentResourceNeeded;


public:
	
//Public functions
	bool ExtractRersouce(EResourceType ResourceType, int32 Amount, ACharacter* Character);
	bool CheckResourceAvailability(EResourceType ResourceType, int32 Amount);
	void AddResourceNeed(EResourceType ResourceType, int32 Amount);
	
	void AddResource(EResourceType ResourceType, int32 Amount);
	FResourceNeedStruct GetResourceNeed();
	
	UResourcesPickupSpot* ReservePickupSpot(ACharacter* CharacterAskingForSpot, UResourcesPickupSpot* PreferableSpot);
	UResourcesPickupSpot* FindReservedPickupSpot(ACharacter* CharacterAskingForSpot);
	UResourcesPickupSpot* FreePickupSpot(ACharacter* CharacterAskingForSpot);

	void AddEndlessResource(EResourceType ResourceType);

//Public variables
	TMap<UResourcesPickupSpot*, AActor*> PickupLocations;


		
};
