// Fill out your copyright notice in the Description page of Project Settings.


#include "leeSmartCharacter2D.h"

void AleeSmartCharacter2D::ShowInterestialAds()
{
	bool avalible = UKismetSystemLibrary::IsInterstitialAdAvailable();
	bool requets = UKismetSystemLibrary::IsInterstitialAdRequested();

	FLatentActionInfo action{};
	action.ExecutionFunction = "ShowInterestialAds";
	action.CallbackTarget = this;
	count++;
	lDebug(count);
	if (!avalible)
		return UKismetSystemLibrary::Delay(this, AdsDelay, action);
	if(!requets)
		return UKismetSystemLibrary::Delay(this, AdsDelay, action);

	UKismetSystemLibrary::LoadInterstitialAd(1);
	UKismetSystemLibrary::ShowInterstitialAd();
}


void AleeSmartCharacter2D::BeginPlay()
{
	Super::BeginPlay();

	/*Show Banner*/
	//UKismetSystemLibrary::ShowAdBanner(0, false);
	//ShowInterestialAds();
}

//void AleeSmartCharacter2D::Tick(float Deltatime)
//{
//	if (CompletedGameCount > NextRewardAds) {
//
//		NextRewardAds += 2;
//		lDebug("RunAds");
//		
//	}
//}
