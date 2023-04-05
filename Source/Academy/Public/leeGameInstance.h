// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "lee3LinesData.h"
#include "lee4BoxData.h"
#include "leeAlphaData.h"
#include "leeUserInfo.h"
#include "leePublicEnum.h"
#include "leePublicInterface.h"
#include "PlayerData.h"
#include <Kismet/GameplayStatics.h>
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "leeGameInstance.generated.h"

/**
 * 
 */

#pragma region Save Game Slot Define directive


#define GAMEDATA  "leeGameData"
#define USERINFO  "PlayerInfo"
#define LINE3S	"ThreeLines"
#define BOX4S	"FourBox"
#define ALPHA	"AlphaBet"

#pragma endregion

UCLASS(BlueprintType)
class ACADEMY_API UleeGameInstance : public UGameInstance ,public IleePublicInterface
{
	GENERATED_BODY()

	void Init() override;

public:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Info")
		FString SlotGame;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Slot Info")
		FString SlotInfo;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "SaveGame")
		UPlayerData* GameData;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Info")
		UleeUserInfo* PlayerInfo;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Info")
		Ulee3LinesData* Line3s;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Info")
		Ulee4BoxData* Box4s;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Info")
		UleeAlphaData* Alpha;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Info")
		TSubclassOf<UleeUserInfo> iinfo;

	void SaveCurrentGameData(UPlayerData*& data);

	UPlayerData* LoadGameData();

	UPlayerData* GameDataInit();

	UleeUserInfo* LoadPlayerInfo();

	void SaveUserInfo(UleeUserInfo*& info);

	void SaveGameData(TEnumAsByte<lGameType> gtype);

	void SaveLine3S(FGameLession& lineData);

	void SaveBox4S(FFourBoxData& boxData);

	void SaveAlpha() {};


	/*Save & Load Game 3 Line*/
	void Save3LinesGame(FGameLession& data);


protected:
	FString previewStr;

	const TArray<FString> ListSlots = {"leeGameData",
		"PlayerInfo",
		"ThreeLines",
		"FourBox",
		"AlphaBet"
	};

	template<class T>
	T* DataInitialize(FString slotname);
};


template<class T>
inline T* UleeGameInstance::DataInitialize(FString slotname)
{
	T* dataS = Cast<T>(UGameplayStatics::LoadGameFromSlot(slotname, 0));
	if (!dataS) {
		dataS= Cast<T>(UGameplayStatics::CreateSaveGameObject(T::StaticClass()));
		UGameplayStatics::SaveGameToSlot(dataS, slotname,0);
	}
	/*report message when data nulll*/
	return dataS;
}
