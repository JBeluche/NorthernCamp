// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "NavigationSystem.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_UpdateWaterLocation.generated.h"

/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UBTS_UpdateWaterLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTS_UpdateWaterLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

	UNavigationSystemV1* NavigationSystemv1;

};
