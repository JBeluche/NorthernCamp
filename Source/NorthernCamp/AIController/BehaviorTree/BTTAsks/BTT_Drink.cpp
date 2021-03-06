// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTTAsks/BTT_Drink.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/AIController/AISettlerController.h"
#include "NorthernCamp/Characters/CharacterSettler.h"


UBTT_Drink::UBTT_Drink()
{
	NodeName = TEXT("Drink water");
}

EBTNodeResult::Type UBTT_Drink::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACharacterSettler* Settler  = Cast<ACharacterSettler>(OwnerComp.GetAIOwner()->GetPawn());

	if(!Settler){return EBTNodeResult::Failed;}
	
	Settler->DrinkWater(10000.0f);

	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("bIsThirsty"));
	
	return EBTNodeResult::Succeeded;


	
}






