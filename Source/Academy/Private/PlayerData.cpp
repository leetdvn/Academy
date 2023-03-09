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

	//init
	//JsHistoriesObject = MakeShareable(new FJsonObject());
	//JsGames = TArray<TSharedPtr<FJsonValue>>();
	//USaveGame* save = UGameplayStatics::LoadGameFromSlot("LeeTdvnGameData", 1);
	//leeSaveSystem = UGameplayStatics::CreateSaveGameObject(UPlayerData::StaticClass());
	//leeSaveSystem=	UGameplayStatics::LoadGameFromSlot("LeeTdvnGameData", 1);//UGameplayStatics::CreateSaveGameObject(UPlayerData::StaticClass());
	//convert Struct to String
	//bool success = FJsonObjectConverter::UStructToJsonObjectString<FGameLession>(Ins->CurrentGame, outJsStr);

	///Ins = Cast<UPlayerData>(save);

	//this = getData;
	//Loadsave
}

FString UPlayerData::GetRawHistoriesStr()
{
	TSharedPtr<FJsonObject> obj = BindGamesToHistories();
	FString fileAbc = FString(FPaths::ProjectSavedDir() + "SaveGames/ACademyPreview.json");
	FString preview = lJsontoStr(obj);
	lCreateFileFromString(preview, fileAbc);
	//UE_LOG(LogTemp, Warning, TEXT("log save : %s"), *preview);
	return RawHistories = preview;
}
void UPlayerData::SaveConstruct()
{
	// Assign Raw data
	GetRawHistoriesStr();
}
TSharedPtr<FJsonValue> UPlayerData::GetGamesAt(int32 index)
{
	if (JsGames.Num() <= 0 || JsGames.Num() - 1 < index) return TSharedPtr<FJsonValue>();
	return JsGames[index];

}
TSharedPtr<FJsonValue> UPlayerData::GetLastGame()
{
	if (JsGames.Num() <= 0) return TSharedPtr<FJsonValue>();
	return JsGames[JsGames.Num() - 1];

}
TSharedPtr<FJsonObject> UPlayerData::BindGamesToHistories()
{
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	TArray<TSharedPtr<FJsonValue>> jsVal;
	int count{};
	for (auto& str : JsGames) {
		FString GameID = "Game_" + FString::FromInt(count);
		jsVal.Add(str);
		count++;
	}
	result->SetArrayField("Games", jsVal);
	JsHistoriesObject->SetObjectField("UserHistories", result);
	return JsHistoriesObject;
}

TSharedPtr<FJsonObject> UPlayerData::LoadHistoriesFromStr()
{
	if (RawHistories.IsEmpty()) {
		lDebug("empty Data...");
		return TSharedPtr<FJsonObject>();
	}

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawHistories);
	bool Success = FJsonSerializer::Deserialize(Reader, JsHistoriesObject);

	const TArray<TSharedPtr<FJsonValue>>* jsVal;
	FString Field = "UserHistories";

	//assign game history Array
	const TSharedPtr<FJsonObject> *result;
	JsHistoriesObject->TryGetObjectField("UserHistories", result);

	if (result) {
		result->Get()->TryGetArrayField("Games", jsVal);
		JsGames = *jsVal;
	}

	UE_LOG(LogTemp, Warning, TEXT("load Histories : %d"), JsGames.Num());

	return JsHistoriesObject;
}

FString UPlayerData::GetGameStrAt(int32 index)
{
	TSharedPtr<FJsonValue> obj = GetGamesAt(index);
	return obj->AsString();
}

FString UPlayerData::GetLastGameStr()
{
	TSharedPtr<FJsonValue> obj = GetLastGame();
	return obj->AsString();
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
