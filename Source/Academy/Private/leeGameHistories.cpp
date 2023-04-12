// Fill out your copyright notice in the Description page of Project Settings.


#include "leeGameHistories.h"
#include <Components/GridSlot.h>
#include <leeHistoryItem.h>
#include <Kismet/GameplayStatics.h>
#include <leeHub.h>

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
		IINFO("Not is Valid", FColor::Purple, "Debug");
		return;

	}
	FString gtype = lGetTypeFromHistories(item);
	return OnSwitchMapFromHistories(gtype,item);
}

void UleeGameHistories::OnSwitchMapFromHistories(FString gametype, UleeHistoryItem*& item)
{
	//Open Histories game
	AleeHub* leeHub = GetleeHub();
	if (gametype.IsEmpty() || item == nullptr || !leeHub) return;
	//lOpenMapLevel(gametype);
	lGameType hisType = lGetEnumFromStr<lGameType>("lGameType", lGetTypeFromHistories(item));
	if (!leeHub) return;
	
	switch (hisType)
	{
		case None: {return; }
		case Threelines: {	
			IINFO(" Threeline " , FColor::Purple);
			leeHub->LoadThreelineFromData(item->ItemID);
			break; }
		case FourBox: {
			IINFO(" Four Box ", FColor::Purple);
			leeHub->LoadFourBoxFromData(item->ItemID);
			break;
		}
		case AlphaBet: {
			IINFO(" alpha bet ", FColor::Purple);
			leeHub->LoadAlphabetFromData(item->ItemID);
			break;
		}
	}

}

AleeHub* UleeGameHistories::GetleeHub()
{
	UWorld* world = GetWorld();
	AHUD* hub = world->GetFirstPlayerController()->GetHUD();
	if (hub)
		return Cast<AleeHub>(hub);
	return nullptr;
}

void UleeGameHistories::lOpenMapLevel(FString mapname)
{
	return UGameplayStatics::OpenLevel(GetWorld(), FName(mapname));
}

FString UleeGameHistories::lGetTypeFromHistories(UleeHistoryItem* item)
{
	if (!item->JsGameObject.IsValid() && item->ItemID <= 0) {
		lDebug("Not is Valid", FColor::Purple, "Debug");
		return FString();

	}

	TSharedPtr<FJsonValue> gEType= item->JsGameObject->TryGetField("lessionType");
	if (!gEType.IsValid()) return FString();
	//TEnumAsByte<lGameType>  gtype = lGetEnumFromStr<lGameType>("lGameType", gEType->AsString());

	return gEType->AsString();
}

void UleeGameHistories::OnOpenUp()
{
	if (!OpenUp) return;
	PlayAnimation(OpenUp);
	isOpened = true;
}

void UleeGameHistories::OnCloseDown()
{
	if (!CloseDown && !isOpened) return;
	PlayAnimation(CloseDown);
	isOpened = false;
}

void UleeGameHistories::NativeConstruct()
{
	lTurnOffButton->OnClicked.AddDynamic(this, &UleeGameHistories::OnCloseDown);
	lBgr->OnMouseButtonDownEvent.BindUFunction(this, FName("OnCloseDown"));
}

void UleeGameHistories::CreateGameHistories(TEnumAsByte<lGameType> gtype)
{
	UleeGameInstance* leeIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (leeIns) {
		switch (gtype)
		{
			case None: {
				return;
			}
			case Threelines: {
				OnHistoriesImplantment<FGameLession>(leeIns->Line3s->DataHistoriesStruct);
				break;
			}
			case FourBox: {
				OnHistoriesImplantment<FFourBoxData>(leeIns->Box4s->DataHistoriesStruct);

				break;
			}
			case AlphaBet:{
				OnHistoriesImplantment<FAlphaBetData>(leeIns->Alpha->DataHistories);

				break;
			}
		}
	}
}

template<class T>
inline void UleeGameHistories::OnHistoriesImplantment(TArray<T> &Games)
{
	if (Games.Num() <= 0) return;
	int32 column = 0;
	for (int i = 0, x = 0; i < Games.Num() + 12; i++, column++) {

		UleeHistoryItem* img = CreateWidget<UleeHistoryItem>(GetWorld(), ItemHistories);


		UGridSlot* gSlot = Cast<UGridSlot>(lGridPanel->AddChild(img));
		if (gSlot) {
			if (i % 4 == 0 && i > 0) {
				x++;
				//lDebug(FString::FromInt(i));
				column = 0;
			}

			gSlot->SetColumn(column);
			gSlot->SetRow(x);
			gSlot->SetPadding(FMargin{ 15,15 });

			//setup On Click
			if (img) {
				bool unlock = i >= Games.Num() ? true : false;
				img->lTakeItem(unlock);
				FString label = FText::FromStringTable(FName(SETTINGTABLE), "Histories").ToString() + " " + FString::FromInt(i + 1);
				img->ItemInfo->SetText(FText::FromString(label));
				int32 id = i < Games.Num() ? i : 0;
				img->ItemID = id;
				if (i < Games.Num()) {
					//img->JsGameObject = playerData->JsGames[i]->AsObject();
					img->JsGameObject = FJsonObjectConverter::UStructToJsonObject(Games[i]);
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
