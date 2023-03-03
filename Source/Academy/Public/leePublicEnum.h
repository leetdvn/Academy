#pragma once
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
enum AgeType {

	TwoFour UMETA(DisplayName = "Age 2-4"),
	ThreeFive UMETA(DisplayName = "Age 3-5"),
	FourSix UMETA(DisplayName = "Age 4-6"),
};

UENUM(BlueprintType)
enum lGameType {
	None UMETA(DisplayName = "None"),
	Threelines UMETA(DisplayName = "Three Lines"),
	FourBox UMETA(DisplayName = "Four Box"),
	DragDrop UMETA(DisplayName = "Drag Drop"),
	Line2Column UMETA(DisplayName = "Shape"),
	AlphaBet UMETA(DisplayName = "Choise"),
};

UENUM(BlueprintType)
enum lSlotType {

	VerticalBox UMETA(DisplayName = "Vertical"),
	HorizontalBox UMETA(DisplayName = "Horizontal"),
	ScrollBox UMETA(DisplayName = "Scroll"),
};

UENUM(BlueprintType)
enum lTopicType {

	Animal UMETA(DisplayName = "Animal"),
	Fruit UMETA(DisplayName = "Fruit"),
	Food UMETA(DisplayName = "Food"),
	Human UMETA(DisplayName = "Human"),
	Cube UMETA(DisplayName = "Cube"),
	Count UMETA(DisplayName = "Count Number"),
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
struct FGameLession : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TEnumAsByte<lGameType> LessionType ;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int LessionID;

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
	//FGameLession& operator=(const FGameLession& other) {
	//	return ;
	//}

	FGameLession() :
		LessionType(None),
		LessionID(0),
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
struct FGameHistoryData : public FTableRowBase
{
	GENERATED_BODY()


	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FGameLession> Games;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameLession CurrentGame;

	int NumCompleted() { return Games.Num(); }

	FGameHistoryData& operator=(const FGameHistoryData& other) {
		return *this;
	}

};