// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leePublicEnum.h"
#include "leePublicInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ACADEMY_API UPlayerData : public USaveGame , public IleePublicInterface
{
	GENERATED_BODY()

public:
	UPlayerData(const FObjectInitializer& ObjectInitializer);
	~UPlayerData() {};


	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		FString username;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int lStar;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		FGameLession CurrentGame;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		TArray<FGameLession> HistoryGames;

	FGameLession GetLastGame() { return HistoryGames[HistoryGames.Num()-1]; }

	FGameLession GetHistoryAt(int32 index) { return HistoryGames[index]; }
};
