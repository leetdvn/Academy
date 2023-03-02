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
	lDataSave = Cast<UPlayerData>(UGameplayStatics::CreateSaveGameObject(UPlayerData::StaticClass()));
	mainData = lDataSave->lPlayerHistorySlot;
	//load tabale data from path
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
	//if (!lChoiseAnswersPanel || correctName.Num() <=0) {
	//	lDebug("missing panel ");
	//	return;
	//}

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
			mainData.CurrentGame.Topics[count].Choises.Add(randPath);
		}

		count++;
	}

	//create data
	//lDataTable->AddRow("CurrentGame", mainData.CurrentGame);
	//lDataTable->WriteTableAsJSON(EDataTableExportFlags::UsePrettyEnumNames);
	FString fileAbc = FPaths::ProjectSavedDir() + "SaveGames/jsPreview.json";
	
	//runtime create asset devlopment
	FString AssetPath = FPaths::ProjectContentDir() + "Data/TestingAsset.uasset";
	FString InPackagePath = FString("/Game/Data/TestingAsset");

	//UDataTable* nData = lCreateDataTableRuntime("TestingAsset", InPackagePath,AssetPath, lDataTable->RowStruct);

	lDataSave->SaveLessions(mainData);
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
	int id =lDataSave->lPlayerHistorySlot.Games.Num();
	mainData.CurrentGame.LessionID = id == 0 ? 1 : id ;
	mainData.CurrentGame.LessionType = GameType;
	mainData.CurrentGame.GameTitle = ltitle->GetText().ToString();
	mainData.CurrentGame.GameDescriptions = lDescription->GetText().ToString();
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
		mainData.CurrentGame.Topics.Add(topic);
	}

	InitializeAnswers(exceptions, "AcademyAssets/Assets/ChoiseAnswers/AnimalShape");

}

bool UleeBaseLessions::lIsValidThreeLine()
{
	if (lThreeline->lQuestions.Num() <= 0 || lThreeline->lUserChoises.Num() <= 0) return false;
	if (lThreeline->lQuestions.Num() != lThreeline->lUserChoises.Num()) return false;
	return true;
}

void UleeBaseLessions::OnSaving(FString SlotName, int32 lessionId)
{

	//UPlayerData* saveGame = Cast<UPlayerData>(UGameplayStatics::CreateSaveGameObject(UPlayerData::StaticClass()));
	//saveGame->lPlayerHistorySlot = mainData;
	//bool isSave = UGameplayStatics::SaveGameToSlot(saveGame, SlotName, lessionId);

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

	OnSaving("Academy", 1);
	FString fileAbc = FPaths::ProjectSavedDir() + "SaveGames/AcademyPreview.json";
	FString outJsStr;
	//convert Struct to String
	bool success = FJsonObjectConverter::UStructToJsonObjectString<FGameHistoryData>(mainData, outJsStr);
	//Save Preview Json on Project/Save/SaveGames
	lCreateFileFromString(outJsStr, fileAbc);

}

void UleeBaseLessions::OnLoadLession(FString SlotName, int32 lessionId)
{
	//debug 
	if (lessionId <= 0) { 
		
		lDebug(FString("can't load lession id zero.."));
		return; 
	}
	//====================================================

	UPlayerData* load = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot(SlotName, lessionId));
	//lDebug(load->lCurrentGame->lGameID, FColor::Blue,"ID");
	//lDebug(load->lCurrentGame->llessiontitle, FColor::Purple, "title");
	//lDebug(load->lCurrentGame->ldescription, FColor::Purple, "description");
	//lDebug(load->lCurrentGame->lGameType, FColor::Purple, "Type");
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

void UleeBaseLessions::OnCompleted() {

	//lDataSave->lPlayerHistorySlot.Games.Add(mainData.CurrentGame);
	lDataSave->SaveLessions(mainData);
}