// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SettlerInfoUserWidget.generated.h"

class ACharacterSettler;
class UScrollBox;
class UButton;

UCLASS()
class NORTHERNCAMP_API USettlerInfoUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TB_SettlersName;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollboxWholeWindow;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;
	

};
