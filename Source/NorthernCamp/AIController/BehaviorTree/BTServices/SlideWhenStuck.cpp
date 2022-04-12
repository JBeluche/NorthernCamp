// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/SlideWhenStuck.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "NorthernCamp/Characters/CharacterBase.h"

USlideWhenStuck::USlideWhenStuck()
{
	NodeName = "Slide Self and Others when touching";
}

void USlideWhenStuck::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) 
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	

}