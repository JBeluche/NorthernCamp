// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/Characters/CharacterHero.h"

#include "Components/CapsuleComponent.h"

ACharacterHero::ACharacterHero()
{
	bIsHero = true;
}

void ACharacterHero::SetIsWounded(bool bWounded)
{
	bIsWounded = bWounded;
	SetFrozen(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	bDiedOrWounded = true;
}

