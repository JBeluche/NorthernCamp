// Copyright Creating Mountains!


#include "NorthernCamp/Actors/Components/ResourceManagerComponent.h"

#include "EngineUtils.h"
#include "NavigationSystem.h"
#include "ResourcesPickupSpot.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NorthernCamp/NorthernCampGameMode.h"

UResourceManagerComponent::UResourceManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
   
}

void UResourceManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = Cast<AActor>(GetOwner());

	for (TActorIterator<AResourceController> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{ 
		ResourceController = Cast<AResourceController>(*ActorItr);
	}

	if(!ResourceController){UE_LOG(LogTemp, Error, TEXT("Resouce Manager Component: I need a resource controller, but its a nullptr it in beginplay")); return;}
	ResourceController->AddResourceManagerComponent(this);



	//AddMyResourcesToController();
	
	if(Owner)
	{
		TInlineComponentArray<UResourcesPickupSpot*> Components;
		Owner->GetComponents(Components);
	
		for (auto CompIt = Components.CreateConstIterator(); CompIt; ++CompIt)
		{
			PickupLocations.Emplace(Cast<UResourcesPickupSpot>(*CompIt), nullptr);
		}

		//Register self to game state as a resource actor;
		
		ANorthernCampGameMode * GameMode = Cast<ANorthernCampGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->AddResourceManager(this);
	}

}

//------------------------------------------
//	Storage functions
//------------------------------------------

int32 UResourceManagerComponent::AddResource(FResourceInfo Resource, FName StorageName)
{
	int32 ResourceLeftToStore = Resource.Amount;
	
	
	//Look for the desired storage space
	int32 ArrayPosition = 0;
	if(GetStorageByName(StorageName).StorageName == StorageName)
	{
		FStorage Storage = GetStorageByName(StorageName);
		
		for(FStorageListItem StorageItem : Storage.ResourcesStoredList)
		{

			FStorageListItem NewStorageItem = StorageItem;
			if(StorageItem.ResourceType == Resource.ResourceType)
			{
				
				//Store the resource if space
				int32 StorageSpaceLeft = (StorageItem.MaxAmount - StorageItem.CurrentAmount);
				
				if(StorageSpaceLeft - ResourceLeftToStore > 0)
				{
					//Store all resources;
					StorageItem.CurrentAmount = (StorageItem.CurrentAmount + ResourceLeftToStore);

					ResourceLeftToStore = 0;
					NewStorageItem.CurrentAmount = StorageItem.CurrentAmount + Resource.Amount;
					Storage.ResourcesStoredList[ArrayPosition] = NewStorageItem;
				}
				else if(StorageSpaceLeft > 0)
				{
					//Store resources that can be stored;
					int32 AmountOfStorableSpace = StorageSpaceLeft - ResourceLeftToStore;
					ResourceLeftToStore = ResourceLeftToStore - AmountOfStorableSpace;

					NewStorageItem.CurrentAmount = (StorageItem.CurrentAmount + AmountOfStorableSpace);
					Storage.ResourcesStoredList[ArrayPosition] = NewStorageItem;
				}
			}
			ArrayPosition++;
		}
	}
	if(ResourceLeftToStore > 0)
	{
		//Check other resource posibilities
		for(FStorage Storage : StorageList)
		{
			UE_LOG(LogTemp, Error, TEXT("UResourceManagerComponent: Storage iterating %s"), *Storage.StorageName.ToString());
			
			for(FStorageListItem StorageItem : Storage.ResourcesStoredList)
			{
				
				if(ResourceLeftToStore <= 0){break;}

				if(StorageItem.ResourceType == Resource.ResourceType)
				{
					int32 StorageSpaceLeft = (StorageItem.MaxAmount - StorageItem.CurrentAmount);
					
					if(StorageSpaceLeft - ResourceLeftToStore >= 0)
					{
						//Store all resources;
						StorageItem.CurrentAmount = (StorageItem.CurrentAmount + ResourceLeftToStore);

						ResourceLeftToStore = 0;
						StorageItem.CurrentAmount = StorageItem.CurrentAmount + Resource.Amount;
					}
					else if(StorageSpaceLeft > 0)
					{
						//Store resources that can be stored;
						int32 AmountOfStorableSpace = StorageSpaceLeft - ResourceLeftToStore;
						ResourceLeftToStore = ResourceLeftToStore - AmountOfStorableSpace;

						StorageItem.CurrentAmount = (StorageItem.CurrentAmount + AmountOfStorableSpace);
					}
				}
			}
		}
	}
	//Return the int with the ResourceLeftToStore

	UE_LOG(LogTemp, Error, TEXT("UResourceManagerComponent: Resources added, left to store: %i, while i needed %i"), ResourceLeftToStore, Resource.Amount);

	return ResourceLeftToStore;
}

FStorage UResourceManagerComponent::GetStorageByName(FName NameOfStorage)
{
	FStorage Storage;
	
	for(int32 i = 0; i < StorageList.Num(); i++)
	{
		if(StorageList[i].StorageName == NameOfStorage)
		{
			Storage = StorageList[i];
		}
	}

	return Storage;
}

bool UResourceManagerComponent::TransferResources(FResourceInfo ResourceInfo, UResourceManagerComponent* ResourceManager)
{

	//This is just for debuging
	FString EnumName;
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EResourceType"), true);
	if (!enumPtr)
	{
		EnumName = FString("Invalid");
	}
	else
	{
		EnumName = enumPtr->GetNameStringByIndex((int32)ResourceInfo.ResourceType);
	}
	//No more debugging.
	int32 ResourceLeftToExtract = ResourceInfo.Amount;
	
	if(ResourceManager)
	{
		if(EndlessResourceList.Contains(ResourceInfo.ResourceType))
		{
			//Beware you only get what you ask for, so if you just asked for 1 water, you only get one.
			ResourceManager->AddResource(ResourceInfo);
			//UpdateResourceNeed(ResourceInfo); TODO This needs to work again
		}

		int32 ArrayPosition = 0;
		//You check all the storages to see if there is enought resource. Otherwise you only retrieve what you can. 
		for(FStorage Storage : StorageList)
		{
			for(FStorageListItem StorageItem : Storage.ResourcesStoredList)
			{
				if(ResourceLeftToExtract <= 0){break;}
				FStorageListItem NewStorageItem = StorageItem;
				FResourceInfo ResourceInfoExtracted = ResourceInfo;
				
				if(StorageItem.ResourceType == ResourceInfo.ResourceType)
				{
					if(StorageItem.CurrentAmount >= 0)
					{
						//Extract resouce
						//Extract what you can.
						if(StorageItem.CurrentAmount >= ResourceInfo.Amount)
						{
							//Simply extract
							NewStorageItem.CurrentAmount = (NewStorageItem.CurrentAmount - ResourceInfo.Amount);
							Storage.ResourcesStoredList[ArrayPosition] = NewStorageItem;
							ResourceLeftToExtract = 0;
							ResourceManager->AddResource(ResourceInfoExtracted);
							//ResourceManager->UpdateResourceNeed(ResourceInfoExtracted); TODO This needs to work again

						}
						else if(StorageItem.CurrentAmount > 0)
						{
							//Extract the maximus
							int32 ExtractedAmount =  (ResourceInfo.Amount - StorageItem.CurrentAmount);
							NewStorageItem.CurrentAmount = (NewStorageItem.CurrentAmount - ExtractedAmount);
							
						//	Storage.ResourcesStoredList.RemoveAt(ArrayPosition);
						//	Storage.ResourcesStoredList.Add(NewStorageItem);
							
							Storage.ResourcesStoredList[ArrayPosition] = NewStorageItem;


							ResourceLeftToExtract = ResourceLeftToExtract - ExtractedAmount;
							ResourceInfoExtracted.Amount = ExtractedAmount;
							ResourceManager->AddResource(ResourceInfoExtracted);
							//ResourceManager->UpdateResourceNeed(ResourceInfoExtracted); TODO This needs to work again

						}
						
				
					}
				}
				ArrayPosition++;
			}
		}

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UResourceManagerComponent: Nullptr ResourceManager in TransferResource()"));
	}

	if(ResourceLeftToExtract <= 0)
	{
		return true;
	}
	return false;

}

int32 UResourceManagerComponent::ExtractRersouce(FResourceInfo ResourceInfo, ACharacter* Character)
{
	if(EndlessResourceList.Contains(ResourceInfo.ResourceType))
	{
		return 0;
	}

	//This is just for debuging
	FString EnumName;
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EResourceType"), true);
	if (!enumPtr)
	{
		EnumName = FString("Invalid");
	}
	else
	{
		EnumName = enumPtr->GetNameStringByIndex((int32)ResourceInfo.ResourceType);
	}
	//No more debugging.
	
	int32 ResourceLeftToExtract = ResourceInfo.Amount;

	//Check other resource posibilities
	for(FStorage Storage : StorageList)
	{
		for(FStorageListItem StorageItem : Storage.ResourcesStoredList)
		{
			if(ResourceLeftToExtract <= 0){break;}

			if(StorageItem.ResourceType == ResourceInfo.ResourceType)
			{
				if(StorageItem.CurrentAmount >= 0)
				{
					//Extract resouce
					//Extract what you can.
					if(StorageItem.CurrentAmount >= ResourceInfo.Amount)
					{
						//Simply extract
						StorageItem.CurrentAmount = (StorageItem.CurrentAmount - ResourceInfo.Amount);
						ResourceLeftToExtract = 0;
						UE_LOG(LogTemp, Warning, TEXT("%s took: %s | Storage name: %s | Amount: %i"), *Character->GetName(), *EnumName, *Storage.StorageName.ToString(), ResourceInfo.Amount);

					}
					else if(StorageItem.CurrentAmount > 0)
					{
						//Extract the maximus
						int32 ExtractedAmount =  (ResourceInfo.Amount - StorageItem.CurrentAmount);
						StorageItem.CurrentAmount = (StorageItem.CurrentAmount - ExtractedAmount);

						ResourceLeftToExtract = ResourceLeftToExtract - ExtractedAmount;
						
						UE_LOG(LogTemp, Warning, TEXT("%s took: %s | Storage name: %s | Amount: %i"), *Character->GetName(), *EnumName, *Storage.StorageName.ToString(), ExtractedAmount);
					}
				
				}
			}
		}
	}

	return ResourceLeftToExtract;
}

bool UResourceManagerComponent::CheckResourceAvailability(FResourceInfo ResourceInfo)
{
	//Might cause a crash if the array does not exists but he tries to compare with the amount.
	if(EndlessResourceList.Contains(ResourceInfo.ResourceType))
	{
		return true;
	}
	if(!GetTotalResourceAmount().Contains(ResourceInfo.ResourceType))		{return false;}
	if(GetTotalResourceAmount()[ResourceInfo.ResourceType] >= ResourceInfo.Amount)
	{
		return true;
	}
	
	return false;

}

void UResourceManagerComponent::AddStorage(FName StorageName, TArray<FResourceInfo> ResourcesSpace)
{
	FStorage Storage = FStorage();

	Storage.StorageName = StorageName;
	FStorageListItem CurrentStorage;

	for(int32 i = 0; i < ResourcesSpace.Num(); i++)
	{
		if(ResourcesSpace[i].ResourceType == EResourceType::All)
		{
			//If you selected all you simply add for each resources
			for(int32 EResourceId = 0; EResourceId < (uint8)EResourceType::All; EResourceId++)
			{
				EResourceType e = (EResourceType)EResourceId;
				if(e != EResourceType::None && e != EResourceType::All)
				{
					CurrentStorage.ResourceType = e;
					CurrentStorage.MaxAmount = ResourcesSpace[i].Amount;
					CurrentStorage.CurrentAmount = 0;
					Storage.ResourcesStoredList.Add(CurrentStorage);
				}
			}
		}
		else
		{
			CurrentStorage.ResourceType = ResourcesSpace[i].ResourceType;
			CurrentStorage.MaxAmount = ResourcesSpace[i].Amount;
			CurrentStorage.CurrentAmount = 0;
			Storage.ResourcesStoredList.Add(CurrentStorage);
		}

	}

	StorageList.Add(Storage);
}

//------------------------------------------
//	Resource functions.
//------------------------------------------

/*void UResourceManagerComponent::AddResourceNeed(FResourceInfo NewResourceNeed)
{
	UE_LOG(LogTemp, Error, TEXT("A resource need was added."));
	
	CurrentResourceNeeded.Add(NewResourceNeed);
	
	if(EndlessResourceList.Contains(NewResourceNeed.ResourceType))
	{
		UE_LOG(LogTemp, Error, TEXT("%s: I am trying to add a resource need, but have an endless supply."), *GetOwner()->GetName())
	}
}*/

void UResourceManagerComponent::UpdateResourceNeed(TArray<FResourceInfo> ResourcesNeeded)
{
	//The function has to check if we have the resouces in store. If we do, we don't need to fetch them.
	TArray<FResourceInfo> NewResourcesNeeded = ResourcesNeeded;

	int32 ArrayPositionResourceInfo = 0;
	int32 ArrayPositionStorageListItem = 0;
	
	for(FStorage Storage : StorageList)
	{
		for(FStorageListItem StorageListItem : Storage.ResourcesStoredList)
		{
			for(FResourceInfo ResourceInfo : ResourcesNeeded)
			{
				if(StorageListItem.ResourceType == ResourceInfo.ResourceType)
				{
					if(StorageListItem.CurrentAmount >= ResourceInfo.Amount && ResourceInfo.Amount > 0)
					{
						NewResourcesNeeded[ArrayPositionResourceInfo].Amount = 0;
					}
					//If there is a need and there is a resource in store
					else if(ResourceInfo.Amount > 0 && StorageListItem.CurrentAmount > 0)
					{
						int32 SubtractedAmount = ResourceInfo.Amount - StorageListItem.CurrentAmount;
						ResourcesNeeded[ArrayPositionResourceInfo].Amount = ResourceInfo.Amount - SubtractedAmount;
						Storage.ResourcesStoredList[ArrayPositionStorageListItem].CurrentAmount = 0;
					}
				}
				ArrayPositionResourceInfo++;
			}
			ArrayPositionStorageListItem++;
		}
	}
	
	CurrentResourceNeeded = NewResourcesNeeded;

	/*OLD CODE
	//Create an array as big as the one give(ResourceNeedArray)
	TArray<FResourceInfo> SortedArray = CurrentResourceNeeded;
	int32 PositionToSet = (CurrentResourceNeeded.Num() - 1);

	//Check each individual. If its higher, add position++
	for(FResourceInfo ArrayItem : CurrentResourceNeeded)
	{
		for(FResourceInfo ArrayItem2 : CurrentResourceNeeded)
		{
			if(ArrayItem.PriorityNumber > ArrayItem2.PriorityNumber)
			{
				PositionToSet--;
			}
		}
		SortedArray[PositionToSet] = ArrayItem;
		PositionToSet = (CurrentResourceNeeded.Num() - 1);
	}

	int32 ResourceLeftToSubtrack = ResourceInfo.Amount;

	int32 ArrayPosition = 0;
	TArray<int32> ArrayPositionsToRemove;
	
	for(FResourceInfo ResourceNeedItem : SortedArray)
	{
		if(ResourceLeftToSubtrack <= 0)
		{
			break;
		}
		if(ResourceNeedItem.ResourceType == ResourceInfo.ResourceType)
		{
			if(ResourceNeedItem.Amount <= ResourceLeftToSubtrack)
			{
				ArrayPositionsToRemove.Add(ArrayPosition);
				ResourceLeftToSubtrack = ResourceLeftToSubtrack - ResourceNeedItem.Amount;
			}
			else if(ResourceNeedItem.Amount > ResourceLeftToSubtrack)
			{
				FResourceInfo NewResourceNeedItem = ResourceNeedItem;
				NewResourceNeedItem.Amount = (ResourceNeedItem.Amount - ResourceLeftToSubtrack);
				ResourceLeftToSubtrack = 0;
				
				SortedArray[ArrayPosition] = NewResourceNeedItem;
			}
		}
		ArrayPosition++;
	}

	for(int32 PositionToRemove : ArrayPositionsToRemove)
	{
		SortedArray.RemoveAt(PositionToRemove);
	}

	CurrentResourceNeeded = SortedArray;
*/
}

void UResourceManagerComponent::AddEndlessResource(EResourceType ResourceType)
{
	if(!EndlessResourceList.Contains(ResourceType))
	{
		EndlessResourceList.Add(ResourceType);
	}
}

FResourceInfo UResourceManagerComponent::GetCurrentResoucesToFetch()
{
	FResourceInfo PriorityResouceNeed;
	PriorityResouceNeed.ResourceType = EResourceType::None;
	PriorityResouceNeed.PriorityNumber = 0;
	
	for(FResourceInfo ArrayItem : CurrentResourceNeeded)
	{
		if(ArrayItem.PriorityNumber > PriorityResouceNeed.PriorityNumber)
		{
			PriorityResouceNeed = ArrayItem;
		//	UE_LOG(LogTemp, Error, TEXT("I found my resource need. | Amount: %i"), ArrayItem.Amount);

		}
	}
	
	return PriorityResouceNeed;
}

TMap<EResourceType, int32> UResourceManagerComponent::GetTotalResourceAmount()
{
	TMap<EResourceType, int32> TotalAmountOfResources;

	for(FStorage Storage : StorageList)
	{
		for(FStorageListItem StorageItem : Storage.ResourcesStoredList)
		{
			//If the resource already is in the array.
			if(TotalAmountOfResources.Contains(StorageItem.ResourceType))
			{
				if(StorageItem.CurrentAmount > 0)
				{
					TotalAmountOfResources.Emplace(StorageItem.ResourceType, (TotalAmountOfResources[StorageItem.ResourceType] + StorageItem.CurrentAmount));
				}
			}
			else if(StorageItem.CurrentAmount > 0)
			{
				TotalAmountOfResources.Add(StorageItem.ResourceType, StorageItem.CurrentAmount);
			}
		}
	}
	return TotalAmountOfResources;
}

bool UResourceManagerComponent::ConsumeResource(FResourceInfo ResourceInfo)
{
	int32 AmountLeftToConsume = ResourceInfo.Amount;

	int32 CurrentArrayPosition = 0;
	//Check all the storages and consume
	for(FStorage StorageItem : StorageList)
	{
		for(FStorageListItem StorageListItem : StorageItem.ResourcesStoredList)
		{
			if(AmountLeftToConsume <= 0){return true;}
			
			if(StorageListItem.ResourceType == ResourceInfo.ResourceType && AmountLeftToConsume > 0)
			{
				if(AmountLeftToConsume <= StorageListItem.CurrentAmount)
				{
					//Consume needed and save array
					FStorageListItem UpdatedStorageListItem = StorageListItem;
					UpdatedStorageListItem.CurrentAmount = (StorageListItem.CurrentAmount - AmountLeftToConsume);
					StorageItem.ResourcesStoredList[CurrentArrayPosition] = UpdatedStorageListItem;
				}
				else
				{
					//Consume all and save array
					FStorageListItem UpdatedStorageListItem = StorageListItem;
					AmountLeftToConsume = AmountLeftToConsume - StorageListItem.CurrentAmount;
					UpdatedStorageListItem.CurrentAmount = 0;
					StorageItem.ResourcesStoredList[CurrentArrayPosition] = UpdatedStorageListItem;
				}
			}
		}
	}
	return false;
}

//------------------------------------------
//	Pickup spots functions.
//------------------------------------------

UResourcesPickupSpot* UResourceManagerComponent::ReservePickupSpot(ACharacter* CharacterAskingForSpot)
{
	UResourcesPickupSpot* Spot;
	Spot = FindReservedPickupSpot(CharacterAskingForSpot);
		
	if(Spot != nullptr)
	{
		return Spot;
	}
	else
	{
		//Get closest spot to the actor. 
		if(!GetClosestPickupSpot(CharacterAskingForSpot)){return nullptr;}
		if(PickupLocations[GetClosestPickupSpot(CharacterAskingForSpot)] == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Preferable spot reserved for: %s"), *CharacterAskingForSpot->GetName());

			PickupLocations.Emplace(GetClosestPickupSpot(CharacterAskingForSpot), CharacterAskingForSpot);
			Spot = GetClosestPickupSpot(CharacterAskingForSpot);
		}
		else
		{
			//This is never the case?
			for (TPair<UResourcesPickupSpot*, AActor*>& Pair : PickupLocations)
			{
				if(Pair.Value == nullptr)
				{
					PickupLocations.Emplace(Pair.Key, CharacterAskingForSpot);
					UE_LOG(LogTemp, Error, TEXT("Other spot reserved for: %s"), *CharacterAskingForSpot->GetName());
					return Pair.Key;
				}
			}
		}
	
		
		
		return Spot;
	}
}

UResourcesPickupSpot* UResourceManagerComponent::FindReservedPickupSpot(ACharacter* CharacterAskingForSpot)
{
	//Check if the character already is in tmap
	for (TPair<UResourcesPickupSpot*, AActor*>& Pair : PickupLocations)
	{
		if(Pair.Value != nullptr)
		{
			if(Pair.Value == CharacterAskingForSpot)
			{
				return Pair.Key;
			}
		}
	}

	return nullptr;
}

UResourcesPickupSpot* UResourceManagerComponent::FreePickupSpot(ACharacter* CharacterAskingForSpot)
{
	//Check if the character already is in tmap
	for (TPair<UResourcesPickupSpot*, AActor*>& Pair : PickupLocations)
	{
		if(Pair.Value == CharacterAskingForSpot)
		{
			UE_LOG(LogTemp, Error, TEXT("Spot deleted by: %s"), *CharacterAskingForSpot->GetName());

			Pair.Value = nullptr; 
		}
	}

	return nullptr;
}

UResourcesPickupSpot* UResourceManagerComponent::GetClosestPickupSpot(ACharacter* Character)
{
	UNavigationSystemV1* NavigationSystemv1 = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	UResourcesPickupSpot* ClosestPickupSpot = nullptr;
	float NewPathLength; 
	float OldPathLength; 

	for (TPair<UResourcesPickupSpot*, AActor*>& Pair : PickupLocations)
	{
		if(Pair.Value == nullptr)
		{
			NavigationSystemv1->GetPathLength(Character->GetActorLocation(), Pair.Key->GetOwner()->GetActorLocation(), NewPathLength);
			
			if(ClosestPickupSpot == nullptr)
			{
				ClosestPickupSpot = Pair.Key;
				OldPathLength = NewPathLength;
			}
			else if(NewPathLength < OldPathLength)
			{
				ClosestPickupSpot = Pair.Key;
				OldPathLength = NewPathLength;
			}
		}
	}

	return ClosestPickupSpot;
}

