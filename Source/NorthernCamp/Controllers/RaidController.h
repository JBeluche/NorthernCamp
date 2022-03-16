// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "DayNightActorController.h"
#include "GameFramework/Actor.h"
#include "NorthernCamp/Characters/CharacterBase.h"
#include "RaidController.generated.h"

enum class ECharacter : uint8 
{
	SeaRaider_01 UMETA(DisplayName = "Sea Raider 01"),

};

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

	TArray<TSubclassOf<class ACharacterBase>> RaidersClassToSpawn;

};

UCLASS()
class NORTHERNCAMP_API ARaidController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARaidController();

	//Variables
	int32 DaysSinceLastRaid;
	float CurrentBaseLevel;
	float RaidStrength;
	float LastRaidStrength; //The strength of the last raid, so you don't bring the best every time.
	
	
	//Functions
	float CalculateBaseLevel(); //Returns CurrentBaseLevel
	void SpawnRaid(FRaidInfo RaidInfo);
	bool RandomRaidCheck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TSubclassOf<class ACharacterBase> Raider_01;


	UFUNCTION() 
	void DayEnded(float CurrentDay);

};
