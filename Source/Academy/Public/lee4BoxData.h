// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leePublicEnum.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "lee4BoxData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ACADEMY_API Ulee4BoxData : public USaveGame
{
	GENERATED_BODY()
public:
	Ulee4BoxData(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		TArray<FFourBoxData>  DataHistoriesStruct;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int32  DataNums;

	TArray<TSharedPtr<FJsonValue>> DataJSonGames;

	TSharedPtr<FJsonObject> DataJSonHistoriesObject;

	FFourBoxData GetLinesAt(int32 index);

	TSharedPtr<FJsonValue> GetGameAsJSonAt(int32 index);

};