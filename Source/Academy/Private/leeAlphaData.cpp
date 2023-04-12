#include "leeAlphaData.h"

UleeAlphaData::UleeAlphaData(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UleeAlphaData::CreateNewData(FAlphaBetData& gameId, bool isPreview)
{
	//DataHistories.Add(gameId);

	if (isPreview) {

		TArray<TSharedPtr<FJsonValue>> ArrayVal;
		TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
		DataJSonHistoriesObject = MakeShareable(new FJsonObject());

		FString preview = FString(FPaths::ProjectSavedDir() + "SaveGames/Box4SPreview.json");
		for (auto& g : DataHistories)
		{
			TSharedPtr<FJsonObject> obj = FJsonObjectConverter::UStructToJsonObject(g);
			ArrayVal.Add(MakeShareable(new FJsonValueObject(obj)));


		}
		result->SetArrayField("Games", ArrayVal);
		DataJSonHistoriesObject->SetObjectField("AlphaHistories", result);

		FString Str = lJsontoStr(DataJSonHistoriesObject);
		lCreateFileFromString(Str, preview);
	}

}
