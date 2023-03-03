//// Fill out your copyright notice in the Description page of Project Settings.
//
//
#include "PlayerData.h"
//#include <Kismet/GameplayStatics.h>
//
//UPlayerData* UPlayerData::Ins;
//
UPlayerData::UPlayerData(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	lStar = 0;
	//USaveGame* save = UGameplayStatics::LoadGameFromSlot("LeeTdvnGameData", 1);
	//leeSaveSystem = UGameplayStatics::CreateSaveGameObject(UPlayerData::StaticClass());
	//leeSaveSystem=	UGameplayStatics::LoadGameFromSlot("LeeTdvnGameData", 1);//UGameplayStatics::CreateSaveGameObject(UPlayerData::StaticClass());
	//convert Struct to String
	//bool success = FJsonObjectConverter::UStructToJsonObjectString<FGameLession>(Ins->CurrentGame, outJsStr);

	///Ins = Cast<UPlayerData>(save);

	//this = getData;
	//Loadsave
}
//
//void UPlayerData::SaveLessions(FGameLession &usersdata, FString OutPreview)
//{
//	// TODO: save lessions
//	FString fileAbc = FPaths::ProjectSavedDir() + "SaveGames/AcademyPreview.json";
//	FString outJsStr;
//	//convert Struct to String
//	bool success = FJsonObjectConverter::UStructToJsonObjectString<FGameLession>(usersdata, outJsStr);
//	lCreateFileFromString(outJsStr, fileAbc);
//	// = Cast<UPlayerData>(UGameplayStatics::CreateSaveGameObject(UPlayerData::StaticClass()));
//	//CurrentGame = usersdata.CurrentGame;
//	this->CurrentGame = usersdata;
//	UGameplayStatics::SaveGameToSlot(this, "LeeTdvnGameData", 1);
//}
//
//void UPlayerData::SaveGameDatas()
//{
//	// TODO: Data all game
//}
//
//void UPlayerData::SaveUserData()
//{
//}
//
//
//FGameHistoryData UPlayerData::LoadGameData(bool& success)
//{
//	// TODO: Load All Game Data
//	//this = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot(SlotName, lessionId));
//	Ins = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot("SlotName", 1));
//
//	return  Ins->lPlayerHistorySlot;
//}
//
//FGameLession UPlayerData::LoadCurrentGameSession()
//{
//	UPlayerData* load = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot(CurrentLessionSlotName, 1));
//	return load->lPlayerHistorySlot.CurrentGame;
//}
//
//void UPlayerData::OnCompleted(FGameLession& current)
//{
//	//lPlayerHistorySlot.CurrentGame = current;
//	HistoryGames.Add(current);
//	return SaveLessions(CurrentGame);
//}
//
//
//
