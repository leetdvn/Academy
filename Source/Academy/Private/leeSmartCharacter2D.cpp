// Fill out your copyright notice in the Description page of Project Settings.


#include "leeSmartCharacter2D.h"
#include <leeGameInstance.h>

//void AleeSmartCharacter2D::ShowInterestialAds()
//{
//	bool avalible = UKismetSystemLibrary::IsInterstitialAdAvailable();
//	bool requets = UKismetSystemLibrary::IsInterstitialAdRequested();
//
//	FLatentActionInfo action{};
//	action.ExecutionFunction = "ShowInterestialAds";
//	action.CallbackTarget = this;
//	count++;
//	lDebug(count);
//	if (!avalible)
//		return UKismetSystemLibrary::Delay(this, AdsDelay, action);
//	if(!requets)
//		return UKismetSystemLibrary::Delay(this, AdsDelay, action);
//
//	UKismetSystemLibrary::LoadInterstitialAd(1);
//	UKismetSystemLibrary::ShowInterstitialAd();
//}


AleeSmartCharacter2D::AleeSmartCharacter2D()
{
	//bAllowTickBeforeBeginPlay = true;
	//bTiechenalbe
}

void AleeSmartCharacter2D::BeginPlay()
{
	Super::BeginPlay();
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	LoadRewardsTime = ShowRewardsTime / 2;
	LoadsInterstitials = ShowInterstititalTime / 2;
	showinterAds = ShowInterstititalTime;
	showRewadsAds = ShowRewardsTime;

	AdsBlocked = IsAntiAds();
	lDebug(AdsBlocked);
	if (!AdsBlocked) {
		OnBannerS.Broadcast();
		OnLoadRewads.Broadcast();

	}
	/*Show Banner*/
	//UKismetSystemLibrary::ShowAdBanner(0, false);
	//ShowInterestialAds();
}

void AleeSmartCharacter2D::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	DeltaCount += Deltatime;

	if (DeltaCount > LoadsInterstitials / 2)
	{
		LoadsInterstitials += ShowInterstititalTime / 2;
		OnLoadIntertititals.Broadcast();
		lDebug("Create Ads");
	}
	else if (DeltaCount > showinterAds) {
		showinterAds += ShowInterstititalTime;
		OnShowInterstitials.Broadcast();
		lDebug("Show Intertitials");
	}

	if (CompletedGameCount == GameNumberShow)
	{
		CompletedGameCount = 0;
		OnShowRewads.Broadcast();
		lDebug("Reload Rewads");
		/*Reload Rewads*/
		OnLoadRewads.Broadcast();
	}
}

bool AleeSmartCharacter2D::IsAntiAds() {
	if(!GameIns)
		GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	return GameIns->PlayerInfo->isAntiAds();
}

void AleeSmartCharacter2D::Destroyed()
{
	OnLoadIntertititals.Clear();
	OnShowInterstitials.Clear();
	OnLoadRewads.Clear();
	OnShowRewads.Clear();
	OnBannerS.Clear();
}
