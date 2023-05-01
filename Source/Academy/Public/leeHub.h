// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <leeGameInstance.h>
#include "leeBaseLessions.h"
#include "leeFourBox.h"
#include "leeAlphaBet.h"
#include <Components/Image.h>
#include "leePublicInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "leeHub.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGamePause);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEnd);

/**
 * 
 */
UCLASS()
class ACADEMY_API AleeHub : public AHUD, public IleePublicInterface
{
	GENERATED_BODY()
public:
	AleeHub();
	//override game begien
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

#pragma region UFUNCTION / PROPERTY UE
	/// <summary>
	/// Menu Widgets
	/// </summary>
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
	TSubclassOf<UUserWidget> lMenuWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		TSubclassOf<UleeBaseLessions> lThreeLine;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		TSubclassOf<UleeFourBox> lFourBox;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		TSubclassOf<UleeAlphaBet> lAlphaBeet;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		UleeGameInstance* GameIns;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Current GameType")
		TEnumAsByte<lGameType> gametype;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Lines Mode")
		TEnumAsByte<LineModes> LinesMode;


	/// <summary>
	/// Widget ingame list
	/// </summary>
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
	TArray<TSubclassOf<class UUserWidget>> lGameWidgets;

	UPROPERTY(BlueprintAssignable, Category = "Test")
		FOnGameStart lOnGStart;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "lee Wave")
		UDialogueWave* lKidMusic;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "lee Dialog Context")
		FDialogueContext lMusic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils")
		USoundClass* KidMusic;

	/*LoadGame Type four box from data index saved */
	void LoadFourBoxFromData(int32 idx);

	/*LoadGame Type 3 Lines from data index saved */
	void LoadThreelineFromData(int32 idx);

	/*LoadGame TypeAlpha from data index saved */
	void LoadAlphabetFromData(int32 idx);

	/*create new game */
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void CreateNewGame(TEnumAsByte<lGameType> gtype, TEnumAsByte<LineModes> linemode=Normal);

	template<class T>
	T* INewGameWidget(TEnumAsByte<lGameType> gtype, UUserWidget*& outWidget);

	TEnumAsByte<lGameType> GameType() { return gametype; }

	void SetMusicVolume(float volume) {
		if (volume < 0 || volume > 1) return;
		KidMusic->Properties.Volume = volume;
	};

#pragma endregion

protected:

	void SetSessionGameID(int32 gameid) { SessionGameId = gameid; }

	UWorld* leeWorld;
	class UUserWidget* MenuWidget;
	FOnGamePause lOnGPause;
	FOnGameEnd lOnGEnd;
	//LevelChanged onlevelChanged;

	UUserWidget* lMoveButton;
	UUserWidget* lCurrentWidget;
	int32 SessionGameId;


};
