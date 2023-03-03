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
	ReloadData();
	return !isNewGame ? OnLoadCurrentGame() : NewGameThreelineInit();
	//int gameid = GameIns->GameData->HistoryGames.Num();
	//SessionID = gameid > 0 ? gameid : 1;
	//FString Topics = lThreeline->lTopicSourceFolder;
	//FString Choise = lThreeline->lChoiseSourceFolder;
	//InitializeThreeLineopic(Topics,Choise);


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

void UleeBaseLessions::InitializeAnswers(TArray<FString> correctName, FGameLession& lession , FString AnswerDir, bool isSwap)
{
	//craete shape
	int count{};
	for (auto& p : lThreeline->lUserChoises) {

		p->ClearButtons();
		//FString defaultPath = "AcademyAssets/Assets/ChoiseAnswers/AnimalShape";
		FString path = FPaths::ProjectContentDir() + AnswerDir;
		//get all img in directory
		TArray<FString> shape{};
		FString correctStr = FindContentFromPath(path, correctName[count]);
		shape.AddUnique(correctStr);

		//get number diffirent files in directory ignore duplicate
		lGetRandFilesFromDirectory(path, shape, correctName.Num());

		//TArray<UleeDragWidget*> btns = lThreeline->LoadChoisesAt(mainData.GetChoiseAt(count), count + 1, count);
		for (int i = 0; i < shape.Num();i++) {

			//swap index
			if(isSwap)
				shape.SwapMemory(i, lRand(i,shape.Num()));
			FString randPath = "/Game/" + AnswerDir + "/" + shape[i];

			//create buttons and binding Muticast DeleGate
			UleeDragWidget* btn = p->lCreateDragButton(randPath, true, true, "", count + 1);
				//btns[i];
			//draft need refactor
			btn->OnDropCorrect.AddDynamic(this, &UleeBaseLessions::OnDropCorrected);
			btn->OnDropFail.AddDynamic(this, &UleeBaseLessions::OnDropFailure);
			btn->OnDropTimes.AddDynamic(this, &UleeBaseLessions::OnDropTimes);
			lession.Topics[count].Choises.Add(randPath);
		}

		count++;
	}
}

void UleeBaseLessions::InitializeThreeLineopic(FString& sourcefolder, FString& choiseFolder)
{
	//if (lPanelWidget->GetClass()->GetName().StartsWith("Scroll")) return;
	if (!lIsValidThreeLine()) {
		lDebug("not is Valid Question or user choises.");
		return;
	}
	FGameLession  nlession;
	nlession.LessionType = Threelines;
	//register game id
	nlession.LessionID = SessionID == 0 ? 1 : SessionID;
	nlession.GameTitle = ltitle->GetText().ToString();
	nlession.GameDescriptions = lDescription->GetText().ToString();


	// case has child
	FString defaultPath = "AcademyAssets/Assets/Topic/Animal";
	FString path = FPaths::ProjectContentDir() + sourcefolder;
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
		nlession.Topics.Add(topic);
		nlession.TopicNames.Add(exceptions[i]);
	}
	//"AcademyAssets/Assets/ChoiseAnswers/AnimalShape"
	InitializeAnswers(exceptions,nlession, choiseFolder,true);

	GameIns->SaveCurrentGameData(nlession);

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
	//if (DropCorrecttimes == 3) {
	//	GameIns->GameData->HistoryGames.Add(mainData);
	//	GameIns->SaveCurrentGameData(mainData);
	//}
	lDebug(report);
	lOnDropVisible = true;

}

void UleeBaseLessions::OnLoadCurrentGame() {

	switch (mainData.LessionType)
	{
	case None:return lDebug("None game type");
	case Threelines: return  LoadThreeLineGame(mainData);
	case FourBox:
		break;
	case DragDrop:
		break;
	case Line2Column:
		break;
	case AlphaBet:
		break;
	}
}

void UleeBaseLessions::LoadThreeLineGame(FGameLession& game)
{
	//load current game from save data
	lDebug(game.GameTitle, FColor::Blue, "Title");
	lDebug(game.GameDescriptions, FColor::Blue, "Desc");
	lDebug(game.LessionType, FColor::Green, "Desc");

	//reload data
	ReloadData();
	//ltitle->SetText(FText::FromString(game.GameTitle));
	//lDescription->SetText(FText::FromString(game.GameDescriptions));

	/*int gameid = GameIns->GameData->HistoryGames.Num();
	SessionID = gameid > 0 ? gameid : 1;
	FString Topics = lThreeline->lTopicSourceFolder;
	FString Choise = lThreeline->lChoiseSourceFolder;
	InitializeThreeLineopic(Topics, Choise);*/
	TArray<int32> ids = { 1,2,3 };
	TArray<FString> correctName = game.TopicNames;
	lThreeline->LoadQuestions(game.GetQuestions(), ids);
	InitializeAnswers(correctName,game, lThreeline->lChoiseSourceFolder, false);
	//lThreeline->LoadAllChoise(mainData);
}

void UleeBaseLessions::LoadFourBoxGame(FGameLession& game)
{
}

TArray<FString> UleeBaseLessions::lGetSwapString(FString dir, TArray<FString> correctname)
{
	TArray<FString> shape{};
	for (int i = 0; i < correctname.Num(); i++) {
		FString path = FPaths::ProjectContentDir() + dir;
		//get all img in directory
		
		FString correctStr = FindContentFromPath(path, correctname[i]);
		shape.AddUnique(correctStr);

		//get number diffirent files in directory ignore duplicate
		lGetRandFilesFromDirectory(path, shape, correctname.Num());
	}
	return TArray<FString>();
}

void UleeBaseLessions::ReloadData()
{
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameIns) { lDebug("Game Instance Nullptr"); }
	GameIns->LoadGameData();
	mainData = GameIns->GameData->CurrentGame;
	//mainData.LessionType = Threelines;
}

void UleeBaseLessions::NewGameThreelineInit()
{
	///generate new game random topic answer
	int gameid = GameIns->GameData->HistoryGames.Num();
	SessionID = gameid > 0 ? gameid : 1;
	FString Topics = lThreeline->lTopicSourceFolder;
	FString Choise = lThreeline->lChoiseSourceFolder;
	InitializeThreeLineopic(Topics, Choise);

}

void UleeBaseLessions::lDeleyCall() {
	lDebug("delay call");
}

void UleeBaseLessions::ReplayGame() {

	FString current = GetWorld()->GetCurrentLevel()->GetName();
	UGameplayStatics::OpenLevel(GetWorld(), FName(current));
	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, [this]() {LoadThreeLineGame(mainData); }, 3.0f, false);

}