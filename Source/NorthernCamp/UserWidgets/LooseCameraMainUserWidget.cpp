// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/UserWidgets/LooseCameraMainUserWidget.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "NorthernCamp/Characters/CharacterHero.h"

bool ULooseCameraMainUserWidget::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success) return false;

	if (!ensure(CampView != nullptr)) return false;
	CampView->OnClicked.AddDynamic(this, &ULooseCameraMainUserWidget::SwitchToCamp);
	
	if (!ensure(ButtonWill != nullptr)) return false;
	ButtonWill->OnClicked.AddDynamic(this, &ULooseCameraMainUserWidget::SwitchToWill);

	if (!ensure(ButtonTrader != nullptr)) return false;
	ButtonTrader->OnClicked.AddDynamic(this, &ULooseCameraMainUserWidget::SwitchToTrader);

	PlayerController = Cast<ANorthernCampPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	return true;
}

void ULooseCameraMainUserWidget::SwitchToCamp()
{
	//PlayerController->SwitchPawn(PlayerController->ECurrentPawn::CAMP);
}


void ULooseCameraMainUserWidget::SwitchToWill()
{
	PlayerController->SetSelectedHero(EHero::Will);
	UE_LOG(LogTemp, Warning, TEXT("Will click"));

}
void ULooseCameraMainUserWidget::SwitchToTrader()
{
	PlayerController->SetSelectedHero(EHero::Trader);
	UE_LOG(LogTemp, Warning, TEXT("Trader click"));
}
void ULooseCameraMainUserWidget::SwitchToHunter()
{
	
}
void ULooseCameraMainUserWidget::SwitchToSeaclan()
{
	
}
void ULooseCameraMainUserWidget::SwitchToMinedweler()
{
	
}
void ULooseCameraMainUserWidget::SwitchToDruida()
{
	
}
void ULooseCameraMainUserWidget::SwitchToAlchemist()
{
	
}
void ULooseCameraMainUserWidget::SwitchToOccultist()
{
	
}