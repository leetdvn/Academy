#include "leeFourBox.h"
#include "Kismet/KismetStringLibrary.h"

void UleeFourBox::NewFourBoxInit()
{
	fourdata.LessionType = FourBox;
	fourdata.GameID = userdata->JsGames.Num() + 1;
	fourdata.GameTitle = ltitle->GetText().ToString();
	fourdata.GameDescriptions = lDescription->GetText().ToString();
	fourdata.GameDecorPath = "";
	
	//LoadGameAt(userdata->JsGames.Num()-1);
	lFourBox->CreateGenerator(fourdata);
	BindAction();
}

void UleeFourBox::LoadGameAt(int32 dataIndex)
{
	//dont' need reload neet make choise new avaible
	//lDebug("On Replay", FColor::Purple, " ");
	if (dataIndex < 0 || dataIndex > userdata->JsGames.Num() - 1) {
		lDebug("Error");
		return;
	}

	isReplay = true;
	//============================Read Data from Game Instance =========================================
	TSharedPtr<FJsonValue> jsVal= userdata->GetGamesAt(dataIndex);
	FFourBoxData* nData=new FFourBoxData();
	FJsonObjectConverter::JsonObjectToUStruct(jsVal->AsObject().ToSharedRef(), nData);
	//------------------------------------------------------------------------

	//==================load call data
	if (nData->topicPaths.Num() > 0) {
		int i = 0; int x = 0;
		lFourBox->lSetQuestions(nData->topicPaths);

		for (auto& p : lFourBox->lQuestions) {
			//paint color panel
			lFourBox->lSetChoiseBgr(i, nData->ChoiseBgrs[i],false);
			//lFourBox->lUserChoises[i]->lSetMakeSameAt(nData->ChoiseBgrs[i],false);
			TArray<FString> nums{};
			for (auto& b : lFourBox->lUserChoises[i]->lGetButtons())
			{
				//if(idx < nData->textsChoiss.Num())
				nums.Add(nData->textsChoiss[x]);
				x++;
			}

			lFourBox->lSetChoiseTextAt(i, nums);
			i++;
		}
		lFourBox->lClearActionBound();
		lFourBox->lClearChecked();

		BindAction();
		
		//OnRePlayGame(fourdata);
		//-----------------------------------------------------------------
	}

}

void UleeFourBox::OnCorrectAnswer(UleeBaseButton* button)
{
	if (AnswerCorrect > 4) return;
	AnswerCorrect++;
	
	lFourBox->lUserChoises[button->Id]->lSetDisable(true);
	if (button) {
		button->lSetChecked(true);

	}
	if (AnswerCorrect == 4) {
		/// save data pass to next game lession
		if(!isReplay)
			OnSaveData();
		WinWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	//debug
}

void UleeFourBox::OnIdReCeiveClick()
{
	//lDebug(idsent);
}

void UleeFourBox::BindAction()
{
	TArray<UleeBaseButton*> buttons{};
	lFourBox->lGetCorrectButtons(buttons);
	for (auto& b : buttons) {
		b->OnCorrect.AddDynamic(this, &UleeFourBox::OnCorrectAnswer);
	}
}

void UleeFourBox::lSetWinOnOff(bool isOn)
{
	ESlateVisibility vis = isOn ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden;
	return WinWidget->SetVisibility(vis);

}

void UleeFourBox::OnRePlayGame(FFourBoxData& odata)
{
	for (auto& p : lFourBox->lUserChoises) {
		p->lSetDisable(false);
		for (auto& b : p->lGetButtons())
			if (b->lGetChecked()) b->lSetChecked(false);
	}
	AnswerCorrect = 0;
}

void UleeFourBox::NativeConstruct()
{
	//UUserWidget* widget = Cast<UUserWidget>(this);

	ReloadData();
	//lDebug("two");

	if (lFourBox->GameHistoriesButton) {
		lFourBox->GameHistoriesButton->OnClicked.AddDynamic(this, &UleeFourBox::OnHistoriesUp);
	}
	GameHistories->OnHistoriesInit(userdata);
	WinWidget->SetVisibility(ESlateVisibility::Hidden);
	return isNewGame ? NewFourBoxInit() : LoadGameAt(userdata->JsGames.Num()-1);
	//lGetTopicCaculateAt(1);
}

void UleeFourBox::ReloadData()
{
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameIns) { lDebug("Game Instance Nullptr"); }
	//load data
	GameIns->LoadGameData();
	userdata = GameIns->GameData;
	//UE_LOG(LogTemp, Warning, TEXT("load Data : %s"), *userdata->GetAllGames());
}

void UleeFourBox::OnSaveData()
{
	ReloadData();
	TSharedPtr<FJsonObject> game = FJsonObjectConverter::UStructToJsonObject<FFourBoxData>(fourdata, 0, 0);
	userdata->JsGames.Add(MakeShareable(new FJsonValueObject(game)));

	//save
	if (GameIns)
		GameIns->SaveCurrentGameData(userdata);
}
