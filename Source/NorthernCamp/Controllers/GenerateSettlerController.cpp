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
	GenerateCharacter();


}

void AGenerateSettlerController::GenerateCharacter()
{

	for (TActorIterator<ASpawnPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{ 
		ASpawnPoint* SpawnPoint = Cast<ASpawnPoint>(*ActorItr);

		if(SpawnPoint->CanSpawn(ACharacterSettler::StaticClass()))
		{
			//ACharacterBase* NewCharacter = Cast<ACharacterBase>(SpawnPoint->SpawnCharacter(SettlerFemaleBaseClass));

			//ACharacterBase* NewCharacter4 = Cast<ACharacterBase>(SpawnPoint->SpawnCharacter(SettlerMaleBaseClass));
			/*for(int32 i = 0; i < 15; i++)
			{
				Char = SpawnPoint->SpawnCharacter(SettlerMaleBaseClass);

				ACharacterBase* NewCharacter = Cast<ACharacterBase>(Char);

				if(NewCharacter)
				{
					NewCharacter->CharacterCustomizationComponent->bIsFemale = false;

					NewCharacter->CharacterCustomizationComponent->LinearColorHair = GetRandomHairColor();

					NewCharacter->CharacterCustomizationComponent->Hair = GetRandomHairStyle();
					NewCharacter->CharacterCustomizationComponent->FacialHair = GetRandomBeardStyle();

					NewCharacter->CharacterCustomizationComponent->GenerateAllMaterials();
					NewCharacter->CharacterCustomizationComponent->GenerateMeshes();
				}

			}*/
			
		}
		
		


		
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
	int32 RandomNum = FMath::RandRange(0, (HairStylesMen.Num() - 1));
	int32 CurrentIteration = 0;
	USkeletalMesh* RandomHairStyle = nullptr;

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
		//If it does'nt exists yet, just add it add a random one.
		if(CurrentIteration == RandomNum)
		{
			RandomHairStyle = SKHair.Key;
		}
		CurrentIteration++;

	}

	return RandomHairStyle;
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
	int32 RandomNum = FMath::RandRange(0, (BeardStyleMen.Num() - 1));
	int32 CurrentIteration = 0;
	USkeletalMesh* RandomBeardStyle = nullptr;

	
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
		//If it does'nt exists yet, add a random one.
		if(CurrentIteration == RandomNum)
		{
			RandomBeardStyle = SKBeard.Key;
		}
		CurrentIteration++;

	}
	return RandomBeardStyle;
}

FLinearColor AGenerateSettlerController::GetRandomHairColor()
{
	int32 TotalMen = 0;
	
	TMap<FLinearColor, int32> HairColorsInMap;

	//Calculate how many settlers on map and how many beards by type
	for (TActorIterator<ACharacterSettler> Settler(GetWorld()); Settler; ++Settler)
	{
		if(Settler)
		{
			if(!Settler->bIsHero)
			{
				
				UE_LOG(LogTemp, Error, TEXT("Looping settlers"));
					
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
	}
	
	//Calculate which beard to set using the percentages allowed in the controller and which ones there are already in level
	//For each beard we can use
	TMap<FLinearColor, float> MissingColors;
	TMap<FLinearColor, float> ColorsLeft;

	FLinearColor Blank;

	//You want to get a random one first, but then you want to get one that has hair that is not yet in the game.
		//The problem is that you are going to get all different colors, then it will be 
	


	//Filter colors that are already on the map.
	for(auto& LColor : HairColorMen)
	{
		UE_LOG(LogTemp, Error, TEXT("Looping color"), LColor.Value, HairColorsInMap.Num(), TotalMen, LColor.Value);

		//If the beard is already in the level
		if(HairColorsInMap.Contains(LColor.Key))
		{
			UE_LOG(LogTemp, Error, TEXT("Color: %f, has a total of %i men using it | TotalMen %i"), LColor.Value, HairColorsInMap[LColor.Key], TotalMen);


			//Check if there are to much of it. Beard amount, times 100, divided by total men = PercentageOfThisBeardType ? lower then allowed.
			if(HairColorsInMap[LColor.Key] * 100.0f / TotalMen < LColor.Value)
			{
				//If not, use it
				UE_LOG(LogTemp, Error, TEXT("There is not enought of these men, adding more"), LColor.Value);

				return LColor.Key;
			}
				//UE_LOG(LogTemp, Error, TEXT("Adding color to missing array: %f"), LColor.Value);

				MissingColors.Add(LColor.Key, 1.0f);
		}
		else
		{

			MissingColors.Add(LColor.Key, 1.0f);
			UE_LOG(LogTemp, Error, TEXT("Adding color to missing array: %f"), LColor.Value);


		}
	}

	//If all the colors on the map already surpase their percentage, add a random 
	int32 RandomNum = FMath::RandRange(0, MissingColors.Num() - 1);

	//Being stupid
	int32 CurrentlyAtIndex = 0;
	for(auto& ColorToReturn : MissingColors)
	{
		UE_LOG(LogTemp, Error, TEXT("At index %i | random is %i | Array size: %i"), CurrentlyAtIndex, RandomNum, MissingColors.Num());
		if(CurrentlyAtIndex == RandomNum)
		{
			UE_LOG(LogTemp, Error, TEXT("Color setting to: %s"), *ColorToReturn.Key.ToString());

			return ColorToReturn.Key;
		}
		CurrentlyAtIndex++;
	}

	return Blank;


}


