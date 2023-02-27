#pragma once
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
struct FDataGamePathConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TEnumAsByte<lTopicType> TopicType;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString TopicPath;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ChoiseAnswerPath;

};