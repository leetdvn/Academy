// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeComfirmWidget.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ACADEMY_API UleeComfirmWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Cancel Button", meta = (BindWidget))
		class UButton* lButtonNo;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Confirm Button", meta = (BindWidget))
		class UButton* lButtonYes;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Message", meta = (BindWidget))
		class UTextBlock* lMessage;

};
