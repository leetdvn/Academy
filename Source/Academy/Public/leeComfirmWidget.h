// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "leePublicInterface.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeComfirmWidget.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ACADEMY_API UleeComfirmWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Cancel Button", meta = (BindWidget))
		UButton* lButtonNo;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Confirm Button", meta = (BindWidget))
		UButton* lButtonYes;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Message", meta = (BindWidget))
		UTextBlock* lMessage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Price")
		FString ProductID;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Status")
		bool isOpen;

	void lSetConfirmTittle(FString Message);

	void lSetTitleFromTable(FString field);

	void lSetVisible(bool isShow);

protected:

	virtual void NativeDestruct() override;

};
