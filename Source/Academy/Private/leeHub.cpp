// Fill out your copyright notice in the Description page of Project Settings.

#include "leeHub.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include <leePanelBase.h>
#include <Kismet/KismetInternationalizationLibrary.h>

class UKidWidget;

AleeHub::AleeHub()
{
}

void AleeHub::BeginPlay()
{
	Super::BeginPlay();
	
	if (!lMenuWidget) return;

	FString map = UGameplayStatics::GetCurrentLevelName(GetWorld());// ->GetMapName();
	TSubclassOf<UUserWidget> panel;// = map.EndsWith("AMenu") ? lMenuWidget : lThreeLine;


	/*
	Create Widget Default and make new game
	Create Widget Default and make new game
	*/
	if (map.EndsWith("AMenu")) {
		lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), lMenuWidget);
	}
	//else if (map.EndsWith("ThreeLines")) {
	//	lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), lThreeLine);
	//	UleeBaseLessions* lines = Cast<UleeBaseLessions>(lCurrentWidget);
	//	lines->isNewGame = SessionGameId <= 0 ? true : false;
	//	if (!lines->isNewGame)
	//		lines->SessionID = SessionGameId;
	//	//lines->NewGameThreelineInit();
	//}
	//else if (map.EndsWith("FourBox")) {
	//	lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), lFourBox);
	//	UleeFourBox* box = Cast<UleeFourBox>(lCurrentWidget);

	//	box->isNewGame = SessionGameId <= 0 ? true : false;
	//	if (!box->isNewGame)
	//		box->GameId = SessionGameId;

	//	box->isNewGame = true;
	//}
	//else if (map.EndsWith("AlphaBet")) {
	//	lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), lAlphaBeet);

	//}

	if (lCurrentWidget) {
		lCurrentWidget->AddToViewport();
	}

	lDebug(SessionGameId, FColor::Green);

	//active Event start game
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameIns) { lDebug("Game Instance Nullptr"); return; }
}

void AleeHub::Tick(float DeltaTime)
{
	//double x{}, y{};
}

void AleeHub::LoadFourBoxFromData(int32 idx)
{
	UUserWidget* nWidget = CreateWidget<UUserWidget>(GetWorld(), lFourBox);
	UleeFourBox* lines = Cast<UleeFourBox>(nWidget);
	if (lines) {
		lines->GameId = idx;
		lCurrentWidget->RemoveFromViewport();
		nWidget->AddToViewport();
		lCurrentWidget = nWidget;
	}
}

void AleeHub::LoadThreelineFromData(int32 idx)
{
	UUserWidget* nWidget = CreateWidget<UUserWidget>(GetWorld(), lThreeLine);
	UleeBaseLessions* lines = Cast<UleeBaseLessions>(nWidget);
	lines->SessionID = idx;

	lCurrentWidget->RemoveFromViewport();
	nWidget->AddToViewport();
	lCurrentWidget = nWidget;
}

void AleeHub::LoadAlphabetFromData(int32 idx)
{
	UUserWidget* nWidget = CreateWidget<UUserWidget>(GetWorld(), lAlphaBeet);
	UleeAlphaBet* Alpha = Cast<UleeAlphaBet>(nWidget);
	if (Alpha) {
		Alpha->GameId = idx;
		lDebug(idx,FColor::Purple);
		lCurrentWidget->RemoveFromViewport();
		nWidget->AddToViewport();
		lCurrentWidget = nWidget;
	}

}

void AleeHub::CreateNewGame(TEnumAsByte<lGameType> gtype,TEnumAsByte<LineModes> linemode)
{
	switch (gtype)
	{
		case None: {return; }
		case Threelines: {
			UleeBaseLessions* line = INewGameWidget<UleeBaseLessions>(gtype, lCurrentWidget);
			gametype = line->GameType = Threelines;
			line->Mode = linemode;
			if (linemode == LineModes::Environment) {
				FText text = FText::FromStringTable(GAMETABLE, "EnvDesc");
				FText tit = FText::FromStringTable(GAMETABLE, "EnvTitle");
				line->lDescription->SetText(text);
				line->ltitle->SetText(tit);
			}
			line->isNewGame = true;
			break;
		}
		case FourBox: {
			UleeFourBox* box = INewGameWidget<UleeFourBox>(gtype, lCurrentWidget);
			box->m_type = FourBox;
			box->isNewGame = true;
			break;
		}
		case AlphaBet: {
			UleeAlphaBet* alpha = INewGameWidget<UleeAlphaBet>(gtype, lCurrentWidget);
			alpha->isNewGame = true;
			alpha->m_type = AlphaBet;
			break;
		}
		default:
			break;
	}
	if (lCurrentWidget) lCurrentWidget->RemoveFromViewport();
	gametype = gtype;
	lCurrentWidget->AddToViewport();
	lOnGStart.Broadcast();
	LinesMode = linemode;
}

template<class T>
T* AleeHub::INewGameWidget(TEnumAsByte<lGameType> gtype, UUserWidget*& outWidget)
{
	switch (gtype)
	{
		case None: {
			break;
		}
		case Threelines: { outWidget = CreateWidget<UUserWidget>(GetWorld(), lThreeLine);
			break;
		}
		case FourBox: { outWidget = CreateWidget<UUserWidget>(GetWorld(), lFourBox);
			break;
		}
		case AlphaBet: {
			outWidget = CreateWidget<UUserWidget>(GetWorld(), lAlphaBeet);
			break;
		}
	}
	return Cast<T>(outWidget);
}

