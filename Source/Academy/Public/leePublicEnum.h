#pragma once
#include <JsonUtilities/Public/JsonObjectConverter.h>
#include "GameFramework/SaveGame.h"
#include "Components/CanvasPanel.h"
#include <Engine/DataTable.h>
#include "CoreMinimal.h"
#include "leePublicEnum.generated.h"

UENUM(BlueprintType)
enum PanelType {

	Files UMETA(DisplayName = "Panel From Files"),
	Folders UMETA(DisplayName = "Panel From Folder"),
};

UENUM(BlueprintType)
enum LineModes {

	Normal UMETA(DisplayName = "Normal"),
	ExtendPremium UMETA(DisplayName = "Mode ExtendPremium"),
	Environment UMETA(DisplayName = "Mode Environment"),
};

UENUM(BlueprintType)
enum lGameType 
{
	None UMETA(DisplayName = "None"),
	Threelines UMETA(DisplayName = "Three Lines"),
	FourBox UMETA(DisplayName = "Four Box"),
	AlphaBet UMETA(DisplayName = "AlphaBet"),
};

UENUM(BlueprintType)
enum lSlotType {

	VerticalBox UMETA(DisplayName = "Vertical"),
	HorizontalBox UMETA(DisplayName = "Horizontal"),
	ScrollBox UMETA(DisplayName = "Scroll"),
};

UENUM(BlueprintType)
enum kLanguage {

	English UMETA(DisplayName = "English"),
	Vietnamese UMETA(DisplayName = "Vietnamese"),
	Chinaese UMETA(DisplayName = "Chinaese"),
};


USTRUCT(BlueprintType)
struct FGameTopics : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FString> Choises;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Label;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ImagePath;


	FString GetTopic() { return ImagePath; }

	FGameTopics() : Choises({}),
		Label(""),
		ImagePath("")
	{
	}
};

USTRUCT(BlueprintType)
struct FPlayerHistories : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
	TArray<UStruct*> Games;
};

/*
* Structor Game Three line
*/
USTRUCT(BlueprintType)
struct FGameLession : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TEnumAsByte<lGameType> LessionType ;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 GameID;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString GameTitle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString GameDescriptions;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString GameDecorPath;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FString> TopicNames;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FGameTopics> Topics;

	FString gName;


	int TopicsNum() { return Topics.Num(); }

	TArray<FString> GetQuestions(){
		TArray<FString> results{};
		for (auto& p : Topics)
			results.Add(p.GetTopic());
		return results;
	}

	TArray<FString> GetChoiseAt(int32 idx) {
		TArray<FString> results{};
		return Topics[idx].Choises;
	}

	bool operator==(const FGameLession& other) {
		if (LessionType == other.LessionType && 
			GameID == other.GameID &&
			GameTitle == other.GameTitle &&
			GameDescriptions == other.GameDescriptions &&
			TopicNames == other.TopicNames &&
			gName==other.gName
			) {
			return true;
		}
		return false;
	}
	TSharedPtr<FJsonObject> ToObject() {
		return FJsonObjectConverter::UStructToJsonObject(*this);
	}

	FString ToString() {
		FString OutStr;
		FJsonObjectConverter::UStructToJsonObjectString<FGameLession>(*this, OutStr);
		return OutStr;
	}

	bool IsValid() {
		if (LessionType == None || Topics.Num() <= 0 || TopicNames.Num() <= 0) return false;
		return true;
	}

	FGameLession() :
		LessionType(None),
		GameID(0),
		GameTitle(""),
		GameDescriptions(""),
		GameDecorPath(""),
		TopicNames({}),
		Topics({}),
		gName("")
	{
	}

};

USTRUCT(BlueprintType)
struct FFourBoxData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TEnumAsByte<lGameType> LessionType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString GameTitle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString GameDescriptions;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString GameDecorPath;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 GameID;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FString> topicPaths;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FString> ChoiseBgrs;

	TArray<FString> GetTopicPaths() { return topicPaths; }

	TArray<FString> GetChoiseBgrs() { return ChoiseBgrs; }

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FString> textsChoiss;

	FFourBoxData() :
		LessionType(None),
		GameTitle(""),
		GameDescriptions(""),
		GameDecorPath(""),
		GameID(0),
		topicPaths({}),
		ChoiseBgrs({}),
		textsChoiss({})
	{
	}
};

USTRUCT(BlueprintType)
struct FAlphaBetData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TEnumAsByte<lGameType> gtype;

	//UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	//	FString GameTitle;

	//UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	//	FString GameDescriptions;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 GameID;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString topicPath;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<int32> topicNums;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FString> ChoiseBgrs;

	FString GetTopicPaths() { return topicPath; }

	TArray<FString> GetChoiseBgrs() { return ChoiseBgrs; }

	TArray<int32> GetTopicNums() { return topicNums; }

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FString> textsChoiss;

	FAlphaBetData() :
		GameID(0),
		topicPath({}),
		topicNums({}),
		ChoiseBgrs({}),
		textsChoiss({})
	{
	}
};