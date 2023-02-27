// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UILeeDelegate.h"
#include "leePublicEnum.h"
#include "leePublicInterface.h"
#include <Components/Image.h>
#include <Components/CanvasPanel.h>
#include <Components/CanvasPanelSlot.h>
#include <Components/SizeBox.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "Blueprint/DragDropOperation.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeBaseButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCorrectClick,FString,SymbolName);

//correct drop action

/**
 * 
 */
UCLASS(Abstract,BlueprintType,Blueprintable)
class ACADEMY_API UleeBaseButton : public UUserWidget , public IleePublicInterface
{
	GENERATED_BODY()
	
#pragma region  UPROPERTY / UFUNCTION 
public:
	UleeBaseButton* operator=(UleeBaseButton*& other);

	UleeBaseButton(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Runtime", DisplayName = "Size Box",meta=(BindWidget))
		USizeBox* lSizeBox;
	
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Runtime", DisplayName = "Path")
		FString lNormalPath;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Runtime", DisplayName = "Size Button")
		FVector2D lSizeOverride;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Runtime", DisplayName = "Text Size")
		int32 ltextsize;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Runtime", DisplayName = "Button", meta = (BindWidget))
		UButton* lButton;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Runtime", DisplayName = "Check Status", meta = (BindWidget))
		UImage* lCheckStatus;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Runtime", DisplayName = "Image Only")
		bool lImageOnly;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Runtime", DisplayName = "Text Block", meta = (BindWidget))
		UTextBlock* ltextblock;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FOnCorrectClick OnCorrectClick;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetNormalFromPath(FString imgPath, FVector2D normalSize);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetHorverFromPath(FString imgPath);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetPressFromPath(FString imgPath);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetTextFont(int32 fontsize);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetButtonSize(FVector2D sizeOverride);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lUpdateBaseSize(FVector2D newsize);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetText(FString newtext);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		FString lGetText() { return ltextblock->GetText().ToString(); };

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetTextVisibility(bool visible);
	
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetVisibility(bool visible);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetDrag(UUserWidget* DragVisual, bool isDrag);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetPading(FMargin newMargin);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetContentSize();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool lGetTextHiden() { return ltextHiden; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetChecked(bool ischecked);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool lGetChecked();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		TEnumAsByte<lSlotType> lGetSlotType();

	UFUNCTION()
		void OnCorrectClicked();
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OpenMap();
	
	UleeBaseButton* lCopyRef(UleeBaseButton*& other);

	UFUNCTION()
		void lOnListenCallback();

	UFUNCTION()
		void lReplyFourBox();

#pragma endregion
	//UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
	template<class T>
	void lSetRules(ESlateSizeRule::Type nRules);

	virtual void lInitialized(FString ImagePath, FString& text, bool ImageOnly = false,TEnumAsByte<lGameType> gametype=None);

	virtual void lDynamicGameType(TEnumAsByte<lGameType> gametype);

	virtual UTexture2D* lGetTextureButton() { return ltexture2D; }
	int32 rowID;
protected:
	virtual void NativeConstruct() override;

	//void ListenForInputAction(FName ActionName, TEnumAsByte<EInputEvent> EventType, bool bConsume, FOnInputAction Callback);

	virtual void NativeDestruct() override;

	/// <summary>
/// Native Initialize
/// </summary>
	virtual void NativeOnInitialized() override;

	/// <summary>
	/// get Texture from Path file  // example   : /Game/you folder/texture name
	/// </summary>
	/// <param name="imgPath"></param>
	/// <returns></returns>
	UTexture2D* ltexture2D;
	static UleeBaseButton* ins;
	bool ltextHiden;
	FString ltext;
	FVector2D lSize;
	//lTextLayout layoutDefault = Bottom;
};
