// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leeAlpha.h"
#include "leeBaseButton.h"
#include "leeGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include <Components/HorizontalBox.h>
#include "leeGameHistories.h"
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

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Win Popup", meta = (BindWidget))
		UUserWidget* WinPanel;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game ID")
		int32 GameId;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnHistoriesUp();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnReplay();

	/*New Game Initialize*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void NewGameInitialize();

	/*Load Game form Array Data : Params game Id*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void LoadGameFromData(int32 gameSession);

	/*On Correct clicked*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnCorrectClick(UleeBaseButton* button);

	/*On Correct clicked*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnWrongClicked(UleeBaseButton* button);

	/*On Correct clicked*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnNextClicked();

	/*Game Instance*/
	UPROPERTY(BlueprintReadWrite, Category = "lee's Ultils")
		UleeGameInstance* GameIns;



	void OnBindAction();


	void WinPanelOnOff(bool Onoff);
	bool isNewGame{}, isReplay{};
	int32 iCorrectNum;

protected:

	virtual void NativeConstruct() override;

	FAlphaBetData c_Data;

	UleeAlphaData* AlPhaData;

};
