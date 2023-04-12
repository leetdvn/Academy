#pragma once

#include "leePublicEnum.h"
#include "CoreMinimal.h"
#include "leePublicInterface.h"
#include "GameFramework/SaveGame.h"
#include "leeAlphaData.generated.h"

/**
 *
 */

UCLASS(BlueprintType)
class ACADEMY_API UleeAlphaData : public USaveGame,public IleePublicInterface
{
	GENERATED_BODY()

public:
	UleeAlphaData(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int32  DataNums;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
	TArray<FAlphaBetData> DataHistories;

	TArray<TSharedPtr<FJsonValue>> DataJSonGames;

	TSharedPtr<FJsonObject> DataJSonHistoriesObject;

	FAlphaBetData GetLinesAt(int32 index) { return DataHistories[index]; }

	//TSharedPtr<FJsonValue> GetGameAsJSonAt(int32 index);

	void CreateNewData(FAlphaBetData& gameId, bool isPreview);
};
