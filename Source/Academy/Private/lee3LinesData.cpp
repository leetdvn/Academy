// Fill out your copyright notice in the Description page of Project Settings.


#include "lee3LinesData.h"

Ulee3LinesData::Ulee3LinesData(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	DataNums = DataHistoriesStruct.Num();
}

FGameLession Ulee3LinesData::GetLinesAt(int32 index)
{
	if (index <= 0) return FGameLession();
	return DataHistoriesStruct[index];
}

void Ulee3LinesData::CreateNewData(FGameLession& game, bool isPrewie)
{
	DataHistoriesStruct.Add(game);

	/*Save preview Json file */
	if (isPrewie) {

		TArray<TSharedPtr<FJsonValue>> ArrayVal;
		TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
		DataJSonHistoriesObject = MakeShareable(new FJsonObject());

		FString preview = FString(FPaths::ProjectSavedDir() + "SaveGames/LinesPreview.json");
		for (auto& game : DataHistoriesStruct)
		{
			TSharedPtr<FJsonObject> obj= FJsonObjectConverter::UStructToJsonObject(game);
			ArrayVal.Add(MakeShareable(new FJsonValueObject(obj)));


		}
		result->SetArrayField("Games", ArrayVal);
		DataJSonHistoriesObject->SetObjectField("Line3sHistories", result);

		FString Str = lJsontoStr(DataJSonHistoriesObject);
		lCreateFileFromString(Str, preview);
	}

}
