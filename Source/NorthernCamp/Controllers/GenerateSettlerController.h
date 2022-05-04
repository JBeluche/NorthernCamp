// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "GenerateSettlerController.generated.h"

UCLASS()
class NORTHERNCAMP_API AGenerateSettlerController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerateSettlerController();

	USkeletalMesh* GetRandomHairStyle();
	USkeletalMesh* GetRandomBeardStyle();
	FLinearColor GetRandomHairColor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	//UPROPERTY
	//Posible hair/beard styles/colors Men
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	TMap<USkeletalMesh*, float> HairStylesMen;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	TMap<USkeletalMesh*, float> BeardStyleMen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	TMap<FLinearColor, float> HairColorMen;

	USkeletalMesh* TestBPClass;
	
	//Posible hair/beard styles/colors Women
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	TMap<USkeletalMesh*, float> HairStylesWomen;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	TMap<FLinearColor, float> HairColorWomen;

	//Variables
	EHairColor HairColorMenToAdd;
	TSubclassOf<AActor> SettlerFemaleBaseClass;
	TSubclassOf<AActor> SettlerMaleBaseClass;


	//Functions
	void GenerateCharacter();

};
