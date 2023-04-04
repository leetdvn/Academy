// Fill out your copyright notice in the Description page of Project Settings.

#include "leeHub.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include <leePanelBase.h>
#include <Kismet/KismetInternationalizationLibrary.h>

class UKidWidget;

AleeHub::AleeHub()
{
	lOnGStart.AddDynamic(this, &AleeHub::OnGameStart);
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
		lines->isNewGame = true;
		//lines->NewGameThreelineInit();
	}
	else if (map.EndsWith("FourBox")) {
		lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), lFourBox);
		UleeFourBox* box = Cast<UleeFourBox>(lCurrentWidget);
		box->isNewGame = true;
	}
	else if (map.EndsWith("AlphaBet")) {
		lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), lAlphaBeet);

	}

	if (lCurrentWidget) {
		lCurrentWidget->AddToViewport();
	}
	//active Event start game
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameIns) { lDebug("Game Instance Nullptr"); return; }
}

void AleeHub::Tick(float DeltaTime)
{
	//double x{}, y{};
}

void AleeHub::lSetGameWidgets(int index)
{
	//if (index >= lGameWidgets.Num()) return;
	//lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), lGameWidgets[index]);
	//if (lCurrentWidget != nullptr) {
	//	lCurrentWidget->AddToViewport();
	//}


}

int AleeHub::lGetlGameWidgets()
{
	return 0;
}

void AleeHub::OnGameStart()
{
	lOnGStart.Broadcast();
}

void AleeHub::OnChangeClick()
{
	//leeTdDebug("Event Dispatcher");
}

void AleeHub::Onlevelchanged()
{
	onlevelChanged.Broadcast();
}
