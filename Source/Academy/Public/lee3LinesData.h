// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <JsonUtilities/Public/JsonObjectConverter.h>
#include "leePublicInterface.h"
#include "leePublicEnum.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "lee3LinesData.generated.h"

/**
 * 
 */

UCLASS(BlueprintType)
class ACADEMY_API Ulee3LinesData : public USaveGame , public IleePublicInterface
{
	GENERATED_BODY()

public:

	Ulee3LinesData(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		TArray<FGameLession>  DataHistoriesStruct;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int32  DataNums;

	TSharedPtr<FJsonObject> DataJSonHistoriesObject;

	FGameLession GetLinesAt(int32 index);

	void CreateNewData(FGameLession& game,bool isPrewiew=false);
};