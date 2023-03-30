// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UILeeDelegate.h"
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

	const FString gametype = "lessionType";
	const FString enumName = "lGameType";
	const FString mainField = "UserHistories";
	const FString GamesField = "Games";

public:
	UPlayerData(const FObjectInitializer& ObjectInitializer);
	~UPlayerData() {};

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		TEnumAsByte<lGameType> lastGame;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		FString DisplayName;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		FString Email;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		FString UserID;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		int Star;

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		TEnumAsByte<kLanguage> LanguagesSelected;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		FString lGetDisPlayName() { return DisplayName; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		FString lGetEmail() { return Email; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		FString lGetUserID() { return UserID; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		int lGetStar() { return Star; }

	UFUNCTION()
		FString GetRawHistoriesStr();

	UFUNCTION()
		void SaveConstruct();

	FString GetAllGames() { return RawHistories; }

	TArray<TSharedPtr<FJsonValue>> JsGames;

	TSharedPtr<FJsonObject> JsHistoriesObject;
	
	TSharedPtr<FJsonValue> GetGamesAt(int32 index);
	
	TSharedPtr<FJsonValue> GetLastGame();

	TEnumAsByte<lGameType> GetLastGameType();

	TEnumAsByte<lGameType> GetGameTypeAt(int32 gameId);

	FString ToString() { return UKismetStringLibrary::Conv_ObjectToString(this); }

	TSharedPtr<FJsonObject> BindGamesToHistories();

	TSharedPtr<FJsonObject> LoadHistoriesFromStr();

	FString GetGameStrAt(int32 index);

	FString GetLastGameStr();


	template <typename T>
	FORCEINLINE T lGetEnumFromStr(const FString name, FString enumStr);

	template<typename T>
	FString lGetStringFromEnum(T ipEnum);

protected:

	UPROPERTY(VisibleAnywhere, Category = "lee's Ultils")
		FString RawHistories;

};
