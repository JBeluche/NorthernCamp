// Copyright Creating Mountains!


#include "NorthernCamp/Controllers/ResourceController.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/UserWidgets/Controls/LooseCameraControlsWidget.h"

// Sets default values
AResourceController::AResourceController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AResourceController::BeginPlay()
{
	Super::BeginPlay();


}

void AResourceController::AddToResourceTotal(EResourceType ResourceType, int32 Amount)
{
	if (TotalResourcesStored.Contains(ResourceType))
	{
		TotalResourcesStored.Emplace(ResourceType, (TotalResourcesStored[ResourceType] + Amount));
	}
	else
	{
		TotalResourcesStored.Add(ResourceType, Amount);
	}
}

void AResourceController::RemoveFromResourceTotal(EResourceType ResourceType, int32 Amount)
{
	if (TotalResourcesStored.Num() > 0)
	{
		if (TotalResourcesStored.Contains(ResourceType))
		{
			if (TotalResourcesStored[ResourceType] <= Amount)
			{
				TotalResourcesStored.Emplace(ResourceType, (TotalResourcesStored[ResourceType] - Amount));
			}
			else
			{
				UE_LOG(LogTemp, Error,
				       TEXT("Resource Controller: Trying to remove from TotalResourcesStored, but amount is to high"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error,
		       TEXT(
			       "Resource Controller: the resource needs to be removed from total but the TotalResourcesStored map is empty."
		       ));
	}
}

void AResourceController::UpdateTotalResouces()
{

	PlayerController = Cast<ANorthernCampPlayerController>( UGameplayStatics::GetPlayerController(GetWorld(), 0) );

	TMap<EResourceType, int32> TotalResoucesCounter;

	uint8 ResouceEnumValue = (uint8)EResourceType::All;

	//Get all the Resource Mangers Component
	for (int i = 0; i < ResouceManagerComponentsList.Num(); i++)
	{

		//Cast to character to check if you need to exclude from total.
		if(ResouceManagerComponentsList[i]->StorageOwnerType != EStorageOwnerType::Character)
		{
			//For each resources type, check in the storage and add to total counter.
			for (EResourceType Val : TEnumRange<EResourceType>())
			{
				EResourceType ResourceType = (EResourceType)Val;

				if (TotalResoucesCounter.Contains(ResourceType) && ResouceManagerComponentsList[i]->GetTotalResourceAmount().Contains(ResourceType))
				{
					TotalResoucesCounter.Emplace(ResourceType, (TotalResoucesCounter[ResourceType] + ResouceManagerComponentsList[i]->GetTotalResourceAmount()[ResourceType]));
				}
				else if(ResouceManagerComponentsList[i]->GetTotalResourceAmount().Contains(ResourceType))
				{
					TotalResoucesCounter.Add(ResourceType, ResouceManagerComponentsList[i]->GetTotalResourceAmount()[ResourceType]);
				}
			}	
		}
	}	

	TotalResourcesStored = TotalResoucesCounter;
}

void AResourceController::AddResourceManagerComponent(UResourceManagerComponent* ResouceManager)
{
	UE_LOG(LogTemp, Error, TEXT("Resouce Controller adding: %s"), *ResouceManager->GetReadableName());

	if (ResouceManager)
	{
		ResouceManagerComponentsList.Add(ResouceManager);
		UpdateTotalResouces();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Resouce Controller: Nullptr in AddResourceManagerComponent"));
	}
}

bool AResourceController::GetResourceAvailability(EResourceType ResourceType, int32 Amount)
{
	UpdateTotalResouces();
	for (TPair<EResourceType, int32>& Pair : TotalResourcesStored)
	{
		if (Pair.Key == ResourceType && Pair.Value >= Amount)
		{
			return true;
		}
	}

	return false;
}

TArray<UResourceManagerComponent*> AResourceController::GetResourceManagersWithResource(EResourceType ResourceType, int32 Amount)
{
	TArray<UResourceManagerComponent*> ComponentsWithResource;

	for (UResourceManagerComponent* ResourceManager : ResouceManagerComponentsList)
	{
		if (TotalResourcesStored.Contains(ResourceType) && ResourceManager->GetTotalResourceAmount().Contains(ResourceType))
		{
			if (ResourceManager->GetTotalResourceAmount()[ResourceType] >= Amount)
			{
				if(ResourceManager != nullptr)
				{
					if(!ComponentsWithResource.Contains(ResourceManager))
					{
						ComponentsWithResource.Add(ResourceManager);
					}
				}
			
			}
		}
	}

	return ComponentsWithResource;
}
