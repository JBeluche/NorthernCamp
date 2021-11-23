// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSettler.h"
#include "CharacterHero.generated.h"


UENUM(BlueprintType)
enum class EHero : uint8 
{
	Will UMETA(DisplayName = "Will"),
	Trader UMETA(DisplayName = "Trader"),
	Hunter UMETA(DisplayName = "Hunter"),
	Seaclan UMETA(DisplayName = "Seaclan"),
	Miner UMETA(DisplayName = "Miner"),
	Druida UMETA(DisplayName = "Druida"),
	Alchemist UMETA(DisplayName = "Alchemist"),
	Occultist UMETA(DisplayName = "Occultist"),
	
};


UCLASS()
class NORTHERNCAMP_API ACharacterHero : public ACharacterSettler
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHero HeroEnum;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float MaxCameraDistance;
	
	ACharacterHero();
};
