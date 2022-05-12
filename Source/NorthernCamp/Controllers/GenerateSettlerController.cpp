// Copyright Creating Mountains!


#include "NorthernCamp/Controllers/GenerateSettlerController.h"

#include "EngineUtils.h"
#include "NorthernCamp/Actors/SpawnPoint.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "NorthernCamp/Characters/Components/CharacterCustomizationComponent.h"

// Sets default values
AGenerateSettlerController::AGenerateSettlerController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//List of the armor and body for the settlers.
	const ConstructorHelpers::FClassFinder<AActor> BP_FemaleSettlerBase(TEXT("/Game/Blueprints/Characters/Settlers/BP_SettlerBaseFemale"));
	const ConstructorHelpers::FClassFinder<AActor> BP_MaleSettlerBase(TEXT("/Game/Blueprints/Characters/Settlers/BP_SettlerBaseMale"));
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> TestBP(TEXT("/Game/_Character/ModularCharacters/ModularParts/SK_Chr_FacialHair_Male_10"));

	SettlerFemaleBaseClass = BP_FemaleSettlerBase.Class;
	SettlerMaleBaseClass = BP_MaleSettlerBase.Class;


}

// Called when the game starts or when spawned
void AGenerateSettlerController::BeginPlay()
{
	Super::BeginPlay();

	//Generate Characters
	GenerateCharacter();


}

void AGenerateSettlerController::GenerateCharacter()
{

		if(SpawnPoint)
		{
			ACharacterBase* Char;
			bool bSpawnFemale = true;
			for(int32 i = 0; i < 15; i++)
			{
				if(bSpawnFemale == true)
				{
					Char = SpawnPoint->SpawnCharacter(SettlerFemaleBaseClass);
					bSpawnFemale = false;
				}
				else
				{
					Char = SpawnPoint->SpawnCharacter(SettlerMaleBaseClass);
					bSpawnFemale = true;
				}


				ACharacterBase* NewCharacter = Cast<ACharacterBase>(Char);
				

				if(NewCharacter)
				{

					NewCharacter->CharacterCustomizationComponent->LinearColorHair = GetRandomHairColor(NewCharacter->CharacterCustomizationComponent->bIsFemale);

					NewCharacter->CharacterCustomizationComponent->Hair = GetRandomHairStyle(NewCharacter->CharacterCustomizationComponent->bIsFemale);

					
					if(!NewCharacter->CharacterCustomizationComponent->bIsFemale)
					{
						NewCharacter->CharacterCustomizationComponent->FacialHair = GetRandomBeardStyle();

						if(NewCharacter->CharacterCustomizationComponent->Hair == nullptr)
						{
							for(int32 ite = 0; ite < 9; ite++)
							{
								if(NewCharacter->CharacterCustomizationComponent->FacialHair != nullptr)
								{
									break;
								}
								NewCharacter->CharacterCustomizationComponent->FacialHair = GetRandomBeardStyle();
							}
						}
					}

					NewCharacter->CharacterCustomizationComponent->GenerateAllMaterials();
					NewCharacter->CharacterCustomizationComponent->GenerateMeshes();
				}
			}
		}

}

USkeletalMesh* AGenerateSettlerController::GetRandomHairStyle(bool bIsFemale)
{
	TArray<USkeletalMesh*> MeshArray;
	if(bIsFemale)
	{
		for(auto& HairItareting : HairStylesWomen)
		{
			for(int32 i = 0; i < HairItareting.Value; i++)
			{
				MeshArray.Add(HairItareting.Key);
			}
		}
	}
	else
	{
		for(auto& HairItareting : HairStylesMen)
		{
			for(int32 i = 0; i < HairItareting.Value; i++)
			{
				MeshArray.Add(HairItareting.Key);
			}
		}
	}

	int32 RandomNum = FMath::RandRange(0, MeshArray.Num() - 1);
				
	return MeshArray[RandomNum];
}


USkeletalMesh* AGenerateSettlerController::GetRandomBeardStyle()
{
	TArray<USkeletalMesh*> MeshArray;

	for(auto& BeardItareting : BeardStyleMen)
	{
		for(int32 i = 0; i < BeardItareting.Value; i++)
		{
			MeshArray.Add(BeardItareting.Key);
		}
	}

	int32 RandomNum = FMath::RandRange(0, MeshArray.Num() - 1);
				
	return MeshArray[RandomNum];

}

FLinearColor AGenerateSettlerController::GetRandomHairColor(bool bIsFemale)
{
	TArray<FLinearColor> ColorArray;

	if(bIsFemale)
	{
		for(auto& ColorItareting : HairColorWomen)
		{
			for(int32 i = 0; i < ColorItareting.Value; i++)
			{
				ColorArray.Add(ColorItareting.Key);
			}
		}
	}
	else
	{
		for(auto& ColorItareting : HairColorMen)
		{
			for(int32 i = 0; i < ColorItareting.Value; i++)
			{
				ColorArray.Add(ColorItareting.Key);
			}
		}
	}

	int32 RandomNum = FMath::RandRange(0, ColorArray.Num() - 1);
				
	return ColorArray[RandomNum];

}


