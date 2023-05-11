// Fill out your copyright notice in the Description page of Project Settings.


#include "leeUserInfo.h"

UleeUserInfo::UleeUserInfo(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Music = true;
	Sound = true;
}

void UleeUserInfo::lSetDisplayName(FString displayname)
{
	DisplayName = displayname;
}

void UleeUserInfo::lSetUID(FString userId)
{
	UserID = userId;
}

void UleeUserInfo::AddStar(int userStar)
{
	if (userStar < 0 ) return;
	Star += userStar;
	BaseStar += userStar;
}

void UleeUserInfo::SetStarValue(int nvalue)
{
	BaseStar = Star = nvalue;
}

void UleeUserInfo::lSetGamesCompleted(int gamescompleted)
{
	if (gamescompleted < 0 || gamescompleted == GamesCompleted) return;

	GamesCompleted = gamescompleted;
}

void UleeUserInfo::lSetIsPurchased(bool ispurchase)
{
	IsPremium = ispurchase;
}
