#pragma once

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

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Game Type")
		TEnumAsByte<lGameType> ltypeGame = FourBox;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Question")
		TArray<UImage*> lQuestions;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Choises")
		TArray<UleePanelBase*> lUserChoises;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Topic Source Folder")
		FString lTopicSourceFolder;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Choise Source Folder")
		FString lChoiseSourceFolder;

	UleePanelBase* lGetChoiseAt(int32 idx);

	UImage* lGetQuestionAt(int32 idx);

	void lSetChoiseBgr(int32 idx, FString& path, bool isDragButton);

	void lSetQuestions(TArray<FString> &paths);

	void lSetChoiseTextAt(int32 idx,TArray<FString> texts);

};