// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTTAsks/BTT_ResetFocus.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/AIController/AIControllerBase.h"
#include "NorthernCamp/AIController/BehaviorTree/BlackboardKeys/AgresorBlackboardKeys.h"

UBTT_ResetFocus::UBTT_ResetFocus()
{
	NodeName = TEXT("Clear focus");
}

EBTNodeResult::Type UBTT_ResetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIControllerBase* AIController  = Cast<AAIControllerBase>(OwnerComp.GetAIOwner()->GetPawn()->GetController());

	if(!AIController){UE_LOG(LogTemp,Error, TEXT("UBTT_ResetFocus::ExecuteTask nullptr AIController")); return EBTNodeResult::Failed;}

	AIController->ClearFocus(EAIFocusPriority::Default);

	return EBTNodeResult::Succeeded;
}
