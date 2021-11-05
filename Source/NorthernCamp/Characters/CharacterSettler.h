// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"

#include "CharacterSettler.generated.h"

class UVitalsComponent;

UCLASS()
class NORTHERNCAMP_API ACharacterSettler : public ACharacterBase
{
	GENERATED_BODY()

public:
	ACharacterSettler();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UVitalsComponent* VitalsComponent;

	UVitalsComponent* GetCharacterVitalsComponent();

	bool bIsHero = false;
	
};
