// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Kismet/KismetStringLibrary.h"
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

	TArray<TSharedPtr<FJsonObject>> ToJsHistory() {
		TArray<TSharedPtr<FJsonObject>> jsArray;
		TArray<TSharedPtr<FJsonValue>> jsArrayV;
		for (auto &session : HistoryGames) {
			jsArray.Add(session.ToObject());
		}
		return jsArray;
	}

	TSharedPtr<FJsonObject> HistoryStr() {
		TArray<FString> result{};
		//TArray<TSharedPtr<FJsonValue>> jsValue;
		TSharedPtr<FJsonObject> obj = MakeShareable(new FJsonObject);
		int count{};
		for (auto& game : HistoryGames) {
			FString Out;
			FJsonObjectConverter::UStructToJsonObjectString<FGameLession>(game, Out);
			result.Add(Out);
			obj.Get()->SetStringField(FString("Game_" + FString::FromInt(count)), Out);
			count++;
		}
		return obj;
	}

	FString ToString() { return UKismetStringLibrary::Conv_ObjectToString(this); }
};
