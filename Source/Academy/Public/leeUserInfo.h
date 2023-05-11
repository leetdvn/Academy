// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "leePublicEnum.h"
#include "leePublicInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "leeUserInfo.generated.h"

/**
 * 
 */
UCLASS()
class ACADEMY_API UleeUserInfo : public USaveGame 
{
	GENERATED_BODY()
	
public:
	UleeUserInfo(const FObjectInitializer& ObjectInitializer);
	~UleeUserInfo() {};

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Displayname")
		FString DisplayName;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player UserId")
		FString UserID;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Star")
		int32 Star;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Email")
		FString Email;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int32 GamesCompleted;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Premium")
		bool IsPremium;

	UPROPERTY(VisibleAnyWhere, Category = "lee's Ultils", DisplayName = "Base Star")
		int BaseStar;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		bool Sound;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		bool Music;
	
	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		bool isFirstTime;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		bool isFirstBox;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		bool isFirstAlpha;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		bool isNoAds;

	const FString SlotName = "PlayerInfo";

	FString lGetDisplayName() { return DisplayName; }

	FString lGetUID() { return UserID; }

	int lGetStar() { return Star; }

	int lGetCompletedGames() { return GamesCompleted; }

	bool isPurChased() { return IsPremium; }

	bool isAntiAds() { return isNoAds; }

	void lSetDisplayName(FString displayname);

	void lSetUID(FString userId);

	void AddStar(int userStar);

	void SetStarValue(int nvalue);

	void lSetGamesCompleted(int gamescompleted);

	void lSetIsPurchased(bool ispurchase);
};
