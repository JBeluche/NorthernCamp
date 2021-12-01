// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/BTS_UpdateCurrentTask.h"

UBTS_UpdateCurrentTask::UBTS_UpdateCurrentTask()
{
	NodeName = "Update current task";
}

void UBTS_UpdateCurrentTask::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	//We need to check if we need to gather resources, work, sleep or have fun

	//If water is low || diner time || work related

	//If in need of water | Gather resource: water

	//If work just finished | Gather resource: Diner ?food
	//If sleep time just finished | Gather resource: Breakfast ?food

	//Check if there is a resource need. 
	//If work | go to work branch. 



}