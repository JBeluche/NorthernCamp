// Copyright Creating Mountains!


#include "NorthernCamp/AIController/AISettlerController.h"


AAISettlerController::AAISettlerController()
{
}

void AAISettlerController::BeginPlay()
{
	if(BehaviorTree != nullptr)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
