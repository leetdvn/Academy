// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "leeGameInstance.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "leePublicInterface.h"
#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "leeSmartCharacter2D.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadIntertials);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShowIntertials);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadRewards);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShowRewads);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShowBanner);


UCLASS(BlueprintType, Blueprintable)
class ACADEMY_API AleeSmartCharacter2D : public APaperCharacter , public IleePublicInterface
{
	GENERATED_BODY()
	
public:

	AleeSmartCharacter2D();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Number Game Show Ads Reward")
		int32 CompletedGameCount;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Number Game Show ")
		int32 GameNumberShow;

	UPROPERTY(BlueprintAssignable, Category = "lee's Ultils")
		FOnLoadIntertials OnLoadIntertititals;

	UPROPERTY(BlueprintAssignable, Category = "lee's Ultils")
		FOnShowIntertials OnShowInterstitials;

	UPROPERTY(BlueprintAssignable, Category = "lee's Ultils")
		FOnLoadRewards OnLoadRewads;

	UPROPERTY(BlueprintAssignable, Category = "lee's Ultils")
		FOnShowRewads OnShowRewads;

	UPROPERTY(BlueprintAssignable, Category = "lee's Ultils")
		FOnShowBanner OnBannerS;

	int32 count;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Intertitials Load Time ")
		float ShowInterstititalTime;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Rewads Load Time ")
		float ShowRewardsTime;


	float LoadsInterstitials, LoadRewardsTime , showinterAds,showRewadsAds;

	float DeltaCount;

	bool AdsBlocked{};
	//UFUNCTION()
	//	void ShowInterestialAds();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		UleeGameInstance* GameIns;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool IsAntiAds();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float Deltatime) override;

	virtual void Destroyed() override;

};
