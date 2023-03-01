// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leePublicEnum.h"
#include "leePublicInterface.h"
#include "leeLessionData.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerData.generated.h"


const FString CurrentLessionSlotName = "currentGame";
/**
 * 
 */
UCLASS(BlueprintType)
class ACADEMY_API UPlayerData : public USaveGame , public IleePublicInterface
{
	GENERATED_BODY()

public:
	UPlayerData();
	~UPlayerData() {};
	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		UleeLessionData* lCurrentGame;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		TArray<UleeLessionData*> lGameCompleted;
	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		FDataGamePathConfig PlayerData;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int lStar;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int32 lUserIndex;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		FString lSaveSlotName;


	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		FString lCurrentSlotName;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		TArray<FString> lPlayerHistorySlot;

	void SaveLessions(FDataGamePathConfig usersdata, FString &OutPreview);

	void SaveGameDatas();

	void SaveUserData();


	FDataGamePathConfig LoadGameData(bool &success);
};
