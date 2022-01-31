// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NorthernCamp/Actors/Components/ResourceManagerComponent.h"
#include "ResourceController.generated.h"

class ANorthernCampPlayerController;
class UResourceManagerComponent;


UENUM(BlueprintType)
enum class EResourceType : uint8 
{
	None UMETA(DisplayName = "None"),
	Water UMETA(DisplayName = "Water"),
	Food UMETA(DisplayName = "Food"),
	Wood UMETA(DisplayName = "Wood"),
	All UMETA(DisplayName = "All"),

};



ENUM_RANGE_BY_COUNT(EResourceType, EResourceType::All)

USTRUCT(BlueprintType)
struct FResourceTypeInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	FSlateBrush ResouceIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	FText DisplayName;
};

UCLASS()
class NORTHERNCAMP_API AResourceController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	TMap<EResourceType, FResourceTypeInfo> ResourcesInfoMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	TArray<EResourceType> GatherableResources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	TMap<EResourceType, int32> TotalResourcesStored;




	TArray<UResourceManagerComponent*> ResouceManagerComponentsList;
	void AddResourceManagerComponent(UResourceManagerComponent* ResouceManager);
	
	void AddToResourceTotal(EResourceType ResourceType, int32 Amount);
	void RemoveFromResourceTotal(EResourceType ResourceType, int32 Amount);
	void UpdateTotalResouces();
	bool GetResourceAvailability(EResourceType ResourceType, int32 Amount);
	TArray<UResourceManagerComponent*> GetResourceManagersWithResource(EResourceType ResourceType, int32 Amount);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	ANorthernCampPlayerController* PlayerController;



};
