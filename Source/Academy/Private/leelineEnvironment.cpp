#include "leelineEnvironment.h"


//UleelineEnvironment::UleelineEnvironment(const FObjectInitializer& ObjectInitializer)
//	:Super(ObjectInitializer)
//{
//
//}

void UleelineEnvironment::OnIDrop(bool isCorrect)
{
	Droptimes++;
	DropCorrecttimes += isCorrect ? 1 : 0;
	lOnDropVisible = isCorrect;

	int32 waveIdx = !isCorrect ? 0 : 1;

	//add History Game List
	if (DropCorrecttimes == 3 && isCorrect) {
		if (isNewGame) {
			lineEnvi->DataHistoriesStruct.Add(gamedata);
			UleeUserInfo* udata = GameIns->PlayerInfo;
			udata->AddStar(1);
			GameIns->SaveUserInfo(udata);

			bool canSave{};
			if (udata->isPurChased())
				canSave = true;
			else if (!udata->isPurChased() && line3S->DataHistoriesStruct.Num() <= 20)
				canSave = true;

			if (canSave) {
				GameIns->SaveLineEnvi(lineEnvi);
			}
		}
		/*neet more vfx star*/

		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, [this]() {	lSetWinOnOff(true); }, 3.0f, false, 0.5f);

		DropCorrecttimes = 0;
		/*Check Ads Runing*/
		AleeSmartCharacter2D* character = IGetChacter<AleeSmartCharacter2D>(GetWorld());
		if (character) {
			character->CompletedGameCount++;
		}

	}
	UGameplayStatics::PlayDialogue2D(GetWorld(), lThreeline->lWaveSound[waveIdx], lThreeline->lContext[waveIdx]);

}

void UleelineEnvironment::NewGameThreelineInit()
{

	isGameRuning = true;
	lThreeline->lTopicsAvalible();
	///generate new game random topic answer
	int gameid = lineEnvi->DataHistoriesStruct.Num();
	SessionID = gameid > 0 ? gameid : 1;
	//FString Topics = !isPremiumUser ?
	//	lThreeline->lTopicSourceFolder :
	//	"AcademyAssets/Assets/Topic/Premium_Animal";
	//FString Choise = !isPremiumUser ?
	//	lThreeline->lChoiseSourceFolder :
	//	"AcademyAssets/Assets/ChoiseAnswers/PremiumShape";

	FString Topics = lGetTopicMatchingPath(Mode);
	FString Choise = lGetTopicMatchingPath(Mode, true);
	InitializeThreeLineopic(Topics, Choise,lineEnvi->DataHistoriesStruct.Num());

}

void UleelineEnvironment::OnPlayerGetWard()
{

	if (!GameIns->PlayerInfo->isPurChased() ){
		if (lineEnvi->DataHistoriesStruct.Num() >= 20) {
			ConfirmPopup->lMessage->SetText(FText::FromStringTable(SETTINGTABLE, "reuiquiredP"));
			ConfirmPopup->lButtonYes->OnClicked.Clear();
			ConfirmPopup->lButtonYes->OnClicked.AddDynamic(this, &UleeBaseLessions::OnGoToShop);
			return;
		}
	}
	/*Not Enoght Star*/
	if (GameIns->PlayerInfo->Star < 5) {
		lDebug("Not Enogh Star");
		ConfirmPopup->lMessage->SetText(FText::FromStringTable(GAMETABLE, "gotoshop"));
		ConfirmPopup->lButtonYes->OnClicked.Clear();
		ConfirmPopup->lButtonYes->OnClicked.AddDynamic(this, &UleeBaseLessions::OnGoToShop);
		return;
	}

	GameIns->PlayerInfo->Star -= 5;
	/*Go To Unlock close Dialog*/
	ToogleConfirmed(false);
	/*Turn off histories*/
	OnBlackSkyTouch();
	/*Create New Game and Save to Histories*/
	NewGameThreelineInit();
	lineEnvi->DataHistoriesStruct.Add(gamedata);
	GameIns->SaveLineEnvi(lineEnvi);

}

void UleelineEnvironment::LoadGameAt(int32 sessionGameID)
{
	//reload data load from Save Gam
	lDebug(sessionGameID);
	FGameLession newlession = GameIns->LoadEnvironmentGame(sessionGameID);
	FString Str{};
	FJsonObjectConverter::UStructToJsonObjectString(newlession, Str);
	UE_LOG(LogTemp, Warning, TEXT(" check lessiong %d :  %s"), sessionGameID, *Str);

	//TSharedPtr<FJsonValue> session= _UserData->GetGamesAt(sessionGameID);
	//FGameLession* lession = new FGameLession();
	//FJsonObjectConverter::JsonObjectToUStruct(session->AsObject().ToSharedRef(), lession);
	//FString jsStr = lJsontoStr(session->AsObject());

	TArray<int32> ids = { 1,2,3 };
	TArray<FString> correctName = newlession.TopicNames;
	lThreeline->LoadQuestions(newlession.GetQuestions(), ids);
	lThreeline->LoadAllChoise(newlession);
	BindButtons();
	DropCorrecttimes = 0;
	lSetWinOnOff(false);
}

void UleelineEnvironment::NativeConstruct()
{
	//Super::NativeConstruct();

	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	lineEnvi = GameIns->lineEnvi;
	ltopdecor->DecorInit(ltopdecor->lGetPath());
	lbottomdecor->DecorInit(ltopdecor->lGetPath());


	lThreeline->lTopicSourceFolder = lGetTopicMatchingPath(Mode);
	lThreeline->lChoiseSourceFolder = lGetTopicMatchingPath(Mode, true);
	//binding event drop for answers
	/*bind BlackSky Touch*/
	BlackSky->OnMouseButtonDownEvent.BindUFunction(this, TEXT("OnBlackSkyTouch"));
	if (GameHistories) {
		GameHistories->lTurnOffButton->OnClicked.AddDynamic(this, &UleeBaseLessions::OnBlackSkyTouch);

		/*Star*/
		GameHistories->OnNewUnlock.AddDynamic(this, &UleeBaseLessions::OnUnlockDialog);
		if (ConfirmPopup) {
			ConfirmPopup->lButtonYes->OnClicked.AddDynamic(this, &UleeBaseLessions::OnPlayerGetWard);
			ConfirmPopup->lButtonNo->OnClicked.AddDynamic(this, &UleeBaseLessions::CloseDialog);
			//ConfirmPopup->
		}

	}

	//load Game History
	lSetWinOnOff(false);

	if (lThreeline->GameHistoriesButton) {
		lThreeline->GameHistoriesButton->OnClicked.AddDynamic(this, &UleeBaseLessions::OnHistoriesUp);
	}

	UGameplayStatics::PlayDialogue2D(GetWorld(), lThreeline->lWaveSound[3], lThreeline->lContext[3]);
	isMakeSound = false;

	/*bind Confirm Popup*/
	isGameRuning = true;
	return isNewGame ? NewGameThreelineInit() : LoadGameAt(SessionID);
}

void UleelineEnvironment::NativeDestruct()
{
	GameHistories->lTurnOffButton->OnClicked.Clear();
	GameHistories->OnNewUnlock.Clear();
	ConfirmPopup->lButtonNo->OnClicked.Clear();
	ConfirmPopup->lButtonYes->OnClicked.Clear();
}
