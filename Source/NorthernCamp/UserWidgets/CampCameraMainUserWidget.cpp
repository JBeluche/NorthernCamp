// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/UserWidgets/CampCameraMainUserWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "NorthernCamp/NorthernCampPlayerController.h"


void UCampCameraMainUserWidget::NativeConstruct()
{

	Super::NativeConstruct();

	if (!ensure(B_SwitchToLoosCameraPawn != nullptr))
	{
		return;
	}
	B_SwitchToLoosCameraPawn->OnClicked.AddDynamic(this, &UCampCameraMainUserWidget::SwitchToCharacter);

	/*if (!ensure(B_Build != nullptr))
	{
		return;
	}
	B_Build->OnClicked.AddDynamic(this, &UCampControls::OpenBuildMenu);*/

	for (FConstPlayerControllerIterator iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	{
		APlayerController* PlayerControllerIterating = Cast<APlayerController>(*iter);

		PlayerController = Cast<ANorthernCampPlayerController>(PlayerControllerIterating);

	}

}

void UCampCameraMainUserWidget::SwitchToCharacter()
{
	PlayerController->SwitchPawn(ECurrentPawn::LooseCamera);
}
/*
void UCampCameraMainUserWidget::OpenBuildMenu()
{
	TArray<AActor *> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuildingBase::StaticClass(), FoundActors);

	for (int i = 0; i < FoundActors.Num(); i++)
	{
		if (FoundActors[i] != nullptr && Cast<ABuildingBase>(FoundActors[i]))
		{
			ABuildingBase *Item = Cast<ABuildingBase>(FoundActors[i]);
			if (BuildingItemContainer)
			{
				if (BuildingBlueprint)
				{
					UBuildingListItem *Widget = CreateWidget<UBuildingListItem>(this, BuildingBlueprint);
					if (Widget)
					{
						BuildingItemContainer->AddChildToWrapBox(Widget);
						if (Widget->TB_NameBuilding)
						{
							Widget->SetData(FText::FromString(Item->GetName()));
						}
					}
				}
			}
		}
	}
}*/