// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SlideWhenStuck.generated.h"

/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API USlideWhenStuck : public UBTService
{
	GENERATED_BODY()

public:
	USlideWhenStuck();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;


	
};
