// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTTAsks/BTT_FindQuietPlace.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/AIController/AISettlerController.h"

UBTT_FindQuietPlace::UBTT_FindQuietPlace()
{
	NodeName = TEXT("Set quiet place");
}

EBTNodeResult::Type UBTT_FindQuietPlace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	ACharacterSettler* Settler = Cast<ACharacterSettler>(OwnerComp.GetAIOwner()->GetPawn());
	FNavLocation ResultLocation;
	
	NavigationSystem->GetRandomReachablePointInRadius(Settler->GetActorLocation(), 1500.0f, ResultLocation);

	float PathLength;
	NavigationSystem->GetPathLength(Settler->GetActorLocation(), ResultLocation, PathLength);

	if(PathLength > 1200.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ResultLocation);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}