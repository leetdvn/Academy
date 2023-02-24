// Fill out your copyright notice in the Description page of Project Settings.


#include "leeBaseLessions.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/DataTable.h>

UleeBaseLessions::UleeBaseLessions(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//implant static 
	//UIleeDrop::F
}

void UleeBaseLessions::NativeConstruct()
{
	//binding event drop for answers
	//load tabale data from path
	InitializeTopic();


}

void UleeBaseLessions::NativeDestruct()
{
}

bool UleeBaseLessions::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UleeBaseButton* DragVisual = Cast<UleeBaseButton>(InOperation->DefaultDragVisual);
	UleeBaseButton* DragObj = Cast<UleeBaseButton>(InOperation->Payload);
	lDebug("drop Bgr");
	if (DragVisual) {
		DragVisual->lSetContentSize();
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
	if (!lChoiseAnswersPanel || correctName.Num() <=0) {
		lDebug("missing panel ");
		return;
	}

	int count{};
	for (auto& p : lChoiseAnswersPanel->GetAllChildren()) {
		UleePanelBase* answerPanel = Cast<UleePanelBase>(p);
		lAnswersPanels.AddUnique(answerPanel);
		if (answerPanel) {
			answerPanel->ClearButtons();
			//FString defaultPath = "AcademyAssets/Assets/ChoiseAnswers/AnimalShape";
			FString path = FPaths::ProjectContentDir() + AnswerDir;
			//get all img in directory
			TArray<FString> shape{};
			FString correctStr = FindContentFromPath(path, correctName[count]);
			shape.AddUnique(correctStr);

			//get number diffirent files in directory ignore duplicate
			lGetRandFilesFromDirectory(path, shape, correctName.Num());

			for (int i = 0; i < shape.Num();i++) {
				//FString correctStr = FindContentFromPath(path, correctName[count]);
				//files.Remove(correctStr);
				shape.SwapMemory(i, lRand(i,shape.Num()));
				FString randPath = "/Game/" + AnswerDir + "/" + shape[i];

				//create buttons and binding Muticast DeleGate
				UleeBaseButton* btn = lAnswersPanels[count]->lCreateButton(randPath, true, true, "", false, count + 1);
				btn->lSetContentSize();
				btn->OnDropCorrect.AddDynamic(this, &UleeBaseLessions::OnDropCorrected);
				btn->OnDropFail.AddDynamic(this, &UleeBaseLessions::OnDropFailure);
				btn->OnDropTimes.AddDynamic(this, &UleeBaseLessions::OnDropTimes);

			}
		}
		count++;
	}
}

void UleeBaseLessions::InitializeTopic()
{
	if (!lTopicPanel || lPanelWidget->GetClass()->GetName().StartsWith("Scroll")) return;

	lTopicPanel->ClearButtons();
	FString defaultPath = "AcademyAssets/Assets/Topic/Animal";
	FString path = FPaths::ProjectContentDir() + defaultPath;
	TArray<FString> ref{}, exceptions{};
	lGetRandFilesFromDirectory(path, exceptions, 3);
	if (exceptions.Num() == 0) {
		lDebug(exceptions.Num());
		return;
	}

	for (int i = 0; i < exceptions.Num(); i++) {
		FString iPath = "/Game/" + defaultPath + "/" + exceptions[i];
		UleeBaseButton* btn = lTopicPanel->lCreateButton(iPath, true, false, "", true,i+1);
		btn->lSetContentSize();

	}
	InitializeAnswers(exceptions, "AcademyAssets/Assets/ChoiseAnswers/AnimalShape");

}

void UleeBaseLessions::OnSaving(int lessionId, UleeLessionData* data)
{
	if (data->isNull()) {
		return;
	}
	UPlayerData* saveGame = Cast<UPlayerData>(UGameplayStatics::CreateSaveGameObject(UPlayerData::StaticClass()));
	saveGame->lGameCompleted.Add(data);
	saveGame->lCurrentGame = data;
	bool isSave = UGameplayStatics::SaveGameToSlot(saveGame, lSlotName, lessionId);

	//leeTdDebug(isSave, FColor::Black, "Game is Save");
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

void UleeBaseLessions::OnSaving()
{
	if (lData->isNull()) return;

	OnSaving(1, lData);

	TArray<UleePanelBase*> panels{};
	lGetAllPanels(lPanelWidget, panels);
	if (panels.Num() > 0) {
		for (auto& p : panels)
			lDebug(p->GetName());
	}

}

void UleeBaseLessions::OnLoadLession(int lessionId)
{
	//debug 
	if (lessionId <= 0) { 
		
		lDebug(FString("can't load lession id zero.."));
		return; 
	}
	//====================================================

	UPlayerData* load = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot(lSlotName, lessionId));
	lDebug(load->lCurrentGame->lGameID, FColor::Blue,"ID");
	lDebug(load->lCurrentGame->llessiontitle, FColor::Purple, "title");
	lDebug(load->lCurrentGame->ldescription, FColor::Purple, "description");
	lDebug(load->lCurrentGame->lGameType, FColor::Purple, "Type");
}

void UleeBaseLessions::OnDropTimes(int times)
{
	Droptimes++;
	FString report = "Tong So Lan la : " + FString::FromInt(Droptimes);
	lDebug(report,FColor::Green,"Count");

}

void UleeBaseLessions::OnDropFailure(int times)
{
	lDebug("Tra loi sai roi");
	DropFailtimes++;
}

void UleeBaseLessions::OnDropCorrected(int times)
{
	DropCorrecttimes++;
	FString report = "Chuc Mung Ban Tra loi dung : " + FString::FromInt(DropCorrecttimes);

	lDebug(report);
	lOnDropVisible = true;

}
