#pragma once

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
		UTextBlock* ltitle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Description", meta = (BindWidget))
		UTextBlock* lDescription;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Top Decor Panel", meta = (BindWidget))
		UPanelWidget* ltopdecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Bottom Decor Panel", meta = (BindWidget))
		UPanelWidget* lbottomdecor;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void NewFourBoxInit();
	
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetChoiseDiffAt(int32 idx);

	FFourBoxData &GetData() { return fourdata; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void LoadCurrentGame();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnCorrectAnswer();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnIdReCeiveClick(int idsent);

protected:

	virtual void NativeConstruct() override;

	void ReloadData();

	void OnSaveData();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		UleeGameInstance* GameIns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Answer Limited")
		int32 Answerlimited;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Max Correct Answer")
		int32 AnswerCorrect;

	int32 GameId;

	FFourBoxData fourdata;

	UPlayerData* userdata;
};

