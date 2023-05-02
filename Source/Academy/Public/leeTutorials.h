// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "leePublicEnum.h"
#include <Components/TextBlock.h>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeTutorials.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ACADEMY_API UleeTutorials : public UUserWidget
{
	GENERATED_BODY()
	
public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Message", meta = (BindWidget))
		TEnumAsByte<lGameType> mode=None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Message", meta = (BindWidget))
		UTextBlock* Desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Drag Tutorials")
		bool isDragTutorials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* Tutorial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* Touch;

protected:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
};
