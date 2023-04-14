#pragma once

#include <Kismet/GameplayStatics.h>
#include <leeAlphaData.h>
#include "leeBaseButton.h"
#include "Components/Image.h"
#include "CoreMinimal.h"
#include "leePublicInterface.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/UserWidget.h"
#include "leeAlpha.generated.h"


#define ALPHADEFAULT "AcademyAssets/Assets/Topic/AlphaBet/"
#define ALPHACHOISES "AcademyAssets/Assets/ChoiseAnswers/AlphaChoises/"


UCLASS(BlueprintType)
class ACADEMY_API UleeAlpha : public UCanvasPanel, public IleePublicInterface
{
	GENERATED_BODY()

public:

	UleeAlpha(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Topic")
		UImage* topicImg;

	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Choises")
	//	TArray<UImage*> ChoisePanels;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Choises")
		TArray <UleeBaseButton*> ChoiseButtons;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "lee Wave")
		TArray<UDialogueWave*> lWaveSound;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "lee Dialog Context")
		TArray<FDialogueContext> lContext;

	/*Create new topic*/
	FString CreateNewTopic();

	/*Generator Choise*/
	TArray<FString> GeneratorChoises();

	/*Create new Choise*/
	void CreateNewChoises();

	/*Get return All Choises*/
	TArray<FString> GetChoises() { return choisePath; }

	/*check Correct Names*/
	bool isCorrectName(FString name);

	TArray<UleeBaseButton*> CorrectButtons{};

	/*Clear Correct Checked Button*/
	void lClearChecked();

	/*Clear All Bound Buton*/
	void ClearAllBound();

	/*Set Topic Texture*/
	void SetTopicBrush(UTexture2D* tex);

	/*Set Topic Texture*/
	void SetTopicBrush(FString Path);

	/*Set Choise Textures*/
	void SetChoiseBrush(TArray<FString> paths);

	/*Get Topic Name*/
	FString GetTopicName() { return topicName; }

	/*Get Correct Button*/

	TArray<UleeBaseButton*> GetCorrectButtons();

private:

	FString topicName;

	TArray<FString> choisePath{};

	TArray<FString> CorrectNames{};

};