// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leePanelBase.h"
#include "leeBaseButton.h"
#include "Components/PanelWidget.h"
#include "Components/Image.h"
#include "leePublicInterface.h"
#include "leePublicEnum.h"
#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include "leeDynamicCanvas.generated.h"

/**
 * 
 */
UCLASS()
class ACADEMY_API UleeDynamicCanvas : public UCanvasPanel
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Interface", DisplayName = "Panel Type")
		TEnumAsByte<PanelType> lpaneltype;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Interface", DisplayName = "Topics")
		TArray<UleePanelBase*> lTopicPanel;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Interface", DisplayName = "Answer Panels")
		TArray<UleePanelBase*> lAnswersPanels;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Interface", DisplayName = "Static Image")
		TArray<UImage*> lStaticImages;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Interface", DisplayName = "Runtime Buttons")
		TArray<UleeBaseButton*> lRuntimeButtons;
};
