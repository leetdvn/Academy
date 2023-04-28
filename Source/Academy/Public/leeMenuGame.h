// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "Online.h" // Online Subsystem
//#include <OnlineSubsystemUtils/Public/OnlineSubsystemUtils.h>
//#include <OnlineSubsystem.h>
//#include <OnlineSubsystemFacebook.h>
#include "leeComfirmWidget.h"
#include "leeParentSettings.h"
#include <Kismet/KismetInternationalizationLibrary.h>
#include <Components/ComboBoxString.h>
#include "Kismet/GameplayStatics.h"
#include "leePanelBase.h"
#include "leePublicInterface.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeMenuGame.generated.h"

/**
 * 
 */
UCLASS()
class ACADEMY_API UleeMenuGame : public UUserWidget, public IleePublicInterface
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidget))
		UButton* lParentsButton;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidget))
		UleeParentSettings* Settings;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Black", meta = (BindWidget))
		UImage* BlackSky;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Confirm Panel", meta = (BindWidget))
		UleeComfirmWidget* Confirm;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Confirm Premium Panel", meta = (BindWidget))
		UleeComfirmWidget* ConfirmPremium;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnMenuClick(FString menuName);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void SetBlackSkyVisible(bool isOn,int32 zOder=0);

	UFUNCTION()
		void OnBlackSkyTouch();

	UFUNCTION()
		void OnPremiumLockClick();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void ConfirmClosed() { return SetConfirmToogle(); }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnOperConfirm() { return SetConfirmToogle(true); }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnOperConfirmPre() { return SetConfirmPremiumToogle(true); }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void ConfirmPremiumClosed() { return SetConfirmPremiumToogle(); }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnParentClicked();
	//UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
	//	void OnSelectChanged(FString itemname, ESelectInfo::Type SelectionType);
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		AleeHub* lGetleeHub();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void SetConfirmToogle(bool isOn=false,FString field ="");


	void SetConfirmPremiumToogle(bool isOn = false);


	UleeGameInstance* GIns;

protected:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Menu" ,meta=(BindWidget));
		UleePanelBase* GameMenu;
	
	void SetUnLockPremium(bool Unlock = false);

	void OnConfirmOpen();


	virtual void NativeConstruct() override;

	FString mapOpen;
	
	bool SettingsOn;

	FString StrTable = "/Game/Stringtable/HomeMenu";

	bool IsPremium(FString textName);
	/*Assign Name of Menu Button */
	TArray<FString> leeMenu = { "Numbers","Shape", "Shape2","Environment","ShapeItems"};

	TArray<FString> PremiumLists = { "shape2","shape3","shapeitems" };

};
