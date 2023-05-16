// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "lee3LinesData.h"
#include "lee4BoxData.h"
#include "leeAlphaData.h"
#include "leeUserInfo.h"
#include "leePublicEnum.h"
#include "leePublicInterface.h"
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

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Info")
		UleeUserInfo* PlayerInfo;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Line3s")
		Ulee3LinesData* Line3s;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Box4s")
		Ulee4BoxData* Box4s;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Alpha")
		UleeAlphaData* Alpha;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "User Info")
		TSubclassOf<UleeUserInfo> iinfo;

	void SaveUserInfo(UleeUserInfo*& info);

	void SaveGameData(TEnumAsByte<lGameType> gtype);

	void AddStarValue(int32 addvalue);

	/*Save & Load Game 3 Line*/
	void SaveLine3S(Ulee3LinesData*& lineData);

	void SaveBox4S(Ulee4BoxData*& boxData);

	void SaveAlpha(UleeAlphaData*& alphaData, bool createjS=false);

	bool CheckPremiumUser() { return PlayerInfo->isPurChased(); }

	int32 GetNumberLinesCompleted() { return Line3s->DataHistoriesStruct.Num(); }

	int32 GetNumber4BoxCompleted() { return Box4s->DataHistoriesStruct.Num(); }

	int32 GetNumberAlphaCompleted() { return Alpha->DataHistories.Num(); }

	template<class T>
	void SavePreview(TArray<T> arrayData);
	/*Save & Load Game 3 Line*/
	FGameLession Load3LinesGame(int32 idx);

	/*Save & Load Game Alpha Line*/
	FAlphaBetData LoadAlphaGameAt(int32 idx);

	/*Reoload 3Line*/
	void ReLoadingData() {
		Line3s = DataInitialize<Ulee3LinesData>(LINE3S);
		Box4s = DataInitialize<Ulee4BoxData>(BOX4S);
		PlayerInfo = DataInitialize< UleeUserInfo>(USERINFO);
		Alpha = DataInitialize<UleeAlphaData>(ALPHA);
	}

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
inline void UleeGameInstance::SavePreview(TArray<T> arrayData)
{
	if (arrayData.Num() <= 0) return;

	TArray<TSharedPtr<FJsonValue>> ArrayVal;
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	TSharedPtr<FJsonObject> DataJSonHistoriesObject = MakeShareable(new FJsonObject());

	FString preview = FString(FPaths::ProjectSavedDir() + "SaveGames/Preview.json");
	for (auto& g : arrayData)
	{
		TSharedPtr<FJsonObject> obj = FJsonObjectConverter::UStructToJsonObject(g);
		ArrayVal.Add(MakeShareable(new FJsonValueObject(obj)));


	}
	result->SetArrayField("Games", ArrayVal);
	DataJSonHistoriesObject->SetObjectField("PreViewHistories", result);

	FString Str = lJsontoStr(DataJSonHistoriesObject);
	lCreateFileFromString(Str, preview);
}

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
