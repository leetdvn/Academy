// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leePublicInterface.h"
#include "leePublicEnum.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "lee4BoxData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ACADEMY_API Ulee4BoxData : public USaveGame , public IleePublicInterface
{
	GENERATED_BODY()
public:
	Ulee4BoxData(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		TArray<FFourBoxData>  DataHistoriesStruct;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int32  DataNums;

	TSharedPtr<FJsonObject> DataJSonHistoriesObject;

	FFourBoxData GetLinesAt(int32 index);

	TSharedPtr<FJsonValue> GetGameAsJSonAt(int32 index);

	void CreateNewData(FFourBoxData boxData, bool isPrewiew = false);
};