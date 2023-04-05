#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "leeAlphaData.generated.h"

/**
 *
 */

UCLASS(BlueprintType)
class ACADEMY_API UleeAlphaData : public USaveGame
{
	GENERATED_BODY()

public:
	UleeAlphaData(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int32  DataNums;

	TArray<TSharedPtr<FJsonValue>> DataJSonGames;

	TSharedPtr<FJsonObject> DataJSonHistoriesObject;

	//FFourBoxData GetLinesAt(int32 index);

	//TSharedPtr<FJsonValue> GetGameAsJSonAt(int32 index);

};
