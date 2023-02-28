// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leePublicEnum.h"
#include "PlayerData.h"
#include "leeLessionData.h"
#include "leePanelBase.h"
#include "leePublicInterface.h"
#include <Components/TextBlock.h>
#include <Components/CanvasPanel.h>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Engine/DataTable.h>
#include "leeBaseLessions.generated.h"

class UImage;
class UPanelWidget;

const FString lSlotName = "Academy";


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompletedGame, UleeBaseLessions*, CurrentGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoseGame, UleeBaseLessions*, CurrentGame);

/**
 * 
 */
UCLASS(BlueprintType)
class ACADEMY_API UleeBaseLessions : public UUserWidget , public IleePublicInterface
{
	GENERATED_BODY()
	
public:
	UleeBaseLessions(const FObjectInitializer& ObjectInitializer);
	~UleeBaseLessions() {};

#pragma region UFUNCTION / PROPERTY Uneal
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "decor folder")
		int lID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "decor folder")
		FString lpathDecor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Title Decor")
		UImage* lTitleDecor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Row Object")
		int lrow;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite,Category="lee's Ultils",DisplayName="Title",meta=(BindWidget))
		UTextBlock* ltitle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Description", meta = (BindWidget))
		UTextBlock* lDescription;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Panel Widget", meta = (BindWidget))
		UPanelWidget* lPanelWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Top Decor Panel" , meta = (BindWidget))
		UPanelWidget* ltopdecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Bottom Decor Panel", meta = (BindWidget))
		UPanelWidget* lbottomdecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Topic", meta = (BindWidget))
		UleePanelBase* lTopicPanel;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Answer Panels")
		TArray<UleePanelBase*> lAnswersPanels;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Choise Answers", meta = (BindWidget))
		UPanelWidget* lChoiseAnswersPanel;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Data Lession")
		UleeLessionData* lData;
	
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Data ")
		FString lstructdata;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Lession Type")
		TEnumAsByte<lGameType> lgametype;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Topic Types")
		TEnumAsByte<lTopicType> ltopictype;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Input Data")
		UPlayerData* lDataSave;

	UPROPERTY(VisibleAnyWhere)
		FDataGamePathConfig lCurrentGameData;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FOnCompletedGame OnCorrectClick;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnSaving();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnLoadLession(int lessionId);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnDropFailure();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnDropCorrected();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnDropTimes();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void InitializeThreeLineopic(TEnumAsByte<lGameType> igametype=None);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void InitializeAnswers(TArray<FString> correctName, FString AnswerDir="");


#pragma endregion //Unreal
	FORCEINLINE void OnSaving(int lessionId, UleeLessionData* data);

	FORCEINLINE void lGetAllPanels(UPanelWidget* parent, TArray<UleePanelBase*> &outpanels);
protected:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	int32 Droptimes;
	int32 DropCorrecttimes;
	int32 DropFailtimes;

	bool lOnDropVisible;

	/// <summary>
	/// implant Choise Answer
	/// </summary>
	/// <param name="correctName"></param>

	/// <summary>
	/// implant topic 
	/// </summary>

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Data Path")
		UDataTable* lDataTable;

	TArray<UleePanelBase*> lPanels;
};
