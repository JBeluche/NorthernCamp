// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_UpdateResourceLocation.generated.h"

class UNavigationSystemV1;

UCLASS()
class NORTHERNCAMP_API UBTS_UpdateResourceLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTS_UpdateResourceLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

	UNavigationSystemV1* NavigationSystemv1;
	
};
