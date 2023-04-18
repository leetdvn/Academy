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
	else if (menuName.EndsWith("shape3")) {
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

		//Settings->SetMusicVolume(0.2f);
	}

	//UGameplayStatics::OpenLevel(GetWorld(),FName(*mapOpen));
}

void UleeMenuGame::SetBlackSkyVisible(bool isOn, int32 zOder)
{
	ESlateVisibility vis = isOn ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	BlackSky->SetVisibility(vis);

	if (zOder <= 0) return;
	
	UCanvasPanelSlot* panel = Cast<UCanvasPanelSlot>(BlackSky->Slot);
	if (!panel) return;
	panel->SetZOrder(zOder);
}

void UleeMenuGame::OnBlackSkyTouch()
{
	if (!Settings) return;

	Settings->OnCloseDown();
	SetBlackSkyVisible(false);
}

void UleeMenuGame::OnPremiumLockClick()
{
	SetConfirmToogle(true,"Menupremiumclick");
	Confirm->lButtonYes->OnClicked.AddDynamic(this, &UleeMenuGame::OnParentClicked);
	Confirm->lButtonNo->OnClicked.AddDynamic(this,&UleeMenuGame::ConfirmClosed);

}

void UleeMenuGame::OnParentClicked()
{
	if (!Settings->isAvalible) {
		Settings->OnOpenUp();
		if (Settings) Settings->CheckLinkAccount();
		//InfoText->SetText(FText::FromString(Settings->DisplayInfo));
		SetBlackSkyVisible(true);
		SetConfirmToogle();
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

void UleeMenuGame::SetConfirmToogle(bool isOn,FString field)
{
	/*empty message return*/
	if (isOn && field.IsEmpty()) return;
	ESlateVisibility vis = isOn ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	Confirm->SetVisibility(vis);

	/*set Message from Table*/
	Confirm->lSetTitleFromTable(field);

}

void UleeMenuGame::SetConfirmPremiumToogle(bool isOn)
{
	ESlateVisibility vis = isOn ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	ConfirmPremium->SetVisibility(vis);

}

void UleeMenuGame::SetUnLockPremium(bool Unlock)
{
	if (GameMenu->lGetButtons().Num() > 0) {
		int32 count{};
		ESlateVisibility vis = Unlock ? ESlateVisibility::Visible : ESlateVisibility::HitTestInvisible;
		for (auto& btn : GameMenu->lGetButtons()) {
			if (IsPremium(btn->lGetTextureName())) {
				btn->lButton->SetIsEnabled(Unlock);
				btn->Premium->SetVisibility(vis);
				btn->Premium->OnMouseButtonDownEvent.BindUFunction(this, TEXT("OnPremiumLockClick"));
				//lDebug(btn->lGetTextureName());
			}
			count++;
		}
	}

}

void UleeMenuGame::OnConfirmOpen()
{
	SetUnLockPremium(true);
}

void UleeMenuGame::NativeConstruct()
{
	if (GameMenu) {

		if (GameMenu->lGetButtons().Num() > 0) {
			int32 count{};
			for (auto& btn : GameMenu->lGetButtons()) {
				btn->OnMenuClick.AddDynamic(this, &UleeMenuGame::OnMenuClick);
				btn->ltextblock->SetText(FText::FromStringTable(FName(*StrTable),leeMenu[count]));
				//btn->Premium = btn->WidgetTree->FindWidget(TEXT("Premium"));
				if (IsPremium(btn->lGetTextureName())) {
					btn->lButton->SetIsEnabled(false);
					btn->Premium->SetVisibility(ESlateVisibility::Visible);
					btn->Premium->OnMouseButtonDownEvent.BindUFunction(this, TEXT("OnPremiumLockClick"));
					lDebug(btn->lGetTextureName());
				}
				count++;
			}
		}
	}

	/*Settting implentation*/
	if (Settings)
		Settings->lClosed->OnClicked.AddDynamic(this, &UleeMenuGame::OnBlackSkyTouch);

	if (ConfirmPremium) {
		ConfirmPremium->lButtonNo->OnClicked.AddDynamic(this, &UleeMenuGame::ConfirmPremiumClosed);

	}

	if (Confirm) {
		Confirm->lButtonNo->OnClicked.AddDynamic(this, &UleeMenuGame::ConfirmClosed);

	}

	BlackSky->OnMouseButtonDownEvent.BindUFunction(this, TEXT("OnBlackSkyTouch"));

}

bool UleeMenuGame::IsPremium(FString textName)
{
	if (textName.IsEmpty()) return false;
	for (auto& vip : PremiumLists) {
		if (vip == textName) return true;
	}
	return false;
}
