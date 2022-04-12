// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTTAsks/BTT_SetFocus.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/AIController/AIControllerBase.h"
#include "NorthernCamp/AIController/BehaviorTree/BlackboardKeys/AgresorBlackboardKeys.h"

UBTT_SetFocus::UBTT_SetFocus()
{
	NodeName = TEXT("Reserve pickup spot");
}

EBTNodeResult::Type UBTT_SetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIControllerBase* AIController  = Cast<AAIControllerBase>(OwnerComp.GetAIOwner()->GetPawn()->GetController());
	ACharacterBase* Enemy = Cast<ACharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AgresorBlackboardKeys::EnnemyTarget));

	if(!AIController){UE_LOG(LogTemp,Error, TEXT("UBTT_SetFocus::ExecuteTask nullptr AIController")); return EBTNodeResult::Failed;}
	if(!Enemy){UE_LOG(LogTemp,Error, TEXT("UBTT_SetFocus::ExecuteTask nullptr EnnemyTarget")); return EBTNodeResult::Failed;}

	AIController->SetFocus(Enemy);

	return EBTNodeResult::Succeeded;
}
