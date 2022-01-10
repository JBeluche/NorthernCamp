// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/BTS_UpdateCurrentTask.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/AIController/AISettlerController.h"
#include "NorthernCamp/CharacterComponents/VitalsComponent.h"

UBTS_UpdateCurrentTask::UBTS_UpdateCurrentTask()
{
	NodeName = "Update current task";
}

void UBTS_UpdateCurrentTask::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{

	AAISettlerController* Controller = Cast<AAISettlerController>(OwnerComp.GetAIOwner());
	ACharacterSettler* Settler = Cast<ACharacterSettler>(Controller->GetPawn());


	if(!Controller){UE_LOG(LogTemp, Error, TEXT("Controller cast failed!"));return;}
	if(!Settler){UE_LOG(LogTemp, Error, TEXT("Settler cast failed!"));return;}
	if(Settler->VitalsComponent == nullptr){UE_LOG(LogTemp, Error, TEXT("Vitals cast failed"));return;}
	
	if(Settler->VitalsComponent->NeedWater == true)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), 1);
		//UE_LOG(LogTemp, Error, TEXT("WATER!"));
	}
	else if(Settler->VitalsComponent->NeedFood == true)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), 1);
		//UE_LOG(LogTemp, Error, TEXT("FOOD!"));
	}
	else if(Settler->CurrentSchedule == ESettlerSchedule::Work)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), 2);
		//UE_LOG(LogTemp, Error, TEXT("WORK!"));
	}
	else if(Settler->CurrentSchedule == ESettlerSchedule::Sleep)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), 3);
		//UE_LOG(LogTemp, Error, TEXT("SLEEP!"));
	}
	else if(Settler->CurrentSchedule == ESettlerSchedule::Leisure)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), 4);
		//UE_LOG(LogTemp, Error, TEXT("LEASURE!"));
	}

	


	


	//If you have water in your hand, task is drink it
		//If you don't but are thirsty, task is gather resource

	//If you need to sleep but are thirsty? Obviously you will drink if you need to before sleep. But if there is no water before sleep then you go to sleep with less.
	//This can mean that you are starving of thirst
	//
	//The task gather resouce happens if there is something in the needed resource list. This can be added as far as i know now only by the vitals(checked here), work branch, and diner bell. 
	//The need for food, work resource and water should not be needed in the slaap phase.
	//Before sleep, callculate if you need to drink(enought water for the night)

		
	//We need to check if we need to gather resources, work, sleep or have fun

	//If water is low || diner time || work related

	//If in need of water | Gather resource: water

	//If work just finished | Gather resource: Diner ?food
	//If sleep time just finished | Gather resource: Breakfast ?food

	//Check if there is a resource need. 
	//If work resource need, set the task to get resource.

	


	//If the need for a resource: Wood, food and water. Water has a priotrity, but it really depends on where the resource are all located. 



}