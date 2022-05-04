// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "NorthernCamp/Controllers/ResourceController.h"

#include "ResourceManagerComponent.generated.h"

class ADayNightActorController;
class UResourcesPickupSpot;
class AResourceController;


USTRUCT()
struct FResourceInfo
{
	GENERATED_BODY()

	EResourceType ResourceType;
	int32 Amount = 0;
	int32 PriorityNumber;

};

UENUM(BlueprintType)
enum class EStorageOwnerType : uint8 
{
	None UMETA(DisplayName = "None"),
	Character UMETA(DisplayName = "Character"),
	Building UMETA(DisplayName = "Building"),
	Cart UMETA(DisplayName = "Cart"),
	All UMETA(DisplayName = "All"),

};

USTRUCT(BlueprintType)
struct FStorageListItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	EResourceType ResourceType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	int32 MaxAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	int32 CurrentAmount;
};


USTRUCT(BlueprintType)
struct FStorage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	FName StorageName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	TArray<FStorageListItem> ResourcesStoredList;
 
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NORTHERNCAMP_API UResourceManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceManagerComponent();

	FResourceInfo GetCurrentResoucesToFetch();
	UResourcesPickupSpot* GetClosestPickupSpot(ACharacter* Character);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	EStorageOwnerType StorageOwnerType;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
	TArray<FResourceInfo> CurrentResourceNeeded;
	
	TArray<EResourceType> EndlessResourceList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	TArray<FStorage> StorageList;

	void UpdateMyResourcesInController();

	FStorage GetStorageByName(FName NameOfStorage);


public:

	
	ADayNightActorController* DayNightController;
	AResourceController* ResourceController;

	//Other Stuff
	//void AddResourceNeed(FResourceInfo ResourceNeedInfo);
	
//Storage functions
	int32 ExtractRersouce(FResourceInfo ResourceInfo, ACharacter* Character);
	bool CheckResourceAvailability(FResourceInfo ResourceInfo);
	void AddStorage(FName StorageName, TArray<FResourceInfo> ResourcesSpace);
	void AddEndlessResource(EResourceType ResourceType);
	int32 AddResource(FResourceInfo Resource, FName StorageName = FName(""));
	TMap<EResourceType, int32> GetTotalResourceAmount();
	bool TransferResources(FResourceInfo ResourceInfo, UResourceManagerComponent* ResourceManager);
	void RemoveResourceNeed(FResourceInfo ResourceInfo);
	void UpdateResourceNeed(TArray<FResourceInfo> ResourcesNeeded);
	bool ConsumeResource(FResourceInfo ResourceInfo);



	//FResourceNeedStruct GetResourceNeed();

	//Pickup spots 
	UResourcesPickupSpot* ReservePickupSpot(ACharacter* CharacterAskingForSpot);
	UResourcesPickupSpot* FindReservedPickupSpot(ACharacter* CharacterAskingForSpot);
	UResourcesPickupSpot* FreePickupSpot(ACharacter* CharacterAskingForSpot);

	TMap<UResourcesPickupSpot*, AActor*> PickupLocations;





	//TMap<EResourceType, int32> ResourcesInStorage;
		
};
