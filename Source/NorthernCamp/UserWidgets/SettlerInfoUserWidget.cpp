// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/UserWidgets/SettlerInfoUserWidget.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "Kismet/GameplayStatics.h"


void USettlerInfoUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ANorthernCampPlayerController* Controller = Cast<ANorthernCampPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(Controller)
	{
		ACharacterSettler* Settler = Cast<ACharacterSettler>(Controller->SelectedSettler);

		TB_SettlersName->SetText(Settler->Name);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The cast to controller has failed in widget"));

	}
}



