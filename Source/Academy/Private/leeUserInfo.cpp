// Fill out your copyright notice in the Description page of Project Settings.


#include "leeUserInfo.h"

UleeUserInfo::UleeUserInfo(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UleeUserInfo::lSetDisplayName(FString displayname)
{
	DisplayName = displayname;
}

void UleeUserInfo::lSetUID(FString userId)
{
	UserID = userId;
}

void UleeUserInfo::lSetStar(int userStar)
{
	if (userStar < 0 || userStar == Star) return;
	Star = userStar;
}

void UleeUserInfo::lSetGamesCompleted(int gamescompleted)
{
	if (gamescompleted < 0 || gamescompleted == GamesCompleted) return;

	GamesCompleted = gamescompleted;
}

void UleeUserInfo::lSetIsPurchased(bool ispurchase)
{
	IsUserPurChased = ispurchase;
}
