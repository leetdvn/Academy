#pragma once
#include <Kismet/GameplayStatics.h>
#include "Components/AudioComponent.h"
#include "leeDragWidget.h"
#include "leePublicEnum.h"
#include "leePanelBase.h"
#include "Components/PanelWidget.h"
#include "Components/Image.h"
#include "leePublicEnum.h"
#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include "CanvasFourBox.generated.h"

/**
 *
 */

UCLASS(BlueprintType)
class ACADEMY_API UCanvasFourBox : public UCanvasPanel , public IleePublicInterface
{
	GENERATED_BODY()

public:

	UCanvasFourBox(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Question")
		TArray<UImage*> lQuestions;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Choises")
		TArray<UleePanelBase*> lUserChoises;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Topic Source Folder")
		FString lTopicSourceFolder;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Choise Source Folder")
		FString lChoiseSourceFolder;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "lee Wave")
		TArray<UDialogueWave*> lWaveSound;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "lee Dialog Context")
		TArray<FDialogueContext> lContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidget))
		UButton* GameHistoriesButton;

	UleePanelBase* lGetChoiseAt(int32 idx);

	UImage* lGetQuestionAt(int32 idx);

	void lSetChoiseBgr(int32 idx, FString& path, bool isDragButton);

	void lSetQuestions(TArray<FString> &paths);

	void lSetChoiseTextAt(int32 idx,TArray<FString> texts);

	//implantation
	void CreateGenerator(FFourBoxData& outData);
	
	//
	void OnLoadFromData(FFourBoxData& outData);

	//get Correct Number
	int32 lGetCorrectNumberAt(int32 idx);

	//generator game topic random in the source directory
	TArray<FString> lGeneratorTopics(FFourBoxData& outData);

	//generator choise random in the source directory
	TArray<FString> lGeneratorChoiseBgr(FFourBoxData& outData);

	void lGetCorrectButtons(TArray<UleeBaseButton*>& buttons);
	//topics 
	TArray<FString> lTopics;

	//bind button
	TArray<UleeBaseButton*> CorrectButtons;
	TArray<UleeBaseButton*> UnCorrectButtons;

	void lClearChecked();

	void lClearActionBound();

	void lGeneratorNumber(FFourBoxData& outData);

	
protected:


};