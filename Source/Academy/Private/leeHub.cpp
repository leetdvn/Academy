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
	
	FString map = UGameplayStatics::GetCurrentLevelName(GetWorld());// ->GetMapName();
	TSubclassOf<UUserWidget> panel;// = map.EndsWith("AMenu") ? lMenuWidget : lThreeLine;
	/*
	Create Widget Default and make new game
	*/
	if (map.EndsWith("AMenu")) {
		if (lCurrentWidget)
			lCurrentWidget->RemoveFromParent();
		lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), lMenuWidget);
		
	}


	if (lCurrentWidget) {
		lCurrentWidget->AddToViewport();

	}

	//lDebug(SessionGameId, FColor::Green);

	//active Event start game
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (lKidMusic) {
		float vol = GameIns->PlayerInfo->Music ? 0.5f : 0.0f;
		SetMusicVolume(vol);
		UGameplayStatics::PlayDialogue2D(GetWorld(), lKidMusic, lMusic);
	}
	if (!GameIns) { lDebug("Game Instance Nullptr"); return; }
	Player = GameIns->PlayerInfo;
	lDebug(Player->isFirstTime,FColor::Purple,"First Time");
}

void AleeHub::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//double x{}, y{};
	if (gametype == lGameType::None) return;
	if (!isKidAFK) return;
	KidTimeAFK += DeltaTime;

	if (!Player->isFirstTime)
	{
		ShowTutorials();
		GameIns->SaveUserInfo(Player);
		Player->isFirstTime = true;
	}
	else if (KidTimeAFK > KidTimeUp && !isTutorialShow)
		ShowTutorials();

	/*De bug Screen*/
	FString  mess = "AFK : " + FString::FromInt(KidTimeAFK);
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			-5,
			5,
			FColor::Purple,
			*mess
		);
	}
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
			if(gametype != gtype)
				line->isMakeSound = true;
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
			if (gametype != gtype)
				box->isMakeSound = true;
			box->m_type = FourBox;
			box->isNewGame = true;
			break;
		}
		case AlphaBet: {
			UleeAlphaBet* alpha = INewGameWidget<UleeAlphaBet>(gtype, lCurrentWidget);
			if (gametype != gtype)
				alpha->isMakeSound = true;
			alpha->isNewGame = true;
			alpha->m_type = AlphaBet;
			break;
		}
		default:
			break;
	}
	gametype = gtype;
	/*remote current widget and add new widget to viewport*/
	if (lCurrentWidget) lCurrentWidget->RemoveFromViewport();
	lCurrentWidget->AddToViewport();
	lOnGStart.Broadcast();
	LinesMode = linemode;
}

void AleeHub::ShowTutorials()
{
	if (isTutorialShow) return;
	if (TutorialWidget)
		TutorialWidget->RemoveFromParent();
	TutorialWidget= CreateWidget<UleeTutorials>(GetWorld(), Tutorials);

	FString Feild = gametype == Threelines ? "drag" : "correct";
	bool iDragTut = gametype == Threelines ? true : false;

	FText text = FText::FromStringTable(TEXT("/Game/Stringtable/Tutorial"), Feild);
	TutorialWidget->Desc->SetText(text);
	TutorialWidget->isDragTutorials = iDragTut;
	TutorialWidget->AddToViewport();
	isTutorialShow = true;
	isKidAFK = false;
	StartOverTutorialTime();
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

