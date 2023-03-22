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
	JsHistoriesObject = MakeShareable(new FJsonObject());

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
	if (!obj.IsValid()) return "";
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

TEnumAsByte<lGameType> UPlayerData::GetLastGameType()
{
	TSharedPtr<FJsonObject> obj = GetLastGame()->AsObject();
	if (!obj.IsValid()) return None;
	FString outStr;
	obj->TryGetStringField(gametype, outStr);
	
	//int32 idx = 
	lastGame = lGetEnumFromStr<lGameType>(enumName, outStr); //TEnumAsByte<lGameType>((uint8)idx);
	//bool success{};
	//FName abc = "Texture2D'/Game/AcademyAssets/Assets/ChoiseAnswers/AnimalShape/B_Bear.B_Bear'";
	//lGetAssetFromContent<UTexture2D>(abc, success);
	//lDebug(lastGame,FColor::Purple,"1");
	lDebug(lGetStringFromEnum<lGameType>(lastGame));
	return lastGame;
}

TEnumAsByte<lGameType> UPlayerData::GetGameTypeAt(int32 gameId)
{
	TSharedPtr<FJsonObject> obj = JsGames[gameId]->AsObject();
	if (!obj.IsValid()) return None;
	FString outStr;
	obj->TryGetStringField(gametype, outStr);

	//int32 idx = 
	TEnumAsByte<lGameType> _gtype = lGetEnumFromStr<lGameType>(enumName, outStr); 
	lDebug(lGetStringFromEnum<lGameType>(lastGame));
	return lastGame;
}

TSharedPtr<FJsonObject> UPlayerData::BindGamesToHistories()
{
	if (JsGames.Num() <= 0) return TSharedPtr<FJsonObject>();
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	TArray<TSharedPtr<FJsonValue>> jsVal;
	int count{};
	for (auto& str : JsGames) {
		jsVal.Add(str);
		count++;
	}
	// export json Field name =  GameField and main Field
	result->SetArrayField(GamesField, jsVal);
	JsHistoriesObject->SetObjectField(mainField, result);

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
	JsHistoriesObject->TryGetObjectField(mainField, result);

	if (result) {
		result->Get()->TryGetArrayField(GamesField, jsVal);
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

template <typename T>
T UPlayerData::lGetEnumFromStr(const FString name, FString enumStr) {
	T result{};
	const UEnum* iEnum = FindObject<UEnum>(ANY_PACKAGE, *name, true);
	if (iEnum) {
		int32 Index = iEnum->GetIndexByName(*enumStr);
		result= TEnumAsByte<T>((uint8)Index);
		return result;
	}
	return result;

}

template<typename T>
FString UPlayerData::lGetStringFromEnum(T ipEnum)
{
	return UEnum::GetValueAsString(ipEnum);
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
