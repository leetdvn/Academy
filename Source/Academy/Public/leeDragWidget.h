// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Particles/ParticleSystemComponent.h>
#include <NiagaraSystemWidget.h>
#include <PaperSprite.h>
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "leePublicInterface.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeDragWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIDrop,bool,isCorrect);

class UImage;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class ACADEMY_API UleeDragWidget : public UUserWidget , public IleePublicInterface
{
	GENERATED_BODY()

public:
	UleeDragWidget(const FObjectInitializer& ObjectInitializer);
	~UleeDragWidget();
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		FString lGetImagePath() { return lImagePath; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		UDragDropOperation* lGetDragOperation() { return lOperation; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		UUserWidget* lGetWidgetVisual() { return lDragWidget; }

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Id")
		int32 lIdname;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Tag")
		FString lTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Can Drop")
		bool lIsDrop;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Smoke", meta = (BindWidget))
		UNiagaraSystemWidget* Smoke;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetTexture(FString path);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		UTexture2D* lGetTexture() { return ltexture; };

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetTags(FString newtag) { lTag = newtag; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		FString lGetTags() { return lTag; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetId(int newId) { lIdname =newId; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		int32 lGetId() { return lIdname; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetShadowVisible(bool visible);

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FOnIDrop OniDrop;

	void lSetTexture(UTexture2D* newtexture) { lImagePath = newtexture->GetPathName(); return lDragImage->SetBrushResourceObject(newtexture); }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool isEnv();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetDropSize(FVector2D newsize);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetVisibility(bool visible);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Status Image", meta = (BindWidget))
		UImage* lStatusImage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "shadow Image", meta = (BindWidget))
		UImage* lShadow;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Drag Image", meta = (BindWidget))
		UImage* lDragImage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Env Image", meta = (BindWidget))
		UImage* lEnv;

	void lSetText(FString newText);

protected:

	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent) override;
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Drag Drop Operation")
		TSubclassOf<UDragDropOperation> lDragSubOperation;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "WidgetVisual")
		TSubclassOf<UUserWidget> lDragSubVisual;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Path")
		FString lImagePath;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Path")
		UPaperSprite* lSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Default Path")
		FString lImageDefault;

private:

	void lInitializeDefault(FString ipath);

	UDragDropOperation* lOperation;

	UUserWidget* lDragWidget;

	UCanvasPanelSlot* lPanelSlot;

	UTexture2D* ltexture;
};
