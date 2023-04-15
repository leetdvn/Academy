// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leeDragWidget.h"
#include "leeBaseButton.h"
#include "leePublicInterface.h"
#include "leePublicEnum.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelSlot.h"
#include "leePanelBase.generated.h"


/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class ACADEMY_API UleePanelBase : public UUserWidget, public IleePublicInterface
{
	GENERATED_BODY()
public:
	UleePanelBase(const FObjectInitializer& ObjectInitializer);

	//UleePanelBase* operator=(UleePanelBase*& other);
#pragma region UPROPERTY/ UFUNCTION

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Directory")
		FString lDirectory;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Panels",meta=(BindWidget))
		UPanelWidget* lPanelWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Runtime Button")
		TSubclassOf<UUserWidget> lRuntimeButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Textures Override")
		TArray<UTexture2D*> lTexturesOverride;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Text Override")
		TArray<FString> lTexts;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Static Image")
		TArray<UImage*> lStaticImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Panel Type")
		TEnumAsByte<PanelType> lpaneltype;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Game Type")
		TEnumAsByte<lGameType> ltypeofgame;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Quantity Override")
		int lQuantityOverride;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Image Only")
		bool ImageOnly;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Drag")
		bool iDrag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Drop")
		bool iDrop;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Margin Pading")
		TArray<FMargin> lMargin;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Drops Buttons")
		TArray<UleeDragWidget*> lDragDropButtons;

	/// <summary>
	/// create Button From List Dir input dir can add Image Override
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lNewPanelImageFromDir(FString /*full path directory*/ dir, bool Hastext = false);

	/// <summary>
	///  create Button From list Files inside Dir can add Image Override
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lNewPanelImageFromFiles(FString /*full path directory*/ dir, bool Hastext = false);

	/// <summary>
	/// init panel auto
	/// </summary>
	/// <param name="idx"></param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lInitializePanels(FString /*full path directory*/ dir, TEnumAsByte<PanelType> panel,bool Hastext =false);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lInitializeChoiseAnswer(FString dir,FString ref);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		UleeBaseButton* lGetButton(int idx);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		TArray<UleeBaseButton*> lGetButtons() { return lbuttons; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		TArray<UleeDragWidget*> lGetDragDropButtons() { return lDragDropButtons; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnDelegate(FString gName);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void ClearButtons();
	
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetDisable(bool disables);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lResetChecked();

	bool isCreated() { return lbuttons.Num() > 0 || lDragDropButtons.Num() > 0 ? true : false; };
	
	void lSetMakeSameAt(FString path,bool DragButton);
	/// <summary>
	/// create button add to panels
	/// </summary>
	UleeBaseButton* lCreateNormalButton(FString imgPath, bool ImgOnly, FString text="",int32 rID =-1);

	bool ButtonExists(FString &buttonRef);

	UleeDragWidget* lCreateDragButton(FString imgPath, bool ImgOnly, bool isDrop, FString text = "", int32 rID = -1);

	void lSetPanelId(int32 Id, bool isDragDrop=false);

	void lOverrideTextName(TArray<FString> texts, TArray<UleeBaseButton*> btns);

	void lOverrideTextName(TArray<FString> texts, TArray<UleeDragWidget*> btns);

	void lOverrideTextName(TArray<FString> texts ,bool isDragButtons=false);

	void lOverrideTextures(TArray<UTexture2D*> textures, TArray<UleeBaseButton*> btns, FVector2D size);

	void lOverridePadding(TArray<FMargin> margin, TArray<UleeBaseButton*> btns);

	//void OnDragDetected() override;
#pragma endregion

#pragma region Private Access Varible

protected:
	TArray<UleeBaseButton*> lbuttons;


	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	UleePanelBase* ins;
private:
	FString lCurrentDir;
#pragma endregion
};
