// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "Online.h" // Online Subsystem
//#include <OnlineSubsystemUtils/Public/OnlineSubsystemUtils.h>
//#include <OnlineSubsystem.h>
//#include <OnlineSubsystemFacebook.h>
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
		UComboBoxString* box;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidget))
		UButton* lParentsButton;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidget))
		UleeParentSettings* Settings;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidget))
		UTextBlock* InfoText;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnMenuClick(FString menuName);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnParentClicked();
	//UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
	//	void OnSelectChanged(FString itemname, ESelectInfo::Type SelectionType);
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		AleeHub* lGetleeHub();
protected:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Menu" ,meta=(BindWidget));
		UleePanelBase* GameMenu;
	
	virtual void NativeConstruct() override;

	FString mapOpen;
	
	bool SettingsOn;

	FString StrTable = "/Game/Stringtable/HomeMenu";

	/*Assign Name of Menu Button */
	TArray<FString> leeMenu = { "Environment","Numbers","Shape", "Shape2","ShapeItems"};
};
