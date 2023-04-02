// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <PlayerData.h>
#include "leePublicEnum.h"
#include "leePublicInterface.h"
#include <Components/RichTextBlock.h>
#include <Components/TextBlock.h>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeAlphaBet.generated.h"

/**
 * 
 */
UCLASS()
class ACADEMY_API UleeAlphaBet : public UUserWidget , public IleePublicInterface
{
	GENERATED_BODY()
	
public:

	UleeAlphaBet(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Title", meta = (BindWidget))
		URichTextBlock* ltitle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Description", meta = (BindWidget))
		UTextBlock* lDescription;


protected:

	virtual void NativeConstruct() override;

	UPlayerData* userdata;

};
