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
	else if (map.EndsWith("ThreeLines")) {
		lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), lThreeLine);
		UleeBaseLessions* lines = Cast<UleeBaseLessions>(lCurrentWidget);
		lines->isNewGame = SessionGameId <= 0 ? true : false;
		if (!lines->isNewGame)
			lines->SessionID = SessionGameId;
		//lines->NewGameThreelineInit();
	}
	else if (map.EndsWith("FourBox")) {
		lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), lFourBox);
		UleeFourBox* box = Cast<UleeFourBox>(lCurrentWidget);

		box->isNewGame = SessionGameId <= 0 ? true : false;
		if (!box->isNewGame)
			box->GameId = SessionGameId;

		box->isNewGame = true;
	}
	else if (map.EndsWith("AlphaBet")) {
		lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), lAlphaBeet);

	}

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
	UUserWidget* nWidget = CreateWidget<UUserWidget>(GetWorld(), lThreeLine);
	UleeFourBox* lines = Cast<UleeFourBox>(nWidget);
	lines->GameId = idx;

	lCurrentWidget->RemoveFromViewport();
	nWidget->AddToViewport();
	lCurrentWidget = nWidget;
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
	UUserWidget* nWidget = CreateWidget<UUserWidget>(GetWorld(), lThreeLine);
	UleeAlphaBet* lines = Cast<UleeAlphaBet>(nWidget);
	//lines->SessionID = idx;

	lCurrentWidget->RemoveFromViewport();
	nWidget->AddToViewport();
	lCurrentWidget = nWidget;

}

void AleeHub::CreateNewGame(TEnumAsByte<lGameType> gtype)
{


	switch (gtype)
	{
		case None: {return; }
		case Threelines: {
			UleeBaseLessions* line = NewGameWidget<UleeBaseLessions>(gtype, lCurrentWidget);
			line->isNewGame = true;
			break;
		}
		case FourBox: {
			UleeFourBox* box = NewGameWidget<UleeFourBox>(gtype, lCurrentWidget);
			box->isNewGame = true;
			break;
		}
		case AlphaBet: {
			UleeAlphaBet* alpha = NewGameWidget<UleeAlphaBet>(gtype, lCurrentWidget);
			break;
		}
	}
	if (lCurrentWidget) lCurrentWidget->RemoveFromViewport();
	gametype = gtype;
	lCurrentWidget->AddToViewport();
	lOnGStart.Broadcast();
}

AleeHub* AleeHub::GetInstance()
{
	UWorld* world = GEngine->GetWorld();
	if (world) {
		AHUD* hub = world->GetFirstPlayerController()->GetHUD();
		if (hub) return Cast<AleeHub>(hub);
	}
	return nullptr;
}

template<class T>
T* AleeHub::NewGameWidget(TEnumAsByte<lGameType> gametype, UUserWidget*& outWidget)
{
	switch (gametype)
	{
	case None:
		break;
	case Threelines: outWidget = CreateWidget<UUserWidget>(GetWorld(), lThreeLine);
		break;
	case FourBox: outWidget = CreateWidget<UUserWidget>(GetWorld(), lFourBox);
		break;
	case DragDrop:
		break;
	case Line2Column:
		break;
	case AlphaBet: outWidget = CreateWidget<UUserWidget>(GetWorld(), lAlphaBeet);
		break;
	default:
		break;
	}
	return Cast<T>(outWidget);
}

