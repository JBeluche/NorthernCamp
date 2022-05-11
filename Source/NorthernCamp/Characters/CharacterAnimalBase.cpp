// Copyright Creating Mountains!


#include "NorthernCamp/Characters/CharacterAnimalBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/CharacterCustomizationComponent.h"

ACharacterAnimalBase::ACharacterAnimalBase()
{
	CharacterCustomizationComponent->bHasCustomAnimation = true;
	CharacterCustomizationComponent->CharacterBodyType = EBodyType::CustomAllLevels;
}
