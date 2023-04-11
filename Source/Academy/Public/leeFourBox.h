#pragma once

#include "leeDecorPanel.h"
#include "lee4BoxData.h"
#include "leeGameHistories.h"
#include "leeGameInstance.h"
#include "CanvasFourBox.h"
#include "leeDragWidget.h"
#include "leePublicEnum.h"
#include "leePanelBase.h"
#include "Components/PanelWidget.h"
#include "Components/Image.h"
#include "leePublicInterface.h"
#include "leePublicEnum.h"
#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include <Components/RichTextBlock.h>
#include "leeFourBox.generated.h"


/**
 *
 class game type fourbox all 
 */

UCLASS(BlueprintType)
class ACADEMY_API UleeFourBox : public UUserWidget, public IleePublicInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Game Type")
		TEnumAsByte<lGameType> m_type = FourBox;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Question",meta=(BindWidget))
		UCanvasFourBox* lFourBox;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Title", meta = (BindWidget))
		URichTextBlock* ltitle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Description", meta = (BindWidget))
		UTextBlock* lDescription;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Top Decor Panel", meta = (BindWidget))
		UleeDecorPanel* ltopdecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Bottom Decor Panel", meta = (BindWidget))
		UleeDecorPanel* lbottomdecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Histories", meta = (BindWidget))
		UleeGameHistories* GameHistories;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Win Widget", meta = (BindWidget))
		UUserWidget* WinWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Session ID")
		int32 GameId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "New Game")
		bool isNewGame;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void NewFourBoxInit();
	
	FFourBoxData &GetData() { return fourdata; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void LoadGameAt(int32 dataIndex);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnCorrectAnswer(UleeBaseButton* button);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnUnCorrectAnswer();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnIdReCeiveClick();
	
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnHistoriesUp();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetWinOnOff(bool isOn);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnStarUp(int32 valueUp);

	//UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
	//	FString lGetUserId() { return userdata->UserID; }

	//UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
	//	int lGetStar() { return userdata->Star; }
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
	void OnRePlayGame();

	void BindAction();


protected:

	virtual void NativeConstruct() override;

	//void FillAnimationsMap();

	void ReloadData();


	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		UleeGameInstance* GameIns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Answer Limited")
		int32 Answerlimited;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Max Correct Answer")
		int32 AnswerCorrect;

	Ulee4BoxData* box4S;

	TArray<UleeBaseButton*> lCorrectButtons;

	FFourBoxData fourdata,LoadData;

	bool isReplay;
};

