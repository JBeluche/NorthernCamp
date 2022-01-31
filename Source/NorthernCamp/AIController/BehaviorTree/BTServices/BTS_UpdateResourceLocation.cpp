// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/BTS_UpdateResourceLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/NorthernCampGameMode.h"
#include "NorthernCamp/AIController/AISettlerController.h"

UBTS_UpdateResourceLocation::UBTS_UpdateResourceLocation()
{
	NodeName = "Update Resource Actor";
}

void UBTS_UpdateResourceLocation::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Find the location of the resource and update the resource location blackboard value


	AAISettlerController* Controller = Cast<AAISettlerController>(OwnerComp.GetAIOwner());
	ACharacterSettler* Settler = Cast<ACharacterSettler>(Controller->GetPawn());
	AActor* ActorWithResource = nullptr;

	NavigationSystemv1 = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

		if(NavigationSystemv1)
	{
		if(Controller != nullptr || Settler != nullptr)
		{

			float NewPathLength;
			float OldPathLength;

			FResourceInfo ResourcesNeeded = Settler->ResourceManagerComp->GetCurrentResoucesToFetch();

			ANorthernCampGameMode * GameMode = Cast<ANorthernCampGameMode>(GetWorld()->GetAuthGameMode());
		
			
			if(GameMode)
			{
				for (UResourceManagerComponent* ResourceManagerComp : GameMode->ResourceController->GetResourceManagersWithResource(ResourcesNeeded.ResourceType, ResourcesNeeded.Amount))
				{

					NavigationSystemv1->GetPathLength(Settler->GetActorLocation(), ResourceManagerComp->GetOwner()->GetActorLocation(), NewPathLength);

					if(ActorWithResource == nullptr)
					{
						ActorWithResource = ResourceManagerComp->GetOwner();
						OldPathLength = NewPathLength;
					}
					else if(NewPathLength < OldPathLength)
					{
						ActorWithResource = ResourceManagerComp->GetOwner();
						OldPathLength = NewPathLength;
					}

				}
			}
		}
		else
		{
			
			UE_LOG(LogTemp, Error, TEXT("BTS_UpdateResourceLocatin: No settler or controller"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("A settler is not finding the navigation system"));
	}

	if(ActorWithResource)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), ActorWithResource);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find ActorWithResource in BTS_UpdateResourceLocatin"));
	}
	
}