// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_UpdateEnemyTarget.generated.h"

/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UBTS_UpdateEnemyTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTS_UpdateEnemyTarget();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
	
};
