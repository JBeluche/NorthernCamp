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
	TestBPClass = TestBP.Object;


}

// Called when the game starts or when spawned
void AGenerateSettlerController::BeginPlay()
{
	Super::BeginPlay();

	//Generate Characters
	SetHairColorToAdd();
	GenerateCharacter();


}

void AGenerateSettlerController::GenerateCharacter()
{

	for (TActorIterator<ASpawnPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{ 
		ASpawnPoint* SpawnPoint = Cast<ASpawnPoint>(*ActorItr);

		if(SpawnPoint->CanSpawn(ACharacterSettler::StaticClass()))
		{
			
		}
		
		//ACharacterBase* NewCharacter = Cast<ACharacterBase>(SpawnPoint->SpawnCharacter(SettlerFemaleBaseClass));

		
		ACharacterBase* NewCharacter2 = Cast<ACharacterBase>(SpawnPoint->SpawnCharacter(SettlerMaleBaseClass));
	//	ACharacterBase* NewCharacter3 = Cast<ACharacterBase>(SpawnPoint->SpawnCharacter(SettlerMaleBaseClass));
		//ACharacterBase* NewCharacter4 = Cast<ACharacterBase>(SpawnPoint->SpawnCharacter(SettlerMaleBaseClass));

		
		if(NewCharacter2)
		{
			NewCharacter2->CharacterCustomizationComponent->LinearColorHair = GetRandomHairColor();

			NewCharacter2->CharacterCustomizationComponent->Hair = nullptr;
			NewCharacter2->CharacterCustomizationComponent->FacialHair = GetRandomBeardStyle();

			//NewCharacter2->CharacterCustomizationComponent->GenerateAllMaterials();
			NewCharacter2->CharacterCustomizationComponent->GenerateMeshes();
		}
	/*	if(NewCharacter3)
		{
			NewCharacter3->CharacterCustomizationComponent->LinearColorHair = GetRandomHairColor();

			NewCharacter3->CharacterCustomizationComponent->Hair = GetRandomHairStyle();
			NewCharacter3->CharacterCustomizationComponent->FacialHair = GetRandomBeardStyle();

			NewCharacter3->CharacterCustomizationComponent->GenerateAllMaterials();
			NewCharacter3->CharacterCustomizationComponent->GenerateMeshes();
		}
		if(NewCharacter4)
		{
			NewCharacter4->CharacterCustomizationComponent->LinearColorHair = GetRandomHairColor();

			NewCharacter4->CharacterCustomizationComponent->Hair = GetRandomHairStyle();
			NewCharacter4->CharacterCustomizationComponent->FacialHair = GetRandomBeardStyle();

			NewCharacter4->CharacterCustomizationComponent->GenerateAllMaterials();
			NewCharacter4->CharacterCustomizationComponent->GenerateMeshes();
		}*/
	}
}

USkeletalMesh* AGenerateSettlerController::GetRandomHairStyle()
{
	float TotalMen = 0.0f;
	TMap<USkeletalMesh*, float> HairStylesInMap;
	
	//Calculate how many settlers on map and how many beards by type
	for (TActorIterator<ACharacterSettler> Settler(GetWorld()); Settler; ++Settler)
	{
		if(Settler)
		{
			if(!Settler->CharacterCustomizationComponent->bIsFemale)
			{
				UE_LOG(LogTemp, Error, TEXT("%s is none female"), *Settler->GetName());

				TotalMen++;
				if(HairStylesInMap.Contains(Settler->CharacterCustomizationComponent->Hair))
				{
					HairStylesInMap.Emplace(Settler->CharacterCustomizationComponent->Hair, (HairStylesInMap[Settler->CharacterCustomizationComponent->Hair] + 1.0f));
				}
				else
				{
					HairStylesInMap.Add(Settler->CharacterCustomizationComponent->Hair, 1);
				}

			}
		}
	}

	//Calculate which beard to set using the percentages allowed in the controller and which ones there are already in level
	//For each beard we can use
	for(auto& SKHair : HairStylesMen)
	{
		//If the beard is already in the level
		if(HairStylesInMap.Contains(SKHair.Key))
		{
			//Check if there are to much of it. Beard amount, times 100, divided by total men = PercentageOfThisBeardType ? lower then allowed.
			if(HairStylesInMap[SKHair.Key] * 100.0f / TotalMen < HairStylesMen[SKHair.Key])
			{
				//If not, use it
				return SKHair.Key;
			}
		}
		else
		{
			//If it does'nt exists yet, just add it.
			return SKHair.Key;
		}
	}
	return nullptr;
}


USkeletalMesh* AGenerateSettlerController::GetRandomBeardStyle()
{
	float TotalMen = 0.0f;
	
	TMap<USkeletalMesh*, float> BeardsInMap;

	//Calculate how many settlers on map and how many beards by type
	for (TActorIterator<ACharacterSettler> Settler(GetWorld()); Settler; ++Settler)
	{
		if(Settler)
		{
			if(!Settler->CharacterCustomizationComponent->bIsFemale)
			{
				TotalMen++;
				if(BeardsInMap.Contains(Settler->CharacterCustomizationComponent->FacialHair))
				{
					BeardsInMap.Emplace(Settler->CharacterCustomizationComponent->FacialHair, (BeardsInMap[Settler->CharacterCustomizationComponent->FacialHair] + 1.0f));
				}
				else
				{
					BeardsInMap.Add(Settler->CharacterCustomizationComponent->FacialHair, 1);
				}

			}
		}
	}

	//Calculate which beard to set using the percentages allowed in the controller and which ones there are already in level
	//For each beard we can use
	for(auto& SKBeard : BeardStyleMen)
	{
		//If the beard is already in the level
		if(BeardsInMap.Contains(SKBeard.Key))
		{
			//Check if there are to much of it. Beard amount, times 100, divided by total men = PercentageOfThisBeardType ? lower then allowed.
			if(BeardsInMap[SKBeard.Key] * 100.0f / TotalMen < BeardStyleMen[SKBeard.Key])
			{
				//If not, use it
				return SKBeard.Key;
			}
		}
		else
		{
			//If it does'nt exists yet, just add it.
			return SKBeard.Key;
		}
	}
	return nullptr;
}

FLinearColor AGenerateSettlerController::GetRandomHairColor()
{
	float TotalMen = 0.0f;
	
	TMap<FLinearColor, float> HairColorsInMap;

	//Calculate how many settlers on map and how many beards by type
	for (TActorIterator<ACharacterSettler> Settler(GetWorld()); Settler; ++Settler)
	{
		if(Settler)
		{
			if(!Settler->CharacterCustomizationComponent->bIsFemale)
			{
				TotalMen++;
				if(HairColorsInMap.Contains(Settler->CharacterCustomizationComponent->LinearColorHair))
				{
					HairColorsInMap.Emplace(Settler->CharacterCustomizationComponent->LinearColorHair, (HairColorsInMap[Settler->CharacterCustomizationComponent->LinearColorHair] + 1.0f));
				}
				else
				{
					HairColorsInMap.Add(Settler->CharacterCustomizationComponent->LinearColorHair, 1);
				}

			}
		}
	}
	
	//Calculate which beard to set using the percentages allowed in the controller and which ones there are already in level
	//For each beard we can use
	for(auto& LColor : HairColorMen)
	{
		//If the beard is already in the level
		if(HairColorsInMap.Contains(LColor.Key))
		{
			//Check if there are to much of it. Beard amount, times 100, divided by total men = PercentageOfThisBeardType ? lower then allowed.
			if(HairColorsInMap[LColor.Key] * 100.0f / TotalMen < HairColorMen[LColor.Key])
			{
				//If not, use it
				return LColor.Key;
			}
		}
		else
		{
			//If it does'nt exists yet, just add it.
			return LColor.Key;
		}
	}
	FLinearColor Blank;

	return Blank;

	
	/*
	FLinearColor Color;
	SetHairColorToAdd();
	for(FHairValue ColorStruct : HairColorMenArray)
	{
		if(HairColorMenToAdd == ColorStruct.HairColorID)
		{
			Color =	ColorStruct.LinearColor;
		}
	}
	return Color;*/
}

void AGenerateSettlerController::SetHairColorToAdd()
{
	
	float TotalBlondeHairMen = 0;
	float TotalBrownHairMen = 0;
	float TotalAmountOfCharacters = 0;
	
	//Get all characters on the map
	for (TActorIterator<ACharacterSettler> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{ 
		ACharacterSettler* Settler = Cast<ACharacterSettler>(*ActorItr);
		if(Settler->HairColorEnum == EHairColor::Blonde)
		{
			TotalBlondeHairMen = TotalBlondeHairMen + 1.0f;
		}
		else if(Settler->HairColorEnum == EHairColor::Brown)
		{
			TotalBrownHairMen = TotalBrownHairMen + 1.0f;
		}
		TotalAmountOfCharacters++;
	}

	float PercentageOfBrownHairCurrently = (TotalBrownHairMen * 100) / TotalAmountOfCharacters;
	float PercentageOfBlondeHairCurrently = (TotalBlondeHairMen * 100) / TotalAmountOfCharacters;

	float BrownHairedPerTen;
	float BlondeHairedPerTen;

	//Get hair colors percentages by adding all of them together.
	for(FHairValue ColorStruct : HairColorMenArray) 
	{ 
		if(ColorStruct.HairColorID == EHairColor::Blonde)
		{
			BlondeHairedPerTen =	ColorStruct.AmountPerTen;
		}
		if(ColorStruct.HairColorID == EHairColor::Brown)
		{
			BrownHairedPerTen =	ColorStruct.AmountPerTen;
		}
	}
	
	float PercentageOfBrownHairDesired = (BrownHairedPerTen * 100) / TotalAmountOfCharacters;
	float PercentageOfBlondeHairDesired = (BlondeHairedPerTen * 100) / TotalAmountOfCharacters;

	if(PercentageOfBrownHairCurrently < PercentageOfBrownHairDesired)
	{
		HairColorMenToAdd = EHairColor::Brown;
	}
	else if(PercentageOfBlondeHairCurrently < PercentageOfBlondeHairDesired)
	{
		HairColorMenToAdd = EHairColor::Blonde;
	}

}

