// Fill out your copyright notice in the Description page of Project Settings.


#include "leeBaseLessions.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/DataTable.h>
#include <JsonUtilities/Public/JsonObjectConverter.h>

UleeBaseLessions::UleeBaseLessions(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

	//implant static 
	//UIleeDrop::F

}

void UleeBaseLessions::NativeConstruct()
{
	//binding event drop for answers
	//load Game History
	//lDataSave = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot("LeeTdvnGameData", 1));
	/*lDataSave = Cast<UPlayerData>(UGameplayStatics::CreateSaveGameObject(UPlayerData::StaticClass()));
	bool isSuccess{};
	lDataSave->LoadGameData(isSuccess);
	mainData = lDataSave->CurrentGame;*/
	//load tabale data from path
	//InitGameData();
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameIns) {
		GameIns->LoadGameData();
	}
	InitializeThreeLineopic(Threelines);


}

void UleeBaseLessions::NativeDestruct()
{
}

bool UleeBaseLessions::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UleeDragWidget* DragVisual = Cast<UleeDragWidget>(InOperation->DefaultDragVisual);
	UleeDragWidget* DragObj = Cast<UleeDragWidget>(InOperation->Payload);
	lDebug("drop Bgr");
	if (DragVisual) {
		if (DragObj)
		{
			if (lOnDropVisible) {
				lOnDropVisible = false;
			}
			else {
				DragObj->lSetVisibility(false);
			}
		}
	}
	return false;
}

void UleeBaseLessions::InitializeAnswers(TArray<FString> correctName, FString AnswerDir)
{
	//craete shape
	int count{};
	for (auto& p : lThreeline->lUserChoises) {

		//FString defaultPath = "AcademyAssets/Assets/ChoiseAnswers/AnimalShape";
		FString path = FPaths::ProjectContentDir() + AnswerDir;
		//get all img in directory
		TArray<FString> shape{};
		FString correctStr = FindContentFromPath(path, correctName[count]);
		shape.AddUnique(correctStr);

		//get number diffirent files in directory ignore duplicate
		lGetRandFilesFromDirectory(path, shape, correctName.Num());
		for (int i = 0; i < shape.Num();i++) {

			shape.SwapMemory(i, lRand(i,shape.Num()));
			FString randPath = "/Game/" + AnswerDir + "/" + shape[i];

			//create buttons and binding Muticast DeleGate
			UleeDragWidget* btn = p->lCreateDragButton(randPath, true, true, "", count + 1);
			//draft need refactor
			btn->OnDropCorrect.AddDynamic(this, &UleeBaseLessions::OnDropCorrected);
			btn->OnDropFail.AddDynamic(this, &UleeBaseLessions::OnDropFailure);
			btn->OnDropTimes.AddDynamic(this, &UleeBaseLessions::OnDropTimes);
			mainData.Topics[count].Choises.Add(randPath);
		}

		count++;
	}
}

void UleeBaseLessions::InitializeThreeLineopic(TEnumAsByte<lGameType> igametype)
{
	//if (lPanelWidget->GetClass()->GetName().StartsWith("Scroll")) return;
	if (!lIsValidThreeLine()) {
		lDebug("not is Valid Question or user choises.");
		return;
	}
	
	GameType = Threelines;
	//register game id
	int id = GameIns->GameData->HistoryGames.Num();
	mainData.LessionID = id == 0 ? 1 : id ;
	mainData.LessionType = GameType;
	mainData.GameTitle = ltitle->GetText().ToString();
	mainData.GameDescriptions = lDescription->GetText().ToString();
	//if (igametype != Threelines) return;


	// case has child
	//if (lThreeline->ltypeGame == Threelines)
	//	lThreeline->lTopics.lQuestion->ClearButtons();//lTopicPanel->ClearButtons();
	FString defaultPath = "AcademyAssets/Assets/Topic/Animal";
	FString path = FPaths::ProjectContentDir() + defaultPath;
	TArray<FString>  exceptions{};
	lGetRandFilesFromDirectory(path, exceptions, 3);
	if (exceptions.Num() == 0) {
		lDebug(exceptions.Num());
		return;
	}

	for (int i = 0; i < exceptions.Num(); i++) {
		FGameTopics topic{};
		FString iPath = "/Game/" + defaultPath + "/" + exceptions[i] ;
		lThreeline->lQuestions[i]->lSetTexture(iPath);
		lThreeline->lQuestions[i]->lSetId(i + 1);
		topic.ImagePath = iPath;
		mainData.Topics.Add(topic);
	}

	InitializeAnswers(exceptions, "AcademyAssets/Assets/ChoiseAnswers/AnimalShape");


	GameIns->SaveCurrentGameData(mainData);

}

bool UleeBaseLessions::lIsValidThreeLine()
{
	if (lThreeline->lQuestions.Num() <= 0 || lThreeline->lUserChoises.Num() <= 0) return false;
	if (lThreeline->lQuestions.Num() != lThreeline->lUserChoises.Num()) return false;
	return true;
}

void UleeBaseLessions::lGetAllPanels(UPanelWidget* parent, TArray<UleePanelBase*> & outpanels)
{

	//check file exits
	bool Success{};
	TArray<UleePanelBase*> results{};
	TArray<UWidget*> widgets = parent->GetAllChildren();
	if (widgets.Num() <= 0) return ;

	//loop find
#pragma omp parallel for
	for (auto wd : widgets) {
		UleePanelBase* p = Cast< UleePanelBase>(wd);
		if (p) outpanels.Add(p);

		UPanelWidget* box = Cast<UPanelWidget>(wd);
		if (box) {
			lGetAllPanels(box, outpanels);
		}
	}
}

void UleeBaseLessions::OnDropTimes()
{
	Droptimes++;
	FString report = "Tong So Lan la : " + FString::FromInt(Droptimes);
	lDebug(report,FColor::Green,"Count");

}

void UleeBaseLessions::OnDropFailure()
{
	lDebug("Tra loi sai roi");
	DropFailtimes++;
}

void UleeBaseLessions::OnDropCorrected()
{
	DropCorrecttimes++;
	FString report = "Chuc Mung Ban Tra loi dung : " + FString::FromInt(DropCorrecttimes);

	lDebug(report);
	lOnDropVisible = true;

}