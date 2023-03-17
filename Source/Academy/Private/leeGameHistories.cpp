// Fill out your copyright notice in the Description page of Project Settings.


#include "leeGameHistories.h"
#include <Components/GridSlot.h>
#include <leeHistoryItem.h>

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
	for (int i = 0, x = 0; i < playerData->JsGames.Num() + 12; i++,column++) {

		TSubclassOf<UUserWidget> createWd =
			i >= playerData->JsGames.Num() ?
			Itemlock :
			ItemUnlock;
		UUserWidget* img = CreateWidget<UUserWidget>(GetWorld(), createWd);
		UleeHistoryItem* Item = Cast<UleeHistoryItem>(img);
		UGridSlot* gSlot = Cast<UGridSlot>(lGridPanel->AddChild(img));
		if (gSlot) {
			if (i % 4 == 0 && i > 0) {
				x++;
				lDebug(FString::FromInt(i));
				column = 0;
			}
			gSlot->SetColumn(column);
			gSlot->SetRow(x);
			gSlot->SetPadding(FMargin{15,15});
			if (Item)
				Item->ItemInfo->SetText(FText::FromString("Game " + FString::FromInt(i +1)));
			//if (ItemInfo)
			//	ItemInfo->SetText(FText::FromString("Lession " + FString::FromInt(i)));
			//gSlot->SetRow(x);

		}

	}
}
