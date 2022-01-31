// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/BTS_UpdateResourceAvailability.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NorthernCamp/NorthernCampGameMode.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "NorthernCamp/Controllers/ResourceController.h"

UBTS_UpdateResourceAvailability::UBTS_UpdateResourceAvailability()
{
	NodeName = "Check if resource available in Level";
}

void UBTS_UpdateResourceAvailability::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	//Get the resource controller
	AResourceController* ResourceController =  Cast<ANorthernCampGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->ResourceController;
	ACharacterSettler* Settler = Cast<ACharacterSettler>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")));

	if(!Settler){UE_LOG(LogTemp, Error, TEXT("Could not cast to settler in: BTS_UpdateResourceAvailability")); return;}
	if(!ResourceController){UE_LOG(LogTemp, Error, TEXT("Could not cast to ResourceController in: BTS_UpdateResourceAvailability")); return;}

	//You need multiple resouces, you first need to decide which will be chosen.

	EResourceType ResourceType = EResourceType::None;

	FResourceInfo PriorityResourceNeeded = Settler->ResourceManagerComp->GetCurrentResoucesToFetch();
	
	ResourceType = PriorityResourceNeeded.ResourceType;
	int32 Amount = PriorityResourceNeeded.Amount;

	if(ResourceType == EResourceType::None){return;}


	if(ResourceController->GetResourceAvailability(ResourceType, Amount))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false);
	}

	


}
