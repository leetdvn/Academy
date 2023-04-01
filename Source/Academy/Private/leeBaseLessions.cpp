// Fill out your copyright notice in the Description page of Project Settings.


#include "leeBaseLessions.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/DataTable.h>
#include <JsonUtilities/Public/JsonObjectConverter.h>
#include <Kismet/KismetInternationalizationLibrary.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <Blueprint/WidgetLayoutLibrary.h>

UleeBaseLessions::UleeBaseLessions(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//lThreeline = Cast<UThreeLines>(lDynamicPanel);
	//implant static 
	//UIleeDrop::F
	//isNewGame = false;
}

void UleeBaseLessions::NativeConstruct()
{
	//binding event drop for answers
	//load Game History
	ReloadData();
	lSetWinOnOff(false);

	if (lThreeline->GameHistoriesButton) {
		lThreeline->GameHistoriesButton->OnClicked.AddDynamic(this, &UleeBaseLessions::OnHistoriesUp);
	}

	return  !isNewGame ? NewGameThreelineInit() : LoadThreeLineGame();

}

void UleeBaseLessions::NativeDestruct()
{
}

void UleeBaseLessions::OnReplay()
{
	FString current = GetWorld()->GetMapName();
	if (current.EndsWith("ThreeLines")) {
		UGameplayStatics::OpenLevel(GetWorld(), FName("ThreeLines"));
		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, [this]() {LoadThreeLineGame(); }, 3.0f, false);
	}
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
				DragObj->lDragImage->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
	return false;
}

void UleeBaseLessions::lCreateNewChoises(TArray<FString> correctName, FGameLession& lession , FString AnswerDir, bool isSwap)
{
	//craete shape
	int count{};
	for (auto& p : lThreeline->lUserChoises) {

		p->ClearButtons();

		//get list Choise Swaped positions
		TArray<FString> shape = lSwapChoises(AnswerDir, correctName[count]);

		for (int i = 0; i < shape.Num();i++) {
			FString randPath = "/Game/" + AnswerDir + "/" + shape[i];
			//create buttons and binding Muticast DeleGate
			UleeDragWidget* btn = p->lCreateDragButton(randPath, true, true, "", count + 1);
			//bind delegate function
			btn->OniDrop.AddDynamic(this, &UleeBaseLessions::OnIDrop);
			lession.Topics[count].Choises.Add(randPath);
			btn->lSetShadowVisible(false);
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
	FGameLession  nlession = FGameLession();
	nlession.LessionType = Threelines;
	//register game id
	nlession.GameID = SessionID == 0 ? 1 : SessionID;
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
		if (lThreeline->lQuestions[i]->GetVisibility() != ESlateVisibility::Visible)
			lThreeline->lQuestions[i]->SetVisibility(ESlateVisibility::Visible);
		topic.ImagePath = iPath;
		nlession.Topics.Add(topic);
		nlession.TopicNames.Add(exceptions[i]);
	}
	//"AcademyAssets/Assets/ChoiseAnswers/AnimalShape"
	lCreateNewChoises(exceptions,nlession, choiseFolder,true);
	nlession.GameID = userdata->JsGames.Num() +1;
	gamedata = nlession;
	if(isReplay) isReplay = false;
	//GameIns->SaveCurrentGameData(userdata);
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

void UleeBaseLessions::OnIDrop(bool isCorrect)
{
	Droptimes++;
	DropCorrecttimes += isCorrect ? 1 : 0;
	lOnDropVisible = isCorrect;
	//add History Game List
	if (DropCorrecttimes == 3 && isCorrect) {
		//if (isReplay) return;
		FString completed;
		//convert to Json object string
		bool success=FJsonObjectConverter::UStructToJsonObjectString<FGameLession>(gamedata, completed, 0,0,0, nullptr, true);
		//convert to json object Shared Ptr
		TSharedPtr<FJsonObject> obj = FJsonObjectConverter::UStructToJsonObject<FGameLession>(gamedata);
		//add To History type Json Obj
		userdata->JsGames.Add(MakeShareable(new FJsonValueObject(obj)));
		//add to History type Struct
		//userdata->HistoryGames.Add(userdata->CurrentGame);
		
		//userdata->SaveConstruct();
		//Save game

		GameIns->SaveCurrentGameData(userdata);
		lSetWinOnOff(true);
		DropCorrecttimes = 0;

		//UE_LOG(LogTemp, Warning, TEXT("view : %s"), *completed);

	}
	lDebug(DropCorrecttimes);
}

void UleeBaseLessions::LoadThreeLineGame()
{

	//reload data load from Save Game;
	ReloadData();
	TEnumAsByte<lGameType> lastgame = userdata->GetLastGameType();
	FGameLession current = lastgame == Threelines ? DataLastGame : gamedata;
	isReplay = true;
	//load Questions and Player choise
	TArray<int32> ids = { 1,2,3 };
	TArray<FString> correctName = current.TopicNames;
	lThreeline->LoadQuestions(current.GetQuestions(), ids);
	lThreeline->LoadAllChoise(current);
	BindButtons();
	DropCorrecttimes = 0;
}

FReply UleeBaseLessions::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent)
{
	FReply iReply = Super::NativeOnTouchStarted(InGeometry, InTouchEvent);
	if (mouseFX) {
		lDebug("mouse FX clicked");
		UCanvasPanelSlot* mSlot = Cast<UCanvasPanelSlot>(mouseFX->Slot);
		if (mSlot) {
			FVector2D mPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
			mSlot->SetPosition(mPos);

			mouseFX->ActivateSystem(true);
		}
	}
	return iReply;
}

void UleeBaseLessions::BindButtons()
{
	for (auto &p : lThreeline->lUserChoises) {
		for (auto& b : p->lDragDropButtons)	{
			if (!b->OniDrop.IsBound())
				b->OniDrop.AddDynamic(this, &UleeBaseLessions::OnIDrop);

		}
	}
}

// Swap position Player Choise Shape
TArray<FString> UleeBaseLessions::lSwapChoises(FString AnswerDir, FString correctname)
{
	TArray<FString> shape{};
	FString path = FPaths::ProjectContentDir() + AnswerDir;
	//get all img in directory
		
	FString correctStr = FindContentFromPath(path, correctname);
	shape.AddUnique(correctStr);

	//get number diffirent files in directory ignore duplicate
	lGetRandFilesFromDirectory(path, shape, 3);
	for (int32 i = 0; i < shape.Num(); i++) {
		shape.SwapMemory(i, lRand(i, shape.Num()));
		UE_LOG(LogTemp,Warning,TEXT("view Swaper :%s"), *shape[i]);
	}
	return shape;
}

void UleeBaseLessions::ReloadData()
{
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameIns) { lDebug("Game Instance Nullptr"); }
	//load data
	GameIns->LoadGameData();
	userdata = GameIns->GameData;

	//case new game no data
	if (!userdata->GetLastGame().IsValid()) {
		lDebug("not Valid");
		return;
	}
	

	userdata->GetLastGameType();
	//init data to Struct
	TSharedPtr<FJsonValue> last = userdata->GetLastGame();
	FJsonObjectConverter::JsonObjectToUStruct(last->AsObject().ToSharedRef(), &DataLastGame, 0, 0);
	
	//previe Log Debug
	FString preview{};
	FJsonObjectConverter::UStructToJsonObjectString(DataLastGame, preview);
	UE_LOG(LogTemp, Warning, TEXT("load : %s"), *preview);
}

void UleeBaseLessions::NewGameThreelineInit()
{
	
	lThreeline->lTopicsAvalible();
	///generate new game random topic answer
	int gameid = GameIns->GameData->JsGames.Num();
	SessionID = gameid > 0 ? gameid : 1;
	FString Topics = lThreeline->lTopicSourceFolder;
	FString Choise = lThreeline->lChoiseSourceFolder;
	InitializeThreeLineopic(Topics, Choise);

}

void UleeBaseLessions::lSetWinOnOff(bool isOn) {
	ESlateVisibility vis = isOn ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden;
	return WinWidget->SetVisibility(vis);

}