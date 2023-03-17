#pragma once

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


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Question",meta=(BindWidget))
		UCanvasFourBox* lFourBox;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Title", meta = (BindWidget))
		URichTextBlock* ltitle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Description", meta = (BindWidget))
		UTextBlock* lDescription;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Top Decor Panel", meta = (BindWidget))
		UPanelWidget* ltopdecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Bottom Decor Panel", meta = (BindWidget))
		UPanelWidget* lbottomdecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Histories", meta = (BindWidget))
		UleeGameHistories* GameHistories;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidgetAnim),Transient)
		UWidgetAnimation* HistoriesTurnOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* HistoriesTurnOff;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void NewFourBoxInit();
	
	FFourBoxData &GetData() { return fourdata; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void LoadGameAt(int32 dataIndex);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnCorrectAnswer(UleeBaseButton* button);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnIdReCeiveClick();
	
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void TurnOffHistories();
	
	void OnRePlayGame(FFourBoxData & odata);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void LoadCurrentQuestions();

	void BindAction();


	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

	bool PlayAnimationByName(FName AnimationName,
		float StartAtTime,
		int32 NumLoopsToPlay,
		EUMGSequencePlayMode::Type PlayMode,
		float PlayBackSpeed
	);

protected:

	virtual void NativeConstruct() override;
	UPROPERTY(EditAnyWhere)
	TMap<FName, UWidgetAnimation*> AnimationsMap;

	TMap<FString, UWidgetAnimation*> AnimationsMaps;

	//void FillAnimationsMap();

	void ReloadData();

	void OnSaveData();


	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		UleeGameInstance* GameIns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Answer Limited")
		int32 Answerlimited;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Max Correct Answer")
		int32 AnswerCorrect;

	int32 GameId;

	TArray<UleeBaseButton*> lCorrectButtons;

	FFourBoxData fourdata,LoadData;

	UPlayerData* userdata;

	bool isReplay, isNewGame = true;
};

