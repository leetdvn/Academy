// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Components/GridPanel.h>
#include <PlayerData.h>
#include <Components/Image.h>
#include <Components/Button.h>
#include <Components/ScrollBox.h>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeGameHistories.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ACADEMY_API UleeGameHistories : public UUserWidget , public IleePublicInterface
{
	GENERATED_BODY()

public:
	UleeGameHistories(const FObjectInitializer& ObjectInitializer);
	

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Off Button", meta = (BindWidget))
		UButton* lTurnOffButton;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Grid", meta = (BindWidget))
		UGridPanel* lGridPanel;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Widget")
		TSubclassOf<UUserWidget> DisplayImg;

	void OnHistoriesInit(UPlayerData* &playerData);

	void OnHistoriesDown();
};
