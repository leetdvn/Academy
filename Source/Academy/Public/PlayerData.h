// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leeLessionData.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ACADEMY_API UPlayerData : public USaveGame
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
		int lStar;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int32 lUserIndex;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		FString lSaveSlotName;

};
