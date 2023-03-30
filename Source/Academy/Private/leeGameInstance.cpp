// Fill out your copyright notice in the Description page of Project Settings.


#include "leeGameInstance.h"

void UleeGameInstance::Init()
{
	SlotGame = "leeGameData";
	SlotInfo = "PlayerInfo";

	LoadPlayerInfo();
	GameDataInit();
	//UE_LOG(LogTemp, Warning, TEXT("Data is Loaded : %s"), *GameData->GetAllGames());
}

void UleeGameInstance::SaveCurrentGameData(UPlayerData*& data)
{
	if (!GameData) { return; }

	FString fileAbc = FString(FPaths::ProjectSavedDir() + "SaveGames/ACademyPreview.json");
	FString outStr;
	//Construct Data
	data->SaveConstruct();
	UGameplayStatics::DeleteGameInSlot(SlotGame, 0);
	UGameplayStatics::SaveGameToSlot(data, SlotGame, 0);
}

UPlayerData* UleeGameInstance::LoadGameData()
{

	if (GameData) {
		lDebug("Data IsLoaded...",FColor::Green," Data ");
		FString result;
		FString fileAbc = FString(FPaths::ProjectSavedDir() + "SaveGames/ACademyPreview.json");
		GameData->LoadHistoriesFromStr();
		//lDebug(GameData->JsGames.Num());

		//GameData->HistoriesObject=lGetJsObjectFromFile(fileAbc);
		//GameData->PlayerHistories = lGetArrayObjFromObject(GameData->HistoriesObject, "UserHistories");
		//lDebug(GameData->PlayerHistories.Num());
		//FFileHelper::LoadFileToArray(GameData->HistoryGames, *fileAbc);
		return GameData;
	}
	lDebug("Nullptr Game data");
	return nullptr;
}


UPlayerData* UleeGameInstance::GameDataInit() {

	 GameData = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot(SlotGame, 0));
	 if (!GameData) {
		 GameData = Cast<UPlayerData>(UGameplayStatics::CreateSaveGameObject(UPlayerData::StaticClass()));
		 UGameplayStatics::SaveGameToSlot(GameData, SlotGame, 0);
		 return GameData;
	 }
	 GameData->LoadHistoriesFromStr();
	 return GameData;
}

UleeUserInfo* UleeGameInstance::LoadPlayerInfo()
{
	PlayerInfo = Cast<UleeUserInfo>(UGameplayStatics::LoadGameFromSlot(SlotInfo, 0));
	if (!PlayerInfo) {
		PlayerInfo = Cast<UleeUserInfo>(UGameplayStatics::CreateSaveGameObject(UleeUserInfo::StaticClass()));
		UGameplayStatics::SaveGameToSlot(PlayerInfo, SlotInfo, 0);
	}
	return PlayerInfo;
}

void UleeGameInstance::SaveUserInfo(UleeUserInfo*& info)
{

	UGameplayStatics::SaveGameToSlot(info, SlotInfo, 0);

}


