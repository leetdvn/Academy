// Fill out your copyright notice in the Description page of Project Settings.


#include "leeGameHistories.h"
#include <Components/GridSlot.h>
#include <leeHistoryItem.h>
#include <Kismet/GameplayStatics.h>

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

void UleeGameHistories::OnMouseClicked(UleeHistoryItem* item)
{
	if (!item->JsGameObject.IsValid()) {
		lDebug("Not is Valid", FColor::Purple, "Debug");
		return;

	}

	TEnumAsByte<lGameType> gtype = lGetTypeFromHistories(item);
	UE_LOG(LogTemp, Warning, TEXT("object : %s"), *lJsontoStr(item->JsGameObject));
	return OnSwitchMapFromHistories(gtype);
}

void UleeGameHistories::OnSwitchMapFromHistories(lGameType gametype)
{
	switch (gametype)
	{
	case None:
		break;
	case Threelines: return lOpenMapLevel("ThreeLines");
	case FourBox: return lOpenMapLevel("FourBox");
	case DragDrop:
		break;
	case Line2Column:
		break;
	case AlphaBet:
		break;
	}
}

void UleeGameHistories::lOpenMapLevel(FString mapname)
{
	return UGameplayStatics::OpenLevel(GetWorld(), FName(mapname));
}

TEnumAsByte<lGameType> UleeGameHistories::lGetTypeFromHistories(UleeHistoryItem* item)
{
	if (!item->JsGameObject.IsValid() && item->ItemID <= 0) {
		lDebug("Not is Valid", FColor::Purple, "Debug");
		return None;

	}

	TSharedPtr<FJsonValue> gEType= item->JsGameObject->TryGetField("lessionType");
	if (!gEType.IsValid()) return None;
	TEnumAsByte<lGameType>  gtype = lGetEnumFromStr<lGameType>("lGameType", gEType->AsString());
	lDebug(gtype);

	return gtype;
}

void UleeGameHistories::OnOpenUp()
{
	if (!OpenUp) return;
	PlayAnimation(OpenUp);
}

void UleeGameHistories::OnCloseDown()
{
	if (!CloseDown) return;
	lDebug("Closed..");
	PlayAnimation(CloseDown);
}

void UleeGameHistories::NativeConstruct()
{
	lTurnOffButton->OnClicked.AddDynamic(this, &UleeGameHistories::OnCloseDown);

}

void UleeGameHistories::OnHistoriesInit(UPlayerData*& playerData)
{
	if (playerData->JsGames.Num() <= 0) return;
	int32 column = 0;
	for (int i = 0, x = 0; i < playerData->JsGames.Num() + 12; i++,column++) {

		//TSubclassOf<UUserWidget> createWd =
		//	i >= playerData->JsGames.Num() ?
		//	Itemlock :
		//	ItemUnlock;
		UleeHistoryItem* img = CreateWidget<UleeHistoryItem>(GetWorld(), ItemHistories);
		

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

			//setup On Click
			if (img) {
				bool unlock = i >= playerData->JsGames.Num() ? true : false;
				img->lTakeItem(unlock);
				img->ItemInfo->SetText(FText::FromString("Game " + FString::FromInt(i + 1)));
				int32 id = i < playerData->JsGames.Num() ? i : 0;
				img->ItemID = id;
				if (i < playerData->JsGames.Num()) {
					img->JsGameObject = playerData->JsGames[i]->AsObject();
				}
				img->OnItemClick.AddDynamic(this, &UleeGameHistories::OnMouseClicked);

			}

		}

	}

}

template<typename T>
inline T UleeGameHistories::lGetEnumFromStr(const FString name, FString enumStr)
{
	T result{};
	const UEnum* iEnum = FindObject<UEnum>(ANY_PACKAGE, *name, true);
	if (iEnum) {
		int32 Index = iEnum->GetIndexByName(*enumStr);
		result = TEnumAsByte<T>((uint8)Index);
		return result;
	}
	return result;
}
