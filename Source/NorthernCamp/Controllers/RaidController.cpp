// Copyright Creating Mountains!


#include "NorthernCamp/Controllers/RaidController.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "NorthernCamp/NorthernCampGameMode.h"
#include "NorthernCamp/Actors/SpawnPoint.h"
#include "NorthernCamp/Characters/CharacterSettler.h"

ARaidController::ARaidController()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Raider01(TEXT("Blueprint'/Game/Blueprints/Characters/SeaRaiders/SeaRainder_01.SeaRainder_01'"));
	if (BP_Raider01.Object){
		Raider_01 = (UClass*)BP_Raider01.Object->GeneratedClass;
	}

	//Characters blueprint?
}

void ARaidController::BeginPlay()
{
	Super::BeginPlay();

	DaysSinceLastRaid = 0;
	ANorthernCampGameMode* GameMode = Cast<ANorthernCampGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	DayEnded(1);

	if(GameMode) 
	{ 
		//GameMode->DayNightController->ADayEnded.AddDynamic(this, &ARaidController::DayEnded); 
	}
	
}

void ARaidController::DayEnded(float CurrentDay)
{
	if(RandomRaidCheck())
	{
		FRaidInfo RaidInfo;

		RaidInfo.RaidersClassToSpawn.Add(Raider_01);
		RaidInfo.RaidersClassToSpawn.Add(Raider_01);
		RaidInfo.RaidersClassToSpawn.Add(Raider_01);
		RaidInfo.Faction = EFactions::Raider;
		
		SpawnRaid(RaidInfo);
	}
}

//For now I only check the amount of settler and send less than the total to fight
//At some point characters will have strength levels based on their stats.

float ARaidController::CalculateBaseLevel()
{
	CurrentBaseLevel = 0;
	for (TActorIterator<ACharacterSettler> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{ 
		ACharacterSettler*  Settler = Cast<ACharacterSettler>(*ActorItr);
		if(Settler->Faction == EFactions::Novard)
		{
			CurrentBaseLevel++;
		}
	}

	return CurrentBaseLevel;
}

void ARaidController::SpawnRaid(FRaidInfo RaidInfo)
{
	//Get all the spawnpoints where you can spawn the following raid.
	for (TActorIterator<ASpawnPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{ 
		ASpawnPoint* SpawnPoint = Cast<ASpawnPoint>(*ActorItr);
		
		if(SpawnPoint->AllowedFactions.Contains(RaidInfo.Faction))
		{
			//Check how many people you can spawn. SpawnRaiders(TMap<ECharacter, int32> RaidersToSpawn)
			// SpawnPoint->MaxPeopleToSpawn. Look how to subtrack raiders, since there is not always room on one spawn.
			SpawnPoint->SpawnRaiders(RaidInfo.RaidersClassToSpawn);

			
		}
	}
	//Filter by the ones that allow the current faction you want to spawn.
	
}

bool  ARaidController::RandomRaidCheck()
{
	//Simply spawn every day for now.
	return true;
}




