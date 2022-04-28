// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/Universal/Components/UHeroBarWidget.h"

#include "EngineUtils.h"
#include "Components/Button.h"
#include "NorthernCamp/NorthernCampPlayerController.h"


bool UUHeroBarWidget::Initialize()
{
	bool Success = Super::Initialize();

	//Foreach character that is in the world. Display the button.
	B_Will->SetVisibility(ESlateVisibility::Collapsed);
	B_Hunter->SetVisibility(ESlateVisibility::Collapsed);
	B_Trader->SetVisibility(ESlateVisibility::Collapsed);
	B_SeaRaider->SetVisibility(ESlateVisibility::Collapsed);
	B_MineDweller->SetVisibility(ESlateVisibility::Collapsed);
	B_Druida->SetVisibility(ESlateVisibility::Collapsed);
	B_Alchemist->SetVisibility(ESlateVisibility::Collapsed);
	B_Occultist->SetVisibility(ESlateVisibility::Collapsed);

	for (TActorIterator<ACharacterHero> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{ 
		if(Cast<ACharacterHero>(*ActorItr))
		{
			if(Cast<ACharacterHero>(*ActorItr)->HeroEnum == EHero::Will)
			{
				B_Will->SetVisibility(ESlateVisibility::Visible);
			}
			else if(Cast<ACharacterHero>(*ActorItr)->HeroEnum == EHero::Hunter)
			{
				B_Hunter->SetVisibility(ESlateVisibility::Visible);
			}
			else if(Cast<ACharacterHero>(*ActorItr)->HeroEnum == EHero::Trader)
			{
				B_Trader->SetVisibility(ESlateVisibility::Visible);
			}
			else if(Cast<ACharacterHero>(*ActorItr)->HeroEnum == EHero::SeaRaider)
			{
				B_SeaRaider->SetVisibility(ESlateVisibility::Visible);
			}
			else if(Cast<ACharacterHero>(*ActorItr)->HeroEnum == EHero::MineDweller)
			{
				B_MineDweller->SetVisibility(ESlateVisibility::Visible);
			}
			else if(Cast<ACharacterHero>(*ActorItr)->HeroEnum == EHero::Druida)
			{
				B_Druida->SetVisibility(ESlateVisibility::Visible);
			}
			else if(Cast<ACharacterHero>(*ActorItr)->HeroEnum == EHero::Alchemist)
			{
				B_Alchemist->SetVisibility(ESlateVisibility::Visible);
			}
			else if(Cast<ACharacterHero>(*ActorItr)->HeroEnum == EHero::Occultist)
			{
				B_Occultist->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
	
	if (!ensure(B_Will != nullptr)) return false;
	B_Will->OnClicked.AddDynamic(this, &UUHeroBarWidget::SwitchToWill);

	if (!ensure(B_Hunter != nullptr)) return false;
	B_Hunter->OnClicked.AddDynamic(this, &UUHeroBarWidget::SwitchToHunter);

	if (!ensure(B_Trader != nullptr)) return false;
	B_Trader->OnClicked.AddDynamic(this, &UUHeroBarWidget::SwitchToTrader);

	if (!ensure(B_SeaRaider != nullptr)) return false;
	B_SeaRaider->OnClicked.AddDynamic(this, &UUHeroBarWidget::SwitchToSeaRaider);

	if (!ensure(B_MineDweller != nullptr)) return false;
	B_MineDweller->OnClicked.AddDynamic(this, &UUHeroBarWidget::SwitchToMineDweller);

	if (!ensure(B_Druida != nullptr)) return false;
	B_Druida->OnClicked.AddDynamic(this, &UUHeroBarWidget::SwitchToDruida);

	if (!ensure(B_Alchemist != nullptr)) return false;
	B_Alchemist->OnClicked.AddDynamic(this, &UUHeroBarWidget::SwitchToAlchemist);

	if (!ensure(B_Occultist != nullptr)) return false;
	B_Occultist->OnClicked.AddDynamic(this, &UUHeroBarWidget::SwitchToOccultist);

	for (FConstPlayerControllerIterator iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	{
		APlayerController* PlayerControllerIterating = Cast<APlayerController>(*iter);

		PlayerController = Cast<ANorthernCampPlayerController>(PlayerControllerIterating);

	}


	
	return true;

}

void UUHeroBarWidget::SwitchToWill()
{
	PlayerController->SetSelectedHero(EHero::Will);
}

void UUHeroBarWidget::SwitchToTrader()
{
	PlayerController->SetSelectedHero(EHero::Trader);
}

void UUHeroBarWidget::SwitchToHunter()
{
	
	PlayerController->SetSelectedHero(EHero::Hunter);

}

void UUHeroBarWidget::SwitchToSeaRaider()
{
	PlayerController->SetSelectedHero(EHero::SeaRaider);

}

void UUHeroBarWidget::SwitchToMineDweller()
{
	PlayerController->SetSelectedHero(EHero::MineDweller);

}

void UUHeroBarWidget::SwitchToDruida()
{
	PlayerController->SetSelectedHero(EHero::Druida);

}

void UUHeroBarWidget::SwitchToAlchemist()
{
	PlayerController->SetSelectedHero(EHero::Alchemist);

}

void UUHeroBarWidget::SwitchToOccultist()
{
	PlayerController->SetSelectedHero(EHero::Occultist);

}

