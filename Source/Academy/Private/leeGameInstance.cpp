// Fill out your copyright notice in the Description page of Project Settings.


#include "leeGameInstance.h"

void UleeGameInstance::Init()
{
	SaveSlot = "LeeTdvnGameData";
	GameData = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
	if (!GameData) {
		GameData = Cast<UPlayerData>(UGameplayStatics::CreateSaveGameObject(UPlayerData::StaticClass()));
		UGameplayStatics::SaveGameToSlot(GameData,SaveSlot, 0);

	}

	LoadGameData();
	UE_LOG(LogTemp, Warning, TEXT("Data is Loaded : %s"), *GameData->GetAllGames());
}

void UleeGameInstance::SaveCurrentGameData(UPlayerData*& data)
{
	if (!GameData) { return; }

	FString fileAbc = FString(FPaths::ProjectSavedDir() + "SaveGames/ACademyPreview.json");
	FString outStr;

	//Construct Data
	data->SaveConstruct();
	UGameplayStatics::DeleteGameInSlot(SaveSlot, 0);
	UGameplayStatics::SaveGameToSlot(data, SaveSlot, 0);

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


UPlayerData* UleeGameInstance::LoadCurrentGameData() {

	UPlayerData* currentGame= Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
	if (currentGame) return currentGame;
	return nullptr;
}

void UleeGameInstance::SaveGame(UPlayerData*& data)
{

}

