// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leeGameInstance.h"
#include "leeDynamicPanel.h"
#include "leePublicEnum.h"
#include "PlayerData.h"
#include "leePanelBase.h"
#include "leePublicInterface.h"
#include <Components/TextBlock.h>
#include <Components/CanvasPanel.h>
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Async/Async.h"
#include "Blueprint/UserWidget.h"
#include <Engine/DataTable.h>
#include "leeBaseLessions.generated.h"

class UImage;
class UPanelWidget;

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
	~UleeBaseLessions() {  };

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

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "New Game")
		bool isNewGame;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		FGameLession DataLoaded;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		UleeGameInstance* GameIns;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FOnCompletedGame OnCorrectClick;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnIDrop(bool isCorrect);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void InitializeThreeLineopic(FString &sourcefolder, FString& choiseFolder);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool lIsValidThreeLine();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lCreateNewChoises(TArray<FString> correctName, FGameLession &lession ,FString AnswerDir="",bool isSwap=false);

	//Create new Game Type Three line lession
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void NewGameThreelineInit();

	//load current game from save data
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void LoadThreeLineGame();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnReplay();

	UFUNCTION()
		void OnlevelChange(ULevel* lv,UWorld* world)
	{
		UE_LOG(LogTemp,Warning,TEXT("level change.."))
	};


#pragma endregion //Unreal

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

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils")
		FGameLession gamedata;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils")
		UPlayerData* userdata;

	TArray<UleePanelBase*> lPanels;
	//assign delegate
	void BindButtons();

	bool isReplay;

	// Swap position Player Choise Shape return Array of Paths 
	TArray<FString> lSwapChoises(FString AnswerDir, FString correctname);

	void ReloadData();
	///generate new game random topic answer
};
