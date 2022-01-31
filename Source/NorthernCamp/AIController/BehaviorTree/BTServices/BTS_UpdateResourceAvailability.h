// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_UpdateResourceAvailability.generated.h"

/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UBTS_UpdateResourceAvailability : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTS_UpdateResourceAvailability();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

};
