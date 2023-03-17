// Fill out your copyright notice in the Description page of Project Settings.


#include "leeGameHistories.h"
#include <Components/GridSlot.h>

UleeGameHistories::UleeGameHistories(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UleeGameHistories::OnHistoriesDown()
{
	if (!lGridPanel) return;


	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, [this]() {lGridPanel->ClearChildren(); }, false, 1);
}

void UleeGameHistories::OnHistoriesInit(UPlayerData*& playerData)
{
	if (playerData->JsGames.Num() <= 0) return;
	int32 column = 0;
	for (int i = 0, x = 0; i < playerData->JsGames.Num(); i++,column++) {
		UUserWidget* img = CreateWidget<UUserWidget>(GetWorld(), DisplayImg);
		
		UGridSlot* gSlot = Cast<UGridSlot>(lGridPanel->AddChild(img));
		if (gSlot) {
			if (i % 4 == 0 && i > 0) {
				x++;
				lDebug(FString::FromInt(i));
				column = 0;
			}
			gSlot->SetColumn(column);
			gSlot->SetRow(x);
			gSlot->SetPadding(FMargin{25,25});
			//gSlot->SetRow(x);

		}

	}
}
