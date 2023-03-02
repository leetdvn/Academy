// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leePublicEnum.h"
#include "leePanelBase.h"
#include "Components/PanelWidget.h"
#include "Components/Image.h"
#include "leePublicInterface.h"
#include "leePublicEnum.h"
#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include "leeDynamicPanel.generated.h"



/**
 * 
 */
USTRUCT(BlueprintType)
struct FLessionsProp
{
	GENERATED_BODY()


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Question")
		class UleePanelBase* lQuestion;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Question Image")
		class UImage* lQuestionImage;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Question Text")
		class UTextBlock* lQuestionText;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Choise")
		TArray<class UleePanelBase*> lUserChoises;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Decorations")
		TArray<class UImage*> lChoiseImages;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Choise Texts")
		TArray<class UTextBlock*> lChoiseText;

};

UCLASS(BlueprintType)
class ACADEMY_API UThreeLines : public UPanelWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Game Type")
		TEnumAsByte<lGameType> ltypeGame = Threelines;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Topics")
		TArray<FLessionsProp> lTopics;

	FGameLession lGetData() { return lGameData; }

protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Preview Data")
		FGameLession lGameData;



};