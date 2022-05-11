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

	/*static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Raider01(TEXT("Blueprint'/Game/Blueprints/Characters/SeaRaiders/SeaRainder_01.SeaRainder_01'"));
	if (BP_Raider01.Object){
		Raider_01 = (UClass*)BP_Raider01.Object->GeneratedClass;
	}
*/
	const ConstructorHelpers::FClassFinder<AActor> BP_Raider01(TEXT("/Game/Blueprints/Characters/SeaRaiders/SeaRainder_01"));
	const ConstructorHelpers::FClassFinder<AActor> BP_Wolf01(TEXT("/Game/Blueprints/Characters/TheForest/Wolf/BP_Wolf"));
	const ConstructorHelpers::FClassFinder<AActor> BP_Bandit01(TEXT("/Game/Blueprints/Characters/Bandits/Bandit_01"));

	Raider01BlueprintClass = BP_Raider01.Class;
	Wolf01BlueprintClass = BP_Wolf01.Class;
	Bandit01BlueprintClass = BP_Bandit01.Class;

	//Characters blueprint?
}

void ARaidController::BeginPlay()
{
	Super::BeginPlay();

	ANorthernCampGameMode* GameMode = Cast<ANorthernCampGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if(DayNightController)
	{
		DayNightController->ADayEnded.AddDynamic(this, &ARaidController::DayEnded);
		DayNightController->AnHourStruck.AddDynamic(this, &ARaidController::CheckRaid);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ARaidController::BeginPlay() nullptr Daynight"));
	}

}

void ARaidController::DayEnded(float CurrentDay)
{
	RaidToSpawn = GetRaid(CurrentDay);

}

void ARaidController::CheckRaid(float CurrentHour)
{
	bool bSpawnAtMidnight = false;
	if(CurrentHour == 0 && RaidToSpawn.HourToSpawn == 24)
	{
		bSpawnAtMidnight = true;
	}
	
	if(RaidToSpawn.HourToSpawn == CurrentHour || bSpawnAtMidnight)
	{
		SpawnRaid(RaidToSpawn);
	}
}

//For now I only check the amount of settler and send less than the total to fight
//At some point characters will have strength levels based on their stats.

float ARaidController::GetBaseLevel()
{
	//The amount of people for now.
	CurrentBaseLevel = 0;
	
	for (TActorIterator<ACharacterSettler> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{ 
		ACharacterSettler*  Settler = Cast<ACharacterSettler>(*ActorItr);
	
		CurrentBaseLevel++;
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
			SpawnPoint->SpawnRaiders(RaidInfo.ClassToSpawn);

			
		}
	}

	
}

FRaidInfo ARaidController::GetRaid(float CurrentDay)
{
	
	//Loop FactionsRaidPriority for each faction
	if(GetBaseLevel() > 2)
	{
		for (EFactions Faction : FactionsRaidPriority)
		{
			//If it has a planned raid day. Is it today? Create raid. Is it not, continue
			if(FactionPlannedRaidDay.Contains(Faction))
			{
				if(FactionPlannedRaidDay[Faction] == CurrentDay)
				{
					return CreateRaid(Faction);
				}
				else
				{
					continue;
				}
			}
			if(FactionSpawnDayRate.Contains(Faction))
			{
				//This is simply to check if the last raid was long ago enought. 
				bool LastRaidOverdue = false;
				if(FactionLastRaidDay.Contains(Faction))
				{
					if(FactionLastRaidDay[Faction] >= FactionSpawnDayRate[Faction])
					{
						LastRaidOverdue = true;
					}
				}
				
				//If the amount of days since game start, or since last raid < faction spawn rate.
				if(CurrentDay >=  FactionSpawnDayRate[Faction] || LastRaidOverdue)
				{
					//Get random day to spawn, if it's today, return, if its not, save in planned day and pass.
					if(FactionSpawnDayRateRandomBuffer.Contains(Faction))
					{
						//Get random day
						int32 RandomNum = FMath::RandRange(0, FactionSpawnDayRateRandomBuffer[Faction] - 1);
						if(RandomNum == 0)
						{
							return CreateRaid(Faction);
						}
						else
						{
							if(FactionPlannedRaidDay.Contains(Faction))
							{
								FactionPlannedRaidDay.Emplace(Faction, (CurrentDay + RandomNum));
							}
							else
							{
								FactionPlannedRaidDay.Add(Faction, (CurrentDay + RandomNum));
							}
						}
					}
					else
					{
						return CreateRaid(Faction);
					}
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("ARaidController::GetRaid One faction cannot spawn, it has not spawn rate set."));
			}
		}
	}
	//Default raid is wolfs
	return CreateRaid(EFactions::Wolf);
}

FRaidInfo ARaidController::CreateRaid(EFactions Faction)
{
	//Check the base level
	//Create a raid info based on the base level
	float BaseLevel = GetBaseLevel() - 1;

	FRaidInfo RaidInfo;
	RaidInfo.Faction = Faction;
	RaidInfo.HourToSpawn = 2;
	//UE_LOG(LogTemp, Error, TEXT("Setting"));


	if(FactionsStartingHourSpawn.Contains(Faction) && FactionsStartingHourSpawn.Contains(Faction))
	{
		RaidInfo.HourToSpawn = FMath::RandRange(FactionsStartingHourSpawn[Faction], FactionsEndingHourSpawn[Faction]);
		UE_LOG(LogTemp, Error, TEXT("Setup random hour"), RaidInfo.HourToSpawn);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ARaidController::CreateRaid One faction has no starting or ending time for spawning. Keeping it to default: 02:00"));
	}

	//Each factions has its own class to spawn. For now I only check the base level and spawn a little bit less ennemies.
	if(Faction == EFactions::Wolf)
	{
		if(BaseLevel < 2)
		{
			RaidInfo.ClassToSpawn.Add(Wolf01BlueprintClass);
			RaidInfo.ClassToSpawn.Add(Wolf01BlueprintClass);
		}
		else
		{
			for(int32 i = 0; i < BaseLevel; i++)
			{
				RaidInfo.ClassToSpawn.Add(Wolf01BlueprintClass);
			}
		}
	}
	else if(Faction == EFactions::Bandit)
	{
		for(int32 i = 2; i < BaseLevel; i++)
		{
			RaidInfo.ClassToSpawn.Add(Bandit01BlueprintClass);
		}
	}
	else if(Faction == EFactions::SeaClan)
	{
		for(int32 i = 2; i < BaseLevel; i++)
		{
			RaidInfo.ClassToSpawn.Add(Raider01BlueprintClass);
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Hour to spawn: %i"), RaidInfo.HourToSpawn);

	return RaidInfo;
}





