// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_ReservePickupSpot.generated.h"

/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UBTT_ReservePickupSpot : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_ReservePickupSpot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	
};
