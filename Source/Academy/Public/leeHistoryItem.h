// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leeLibraries.h"
#include <Components/Button.h>
#include "leePublicInterface.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeHistoryItem.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHistories, UleeHistoryItem*, Item);

UCLASS()
class ACADEMY_API UleeHistoryItem : public UUserWidget , public IleePublicInterface , public IleeLibraries
{
	GENERATED_BODY()
	
public:
	UleeHistoryItem(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Info", meta = (BindWidget))
		UTextBlock* ItemInfo;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "BackGround", meta = (BindWidget))
		UButton* ItemBgr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Check Item", meta = (BindWidget))
		UImage* ItemCheck;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game ID")
		int32 ItemID;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Image Path Lock")
		UTexture2D* LockPath;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Image Path UnLock")
		UTexture2D* UnLockPath;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FOnHistories OnItemClick;

	TSharedPtr<FJsonObject> JsGameObject;

	FString ObjectStr;

	UButton* lTakeItem(bool isLock);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnMouseDown();

protected:

	virtual void NativeConstruct() override;
};
