// Fill out your copyright notice in the Description page of Project Settings.


#include "leeGameInstance.h"

void UleeGameInstance::Init()
{
	SaveSlot = "LeeTdvnGameData";
	GameData = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
	if (!GameData) {
		GameData = Cast<UPlayerData>(UGameplayStatics::CreateSaveGameObject(UPlayerData::StaticClass()));
		UGameplayStatics::SaveGameToSlot(GameData,SaveSlot, 0);
		GameData->HistoryGames = TArray<FGameLession>();
	}
}

void UleeGameInstance::SaveCurrentGameData(FGameLession& data)
{
	if (!GameData) { return; }
	GameData->CurrentGame = data;
	FString fileAbc = FString(FPaths::ProjectSavedDir() + "SaveGames/ACademyPreview.json");
	FString outStr;
	bool success = FJsonObjectConverter::UStructToJsonObjectString<FGameLession>(data, outStr);
	if (success) {
		UE_LOG(LogTemp, Warning,TEXT("data : %s"),* outStr);
		lCreateFileFromString(outStr, fileAbc);
	}
	//lDebug("Nullptr Game data");
	UGameplayStatics::DeleteGameInSlot(SaveSlot, 0);



	UGameplayStatics::SaveGameToSlot(GameData, SaveSlot, 0);

}

UPlayerData* UleeGameInstance::LoadGameData()
{
	if (GameData) {
		lDebug("Data IsLoaded...",FColor::Green," Data ");
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
