// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/BTS_UpdateWaterLocation.h"

#include "NorthernCamp/AIController/AISettlerController.h"



UBTS_UpdateWaterLocation::UBTS_UpdateWaterLocation()
{
	NodeName = "Update Water Actor and Location";
}

void UBTS_UpdateWaterLocation::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) 
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UE_LOG(LogTemp, Error, TEXT("Ballsacks!!!") );


}