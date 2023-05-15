// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leeSmartCharacter2D.h"
#include "leeComfirmWidget.h"
#include "leeDecorPanel.h"
#include "leeGameInstance.h"
#include "leeDynamicPanel.h"
#include "leePublicEnum.h"
#include "leePanelBase.h"
#include "leePublicInterface.h"
#include <Components/TextBlock.h>
#include <Components/CanvasPanel.h>
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Async/Async.h"
#include "Blueprint/UserWidget.h"
#include <Engine/DataTable.h>
#include <NiagaraSystemWidget.h>
#include <leeGameHistories.h>
#include <Particles/ParticleSystemComponent.h>
#include <Components/RichTextBlock.h>
#include "leeBaseLessions.generated.h"

class UImage;
class UPanelWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompletedGame, UleeBaseLessions*, CurrentGame);

#define TOPICPREMIUM "AcademyAssets/Assets/Topic/Premium_Animal"
#define TOPICENVI "AcademyAssets/Assets/Topic/Environment"
#define TOPICDEFAULT "AcademyAssets/Assets/Topic/Animal"

#define CHOISEPREMIUM "AcademyAssets/Assets/ChoiseAnswers/PremiumShape"
#define CHOISEENVI "AcademyAssets/Assets/ChoiseAnswers/EnvShape"
#define CHOISEDEFAULT "AcademyAssets/Assets/ChoiseAnswers/AnimalShape"


class AleeHub;
/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class ACADEMY_API UleeBaseLessions : public UUserWidget, public IleePublicInterface
{
	GENERATED_BODY()

public:
	UleeBaseLessions(const FObjectInitializer& ObjectInitializer);
	~UleeBaseLessions() {  };

#pragma region UFUNCTION / PROPERTY Uneal


	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Topic Types")
		TEnumAsByte<lGameType> GameType;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Lines Modes")
		TEnumAsByte<LineModes> Mode;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "StringTable")
		FString TableStr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Title", meta = (BindWidget))
		URichTextBlock* ltitle;

	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "VFX", meta = (BindWidget))
	//	UNiagaraSystemWidget* mouseFX;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Description", meta = (BindWidget))
		UTextBlock* lDescription;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Top Decor Panel", meta = (BindWidget))
		UleeDecorPanel* ltopdecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Bottom Decor Panel", meta = (BindWidget))
		UleeDecorPanel* lbottomdecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Dynamic Canvas", meta = (BindWidget))
		UThreeLines* lThreeline;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Win Widget", meta = (BindWidget))
		UUserWidget* WinWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Confirm Widget", meta = (BindWidget))
		UleeComfirmWidget* ConfirmPopup;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game ID")
		int  SessionID;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "New Game")
		bool isNewGame;

	UPROPERTY(BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Runing")
		bool isGameRuning;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		UleeGameInstance* GameIns;

	/*Correct click Event Delegate */
	UPROPERTY(BlueprintAssignable,  Category = "EventDispatchers")
		FOnCompletedGame OnCorrectClick;

	/*Correct click Event Delegate */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Histories", meta = (BindWidget))
		UleeGameHistories* GameHistories;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Black", meta = (BindWidget))
		UImage* BlackSky;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnIDrop(bool isCorrect);


	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnUnlockDialog();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnPlayerGetWard();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnGoToShop();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void ToogleConfirmed(bool isOn,FString FeildMessage="");

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void CloseDialog() { ToogleConfirmed(false); };

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnSaveUserStar();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void InitializeThreeLineopic(FString& sourcefolder, FString& choiseFolder);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool lIsValidThreeLine();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lCreateNewChoises(TArray<FString> correctName, FGameLession& lession, FString AnswerDir = "", bool isSwap = false);

	//Create new Game Type Three line lession
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void NewGameThreelineInit();

	/*load current game from save data */
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void LoadThreeLineGame();

	/*Load Game From Histories data at index*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void LoadGameAt(int32 sessionGameID);

	/*on replay*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnReplay();

	/*toogle on off popup win*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetWinOnOff(bool isOn);

	/*Get Path Matching Topic*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		FString lGetTopicMatchingPath(TEnumAsByte<LineModes> linemode, bool isChoise = false);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool CheckIsAntiAds();


	/*check User is Premium*/
	bool isPremiumUser=true;

	/*Load Game From Histories*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnHistoriesUp();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void SetBlackSkyVisible(bool isOn);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool CheckTutorials();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool isFirebaseLogins();

	UFUNCTION()
		void OnBlackSkyTouch();

	template<class T>
	T* IGetChacter(UWorld* world);

	bool isMakeSound{};
#pragma endregion 

	FORCEINLINE void lGetAllPanels(UPanelWidget* parent, TArray<UleePanelBase*> &outpanels);
protected:

	virtual void NativeConstruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent) override;

	int32 Droptimes;
	int32 DropCorrecttimes;
	int32 DropFailtimes;

	bool lOnDropVisible;

	FGameLession gamedata, DataLastGame;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils")
		Ulee3LinesData* line3S;


	TArray<UleePanelBase*> lPanels;
	//assign delegate
	void BindButtons();


	bool isReplay;

	// Swap position Player Choise Shape return Array of Paths 
	TArray<FString> lSwapChoises(FString AnswerDir, FString correctname);

};

template<class T>
inline T* UleeBaseLessions::IGetChacter(UWorld* world)
{
	if (!world) return nullptr;
	ACharacter* fCharacter = UGameplayStatics::GetPlayerCharacter(world, 0);
	if (fCharacter)
		return Cast<T>(fCharacter);
	return nullptr;
}
