// Fill out your copyright notice in the Description page of Project Settings.


#include "lee4BoxData.h"

Ulee4BoxData::Ulee4BoxData(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

FFourBoxData Ulee4BoxData::GetLinesAt(int32 index)
{
	return FFourBoxData();
}

TSharedPtr<FJsonValue> Ulee4BoxData::GetGameAsJSonAt(int32 index)
{
	return TSharedPtr<FJsonValue>();
}

void Ulee4BoxData::CreateNewData(FFourBoxData boxData, bool isPrewiew)
{
	DataHistoriesStruct.Add(boxData);

	/*Save preview Json file */
	if (isPrewiew) {

		TArray<TSharedPtr<FJsonValue>> ArrayVal;
		TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
		DataJSonHistoriesObject = MakeShareable(new FJsonObject());

		FString preview = FString(FPaths::ProjectSavedDir() + "SaveGames/Box4SPreview.json");
		for (auto& g : DataHistoriesStruct)
		{
			TSharedPtr<FJsonObject> obj = FJsonObjectConverter::UStructToJsonObject(g);
			ArrayVal.Add(MakeShareable(new FJsonValueObject(obj)));


		}
		result->SetArrayField("Games", ArrayVal);
		DataJSonHistoriesObject->SetObjectField("Box4sHistories", result);

		FString Str = lJsontoStr(DataJSonHistoriesObject);
		lCreateFileFromString(Str, preview);
	}

}
