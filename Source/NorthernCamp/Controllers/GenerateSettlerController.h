// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NorthernCamp/Actors/SpawnPoint.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "GenerateSettlerController.generated.h"

UCLASS()
class NORTHERNCAMP_API AGenerateSettlerController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerateSettlerController();

	USkeletalMesh* GetRandomHairStyle(bool bIsFemale);
	USkeletalMesh* GetRandomBeardStyle();
	FLinearColor GetRandomHairColor(bool bIsFemale);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY
	//Posible hair/beard styles/colors Men
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts Men")
	TMap<USkeletalMesh*, float> HairStylesMen;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts Men")
	TMap<USkeletalMesh*, float> BeardStyleMen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts Men")
	TMap<FLinearColor, float> HairColorMen;

	//Posible hair/beard styles/colors Women
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts Women")
	TMap<USkeletalMesh*, float> HairStylesWomen;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts Women")
	TMap<FLinearColor, float> HairColorWomen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
	TArray<int32> PossibleSpawnHours;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
	ASpawnPoint* SpawnPoint;

	//Variables
	EHairColor HairColorMenToAdd;
	TSubclassOf<AActor> SettlerFemaleBaseClass;
	TSubclassOf<AActor> SettlerMaleBaseClass;


	//Functions
	void GenerateCharacter();

};
