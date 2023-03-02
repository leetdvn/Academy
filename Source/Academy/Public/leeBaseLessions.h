// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leeDynamicPanel.h"
#include "leePublicEnum.h"
#include "PlayerData.h"
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


	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Topic Types")
		TEnumAsByte<lGameType> GameType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite,Category="lee's Ultils",DisplayName="Title",meta=(BindWidget))
		UTextBlock* ltitle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Description", meta = (BindWidget))
		UTextBlock* lDescription;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Top Decor Panel" , meta = (BindWidget))
		UPanelWidget* ltopdecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Bottom Decor Panel", meta = (BindWidget))
		UPanelWidget* lbottomdecor;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Dynamic Canvas", meta = (BindWidget))
		UThreeLines* lThreeline;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game ID")
		int  SessionID;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Input Data",meta=(CreateDefaultSubobject))
		class UPlayerData* lDataSave;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Base Data")
		TSubclassOf<UPlayerData> lBaseData;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		FGameHistoryData mainData;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FOnCompletedGame OnCorrectClick;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnSaving();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnLoadLession(FString slotName,int32 lessionId);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnDropFailure();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnDropCorrected();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnCompleted();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnDropTimes();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void InitializeThreeLineopic(TEnumAsByte<lGameType> igametype=None);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool lIsValidThreeLine();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void InitializeAnswers(TArray<FString> correctName, FString AnswerDir="");


#pragma endregion //Unreal
	FORCEINLINE void OnSaving(FString SlotName,int32 lessionId);

	FORCEINLINE void lGetAllPanels(UPanelWidget* parent, TArray<UleePanelBase*> &outpanels);
protected:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	int32 Droptimes;
	int32 DropCorrecttimes;
	int32 DropFailtimes;

	bool lOnDropVisible;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Data Path")
		UDataTable* lDataTable;

	TArray<UleePanelBase*> lPanels;

};
