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

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		FString DisplayName;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		FString UserID;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int Star;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int GamesCompleted;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		bool IsUserPurChased;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		bool Sound;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		bool Music;


	const FString SlotName = "PlayerInfo";

	FString lGetDisplayName() { return DisplayName; }

	FString lGetUID() { return UserID; }

	int lGetStar() { return Star; }

	int lGetCompletedGames() { return GamesCompleted; }

	bool isPurChased() { return IsUserPurChased; }

	void lSetDisplayName(FString displayname);

	void lSetUID(FString userId);

	void lSetStar(int userStar);

	void lSetGamesCompleted(int gamescompleted);

	void lSetIsPurchased(bool ispurchase);
};
