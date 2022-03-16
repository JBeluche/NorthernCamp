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
	
	if(!Controller){

		// Apperently it fails for some.
		//UE_LOG(LogTemp, Error, TEXT("Controller cast failed!"));

		return;}

	ACharacterSettler* Settler = Cast<ACharacterSettler>(Controller->GetPawn());
	if(!Settler){UE_LOG(LogTemp, Error, TEXT("Settler cast failed!"));return;}
	if(Settler->VitalsComponent == nullptr){UE_LOG(LogTemp, Error, TEXT("Vitals cast failed"));return;}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("SelfActor"), Settler);

	//Drink water
	//Eat
	//Bring resource to work


	//Settler is simply thirsty
	if(Settler->VitalsComponent->NeedWater == true)
	{
		TArray<FResourceInfo> NewResourcesNeeded;
		FResourceInfo ResourceInfo;
		ResourceInfo.Amount = 1;
		ResourceInfo.ResourceType = EResourceType::Water;
		NewResourcesNeeded.Add(ResourceInfo);
		bool bWeHaveEnoughtResources = false;

		for(FResourceInfo ResourceNeed : NewResourcesNeeded)
		{
			if(Settler->ResourceManagerComp->CheckResourceAvailability(ResourceNeed))         
			{
				bWeHaveEnoughtResources = true;
			}
			else
			{
				bWeHaveEnoughtResources = false;
			}
         
		}
		if(!bWeHaveEnoughtResources)
		{

			Settler->ResourceManagerComp->UpdateResourceNeed(NewResourcesNeeded);
		}
		else
		{
			//Settler->ResourceManagerComp->ConsumeResources(NewResourcesNeeded);
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)ECurrentTask::FetchingResource);


		//So what if the settler has already other resources and no room to store water?
		//The resource need is dropped, since we don't need it anymore. For now at least.
		//A resouce need is added for the water. Only the water is now needed.
		//Wether you want watter or food, the choice is made in this class. Not outside of it.



		
		//IF you have water in store. Consume it. -> Set the task to consume resource
		//IF if you already, have a resource need -> Set the task to fetch resouce
		//ELSE Add resource need in the settler resource manager, with an id. -> Set the task to fetch resouce

		
		/* OLD
		if(Settler->ResourceManagerComp->GetPriorityResouceNeed().ResourceType == EResourceType::Water)
		{
			//Settler->VitalsComponent->RequestExecuted(EResourceRequest::Thirsty);
			Settler->ResourceManagerComp->ConsumeResource(Settler->ResourceManagerComp->GetPriorityResouceNeed());
			Settler->ResourceManagerComp->GetPriorityResouceNeed();
		}*/
	}
	






	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), 0);

	}


	
	//Check the CharacterSettler->CanConsumeResource. Which check the resources in hand with the resources needed to consume.


	/*if(Settler->ResourceManagerComp->GetResourceNeed().Amount != 0)
	{
		//Set the consume resource task.
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), 2);
		UE_LOG(LogTemp, Error, TEXT("Updated task to going for water!"));
	}*/

	/*else if(Settler->Character->NeedsResource == true)
	{
		//When the character pickups a resource he should remove the need for the resource. His need to consume it should remain. 
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), 1);
		UE_LOG(LogTemp, Error, TEXT("Updated task to going for diner!"));
	}
	else if(Settler->CurrentSchedule == ESettlerSchedule::Work)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), 2);
		UE_LOG(LogTemp, Error, TEXT("Updated task to going for WORK!"));

	}
	else if(Settler->CurrentSchedule == ESettlerSchedule::Sleep)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), 3);
		UE_LOG(LogTemp, Error, TEXT("Updated task to going for SLEEP!"));

	}
	else if(Settler->CurrentSchedule == ESettlerSchedule::Leisure)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), 4);
		UE_LOG(LogTemp, Error, TEXT("Updated task to going for leisure!"));

	}*/

	


	


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