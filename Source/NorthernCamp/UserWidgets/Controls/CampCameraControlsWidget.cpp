// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/Controls/CampCameraControlsWidget.h"

#include "Components/Button.h"
#include "NorthernCamp/NorthernCampPlayerController.h"

void UCampCameraControlsWidget::NativeConstruct()
{

	Super::NativeConstruct();

	if (!ensure(B_SwitchToLoosCameraPawn != nullptr))
	{
		return;
	}
	B_SwitchToLoosCameraPawn->OnClicked.AddDynamic(this, &UCampCameraControlsWidget::SwitchToCharacter);

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

void UCampCameraControlsWidget::SwitchToCharacter()
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