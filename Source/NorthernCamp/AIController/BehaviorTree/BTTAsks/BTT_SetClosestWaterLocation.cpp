// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTTAsks/BTT_SetClosestWaterLocation.h"

UBTT_SetClosestWaterLocation::UBTT_SetClosestWaterLocation()
{
	NodeName = TEXT("Set Closest Water Location");
}

EBTNodeResult::Type UBTT_SetClosestWaterLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent();
	
	GetSelectedBlackboardKey();
}