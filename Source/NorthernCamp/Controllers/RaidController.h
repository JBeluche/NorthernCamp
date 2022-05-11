// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "DayNightActorController.h"
#include "GameFramework/Actor.h"
#include "NorthernCamp/Characters/CharacterBase.h"
#include "RaidController.generated.h"

USTRUCT(BlueprintType)
struct FRaidInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raid Settings")
	EFactions Faction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raid Settings")
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raid Settings")
	int32 HourToSpawn;

	TArray<TSubclassOf<AActor>> ClassToSpawn;

};

UCLASS()
class NORTHERNCAMP_API ARaidController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARaidController();

	//Variables
	float CurrentBaseLevel;
	float RaidStrength;
	float LastRaidStrength; //The strength of the last raid, so you don't bring the best every time.
	TArray<EFactions> FactionsRaidPriority;
	
	
	//Functions
	float GetBaseLevel(); //Returns CurrentBaseLevel
	FRaidInfo GetRaid(float CurrentDay);
	FRaidInfo CreateRaid(EFactions Faction);


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Rate", meta = (AllowPrivateAccess = "true"))
	TMap<EFactions, int32> DaysSinceLastRaid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Rate", meta = (AllowPrivateAccess = "true"))
	TMap<EFactions, int32> FactionSpawnDayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Rate", meta = (AllowPrivateAccess = "true"))
	TMap<EFactions, int32> FactionSpawnDayRateRandomBuffer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Rate", meta = (AllowPrivateAccess = "true"))
	TMap<EFactions, int32> FactionsStartingHourSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Rate", meta = (AllowPrivateAccess = "true"))
	TMap<EFactions, int32> FactionsEndingHourSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Rate", meta = (AllowPrivateAccess = "true"))
	ADayNightActorController* DayNightController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TSubclassOf<AActor> Raider01BlueprintClass;
	TSubclassOf<AActor> Bandit01BlueprintClass;
	TSubclassOf<AActor> Wolf01BlueprintClass;
	FRaidInfo RaidToSpawn;

	UFUNCTION() 
	void DayEnded(float CurrentDay);

	UFUNCTION() 
	void CheckRaid(float CurrentHour);
	
	void SpawnRaid(FRaidInfo RaidInfo);

	//Can be the future, can be the past.
	TMap<EFactions, int32> FactionLastRaidDay;
	TMap<EFactions, int32> FactionPlannedRaidDay;


};
