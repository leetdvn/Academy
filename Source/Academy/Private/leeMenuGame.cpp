// Fill out your copyright notice in the Description page of Project Settings.


#include "leeMenuGame.h"
#include <Source/Private/OnlineSharingFacebookCommon.h>

void UleeMenuGame::OnMenuClick(FString menuName)
{
	if (menuName.IsEmpty()) return;
	lDebug(menuName);
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
	else if (menuName.StartsWith("shape1")) {
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

void UleeMenuGame::OnOpenLogIn()
{
	ESlateVisibility vis = AccountLogin->GetVisibility() == ESlateVisibility::Hidden ?
		ESlateVisibility::SelfHitTestInvisible :
		ESlateVisibility::Hidden;
	return AccountLogin->SetVisibility(vis);
}

void UleeMenuGame::LinkUser(FString UserId, FString Email, FString dispname)
{
	///Save link User
	if(!GIns)
		GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UleeUserInfo* data = GIns->PlayerInfo;
	data->DisplayName = dispname;
	data->UserID = UserId;
	data->Email = Email;
	GIns->SaveUserInfo(data);


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
	AHUD* uhub = world->GetFirstPlayerController()->GetHUD();
	if (uhub)
		return Cast<AleeHub>(uhub);
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

	if (field == "") {
		Confirm->lButtonYes->OnClicked.Clear();
		Confirm->lButtonYes->OnClicked.AddDynamic(this, &UleeMenuGame::GotoPurchase);

	}
}

#pragma region get Data Player

bool UleeMenuGame::IsAdsShield()
{
	if (!GIns) {
		GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}

	// return Data
	return GIns->PlayerInfo->isAntiAds();
}

bool UleeMenuGame::IsPremium()
{
	if (!GIns) {
		GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}

	// return Data
	return GIns->PlayerInfo->isPurChased();
}

FString UleeMenuGame::GetUserId()
{
	if (!GIns) {
		GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}

	return GIns->PlayerInfo->lGetUID();
}

bool UleeMenuGame::isFirebaseLogins()
{
	if (!GIns) {
		GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}

	FString UID = GIns->PlayerInfo->lGetUID();

	return  UID != "" ? true : false;
}

int32 UleeMenuGame::GetUserStar()
{
	if (!GIns) {
		GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}

	return GIns->PlayerInfo->lGetStar();
}

void UleeMenuGame::StarCheckout(int32 number)
{
	if (!GIns) {
		GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	return AddStarToData(number);

}

void UleeMenuGame::AdsShieldCheckout()
{
	if (!GIns) {
		GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}

	UleeUserInfo* udata = GIns->PlayerInfo;
	udata->isNoAds = true;
	GIns->SaveUserInfo(udata);
}

void UleeMenuGame::PremiumCheckout()
{
	if (!GIns) {
		GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}

	UleeUserInfo* udata = GIns->PlayerInfo;
	udata->IsPremium = true;
	GIns->SaveUserInfo(udata);

	for (auto& btn : GameMenu->lGetButtons()) {
		btn->lButton->SetIsEnabled(true);
		btn->Premium->SetVisibility(ESlateVisibility::Hidden);
		btn->Premium->OnMouseButtonDownEvent.Clear();
	}

}

void UleeMenuGame::AddStarToData(int32 starnumber)
{
	if (!GIns) {
		GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}

	UleeUserInfo* udata = GIns->PlayerInfo;
	udata->AddStar(starnumber);
	GIns->SaveUserInfo(udata);
}

bool UleeMenuGame::isAdsSheildProtected()
{
	if (!GIns) {
		GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	return GIns->PlayerInfo->isAntiAds();
}

void UleeMenuGame::SetDataFromFirebase(bool AdSheild, bool isPremium, int32 fireStar, FString uid, FString email, FString displayname)
{
	if (!GIns) {
		GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}

	UleeUserInfo* udata = GIns->PlayerInfo;
	udata->isNoAds = AdSheild; 
	udata->IsPremium = isPremium;
	udata->BaseStar = udata->Star = fireStar;
	udata->UserID = uid;
	udata->Email = email;
	udata->DisplayName = displayname;
	/*Generate Game*/
	GIns->SaveUserInfo(udata);
}

#pragma endregion

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
	Super::NativeConstruct();
	GIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	hub = lGetleeHub();
	if (hub->isOpenShop) OnBlackSkyTouch();

	if (GameMenu) {

		if (GameMenu->lGetButtons().Num() > 0) {
			int32 count{};
			for (auto& btn : GameMenu->lGetButtons()) {
				if (btn->OnMenuClick.IsBound())
					btn->OnMenuClick.Clear();
				btn->OnMenuClick.AddDynamic(this, &UleeMenuGame::OnMenuClick);
				btn->ltextblock->SetText(FText::FromStringTable(FName(*StrTable),leeMenu[count]));
				//btn->Premium = btn->WidgetTree->FindWidget(TEXT("Premium"));
				if (!GIns->PlayerInfo->IsPremium) {
					if (IsPremium(btn->lGetTextureName())) {
						btn->lButton->SetIsEnabled(false);
						btn->Premium->SetVisibility(ESlateVisibility::Visible);
						btn->Premium->OnMouseButtonDownEvent.BindUFunction(this, TEXT("OnPremiumLockClick"));
						lDebug(btn->lGetTextureName());
					}

				}
				count++;
			}
		}
	}
	UKismetSystemLibrary::ShowAdBanner(0, false);
	/*Settting implentation*/
	if (Settings) {
		Settings->lClosed->OnClicked.AddDynamic(this, &UleeMenuGame::OnBlackSkyTouch);
	}

	if (ConfirmPremium) {
		ConfirmPremium->lButtonNo->OnClicked.AddDynamic(this, &UleeMenuGame::ConfirmPremiumClosed);

	}

	if (Confirm) {
		Confirm->lButtonNo->OnClicked.AddDynamic(this, &UleeMenuGame::ConfirmClosed);
	}

	BlackSky->OnMouseButtonDownEvent.BindUFunction(this, TEXT("OnBlackSkyTouch"));

	
	PlayAnimation(Khicau1, 0, 0);;
	PlayAnimation(Khicau2, 0, 0);;

}

void UleeMenuGame::NativeDestruct()
{
	Super::NativeDestruct();
	/*clear event*/
	Settings->lClosed->OnClicked.Clear();
	ConfirmPremium->lButtonNo->OnClicked.Clear();
	BlackSky->OnMouseButtonDownEvent.Clear();
	OnLoginSuccess.Clear();
	Confirm->lButtonNo->OnClicked.Clear();
	Confirm->lButtonYes->OnClicked.Clear();

}

bool UleeMenuGame::IsPremium(FString textName)
{
	if (textName.IsEmpty()) return false;
	for (auto& vip : PremiumLists) {
		if (vip == textName) return true;
	}
	return false;
}
