// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Components/HorizontalBox.h>
#include "leeGameHistories.h"
#include "Components/CanvasPanel.h"
#include "leePublicEnum.h"
#include "leeDecorPanel.h"
#include "leePublicInterface.h"
#include <Components/RichTextBlock.h>
#include <Components/TextBlock.h>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeAlphaBet.generated.h"

/**
 * 
 */

#define ALPHADEFAULT "AcademyAssets/Assets/Topic/AlphaBet/"
#define ALPHACHOISES "AcademyAssets/Assets/ChoiseAnswers/AlphaChoises/"

UCLASS(BlueprintType)
class ACADEMY_API UleeAlpha : public UCanvasPanel, public IleePublicInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Topic")
		UImage* topicImg;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Choises")
		TArray<UImage*> ChoisePanels;

	/*Create new topic*/
	FString CreateNewTopic();

	/*Generator Choise*/
	TArray<FString> GeneratorChoises();

	/*Create new Choise*/
	void CreateNewChoises();

	/*Get return All Choises*/
	TArray<FString> GetChoises() { return choisePath; }

private:

	FString topicName;

	TArray<FString> choisePath{};
};


UCLASS(BlueprintType)
class ACADEMY_API UleeAlphaBet : public UUserWidget , public IleePublicInterface
{
	GENERATED_BODY()
	
public:

	UleeAlphaBet(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Mode", meta = (BindWidget))
		TEnumAsByte<lGameType> m_type=AlphaBet;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Title", meta = (BindWidget))
		URichTextBlock* ltitle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Description", meta = (BindWidget))
		UTextBlock* lDescription;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Top Decorations", meta = (BindWidget))
		UleeDecorPanel* topdecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Bottom Decorations", meta = (BindWidget))
		UleeDecorPanel* botdecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Histories", meta = (BindWidget))
		UleeGameHistories* GameHistories;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Alpha", meta = (BindWidget))
		UleeAlpha* Alpha;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnHistoriesUp();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnReplay();

	/*New Game Initialize*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void NewGameInitialize();

	/*Load Game form Array Data : Params game Id*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void LoadGameFromData(int32 gameId);

	/*On Correct clicked*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnCorrectClick();

	bool isNewGame{};

protected:

	virtual void NativeConstruct() override;

	FAlphaBetData c_Data;
};
