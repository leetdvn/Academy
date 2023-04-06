// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <leeLibraries.h>
#include <leeHistoryItem.h>
#include <Components/GridPanel.h>
#include <PlayerData.h>
#include <Components/Image.h>
#include <Components/Button.h>
#include <Components/ScrollBox.h>
#include <Components/TextBlock.h>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeGameHistories.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ACADEMY_API UleeGameHistories : public UUserWidget , public IleeLibraries , public IleePublicInterface
{
	GENERATED_BODY()

public:
	UleeGameHistories(const FObjectInitializer& ObjectInitializer);
	

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Off Button", meta = (BindWidget))
		UButton* lTurnOffButton;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Grid", meta = (BindWidget))
		UGridPanel* lGridPanel;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Bgr", meta = (BindWidget))
		UImage* lBgr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Unlock Item")
		TSubclassOf<UUserWidget> ItemHistories;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* OpenUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* CloseDown;


	bool isOpened;

	void OnHistoriesInit(UPlayerData* &playerData);

	void CreateGameHistories(TEnumAsByte<lGameType> gtype);

	template<class T>
	void OnHistoriesImplantment(TArray<T> &Games);

	void OnHistoriesDown();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnMouseClicked(UleeHistoryItem* item);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
	void OnSwitchMapFromHistories(FString gametype, UleeHistoryItem*& item);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
	AleeHub* GetleeHub();

	void lOpenMapLevel(FString mapname);

	FString lGetTypeFromHistories(UleeHistoryItem* item);
	//UUserWidget* CreateWidgetItem(TSubclassOf<UUserWidget> widget);

	template <typename T>
	FORCEINLINE T lGetEnumFromStr(const FString name, FString enumStr);
	
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnOpenUp();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnCloseDown();

protected:
	virtual void NativeConstruct() override;
};

