// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "GenerateSettlerController.generated.h"

USTRUCT(BlueprintType)
struct FHairValue
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	EHairColor HairColorID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	FLinearColor LinearColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	float AmountPerTen;
};


UCLASS()
class NORTHERNCAMP_API AGenerateSettlerController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerateSettlerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	//UPROPERTY
	//Posible hair/beard styles/colors Men
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	TMap<USkeletalMesh*, float> HairStylesMen;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	TArray<FHairValue> HairColorMenArray;
	
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
	void SetHairColorToAdd();
	void GenerateCharacter();
	USkeletalMesh* GetRandomHairStyle();
	USkeletalMesh* GetRandomBeardStyle();
	FLinearColor GetRandomHairColor();
};
