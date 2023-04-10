// Fill out your copyright notice in the Description page of Project Settings.


#include "leeMenuGame.h"
#include <Source/Private/OnlineSharingFacebookCommon.h>
#include <leeHub.h>

void UleeMenuGame::OnMenuClick(FString menuName)
{
	if (menuName.IsEmpty()) return;
	lDebug(menuName);
	AleeHub* hub = lGetleeHub();
	TEnumAsByte<LineModes> mode = Normal;
	TEnumAsByte<lGameType> gMode = None;
	if (menuName.EndsWith("shape")) {
		mapOpen = "ThreeLines";
		gMode = Threelines;
	}
	else if (menuName.EndsWith("shape2")) {
		mode = LineModes::ExtendPremium;
		gMode = Threelines;
		mapOpen = "ThreeLines";
	}
	else if (menuName.EndsWith("environment")) {
		mode = LineModes::Environment;
		gMode = Threelines;
		mapOpen = "ThreeLines";
	}
	else if (menuName.StartsWith("numbers")) {
		mapOpen = "FourBox";
		gMode = FourBox;
	}
	else if (menuName.StartsWith("shapeitems")) {
		mapOpen = "AlphaBet";
		gMode = AlphaBet;
	}

	if (mapOpen.IsEmpty()) return;

	if (hub) {
		hub->CreateNewGame(gMode, mode);
	}

	//UGameplayStatics::OpenLevel(GetWorld(),FName(*mapOpen));
}

void UleeMenuGame::OnParentClicked()
{
	if (!Settings->isAvalible) {
		Settings->OnOpenUp();
		if (Settings) Settings->CheckLinkAccount();
		//InfoText->SetText(FText::FromString(Settings->DisplayInfo));
	}
}

AleeHub* UleeMenuGame::lGetleeHub()
{
	UWorld* world = GetWorld();
	AHUD* hub = world->GetFirstPlayerController()->GetHUD();
	if (hub)
		return Cast<AleeHub>(hub);
	return nullptr;
}

void UleeMenuGame::NativeConstruct()
{
	if (GameMenu) {
		if (GameMenu->lGetButtons().Num() > 0) {
			int32 count{};
			for (auto& btn : GameMenu->lGetButtons()) {
				btn->OnMenuClick.AddDynamic(this, &UleeMenuGame::OnMenuClick);
				btn->ltextblock->SetText(FText::FromStringTable(FName(*StrTable),leeMenu[count]));
				count++;
			}
		}
	}
}
