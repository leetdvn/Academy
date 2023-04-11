// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Image.h"
#include "leePublicInterface.h"
#include "Components/CanvasPanel.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeDecorPanel.generated.h"

/**
 * 
 * Class Decoration Back Grounds
 */

#define PATHDEFAULTS =""

UCLASS()
class ACADEMY_API UleeDecorPanel : public UUserWidget , public IleePublicInterface
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Panel", meta = (BindWidget))
		UCanvasPanel* DecorPanel;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Folder Path Decorations")
		FString PathDecor = "AcademyAssets/hoatietnen/";

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Numbers ", meta = (ClampMin="2",ClampMax="6",UIMin="2",UIMax=6))
		int32 Number;

	void DecorInit(FString pathdecor);

	FString PathInit();

	FString lGetPath() { return decorPath; }

protected:

	FString decorPath;
	//virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	TArray<UImage*> DecorImgs{};
};
