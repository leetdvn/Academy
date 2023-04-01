// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leeDragWidget.h"
#include "leePublicEnum.h"
#include "leePanelBase.h"
#include "Components/PanelWidget.h"
#include "Components/Image.h"
#include "leePublicInterface.h"
#include "leePublicEnum.h"
#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include "Components/ComboBoxString.h"
#include "leeDynamicPanel.generated.h"



/**
 * 
 */

UCLASS(BlueprintType)
class ACADEMY_API UThreeLines : public UCanvasPanel , public IleePublicInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Game Type")
		TEnumAsByte<lGameType> ltypeGame = Threelines;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Question")
		TArray<UleeDragWidget*> lQuestions;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Choise")
		TArray<UleePanelBase*> lUserChoises;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Topic Source Folder")
		FString lTopicSourceFolder;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Choise Source Folder")
		FString lChoiseSourceFolder;

	//UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Choise Source Folder")
	//	UComboBoxString* boxStr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidget))
		UButton* GameHistoriesButton;

	//FGameLession lGetData() { return lGameData; }

	void lTopicsAvalible();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		TArray<FGameTopics> LoadQuestions(TArray<FString> paths, TArray<int32> ids);
	
	int QuestNum() { return lQuestions.Num(); }
	
	int ChoiseNum() { return lUserChoises.Num(); }

	//load choise at index
	TArray<UleeDragWidget*> LoadChoisesAt(TArray<FString> paths,int32 Ids,int32 idx);

	TArray<UleeDragWidget*> GetAllButtons();

	//load all user choise 
	void LoadAllChoise(FGameLession& data);
	UThreeLines() :ltypeGame(Threelines),
		lQuestions({}),
		lUserChoises({}),
		lTopicSourceFolder(""),
		lChoiseSourceFolder("")
	{
	}
protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Preview Data")
		FGameLession lGameData;



};