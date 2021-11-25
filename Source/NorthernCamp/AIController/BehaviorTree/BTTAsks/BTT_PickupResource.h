// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_PickupResource.generated.h"

/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UBTT_PickupResource : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_PickupResource();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
