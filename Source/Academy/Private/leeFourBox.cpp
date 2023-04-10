#include "leeFourBox.h"
#include "Kismet/KismetStringLibrary.h"

void UleeFourBox::NewFourBoxInit()
{
	ReloadData();
	fourdata.GameID = GameIns->Box4s->DataHistoriesStruct.Num();
	fourdata.LessionType = m_type;
	fourdata.GameTitle = "BoxTitle";
	fourdata.GameDescriptions = "BoxDesc";
	fourdata.GameDecorPath = "";
	
	//LoadGameAt(userdata->JsGames.Num()-1);
	lFourBox->CreateGenerator(fourdata);
	BindAction();
}

void UleeFourBox::LoadGameAt(int32 dataIndex)
{
	//dont' need reload neet make choise new avaible
	//lDebug("On Replay", FColor::Purple, " ");
	if (dataIndex < 0) {
		lDebug("Error");
		return;
	}
	//return;
	//isReplay = true;
	//============================Read Data from Game Instance =========================================
	//TSharedPtr<FJsonValue> jsVal= userdata->GetGamesAt(dataIndex);
	FFourBoxData nData = GameIns->Box4s->DataHistoriesStruct[dataIndex];
	FString prev{};
	FJsonObjectConverter::UStructToJsonObjectString(nData,prev);
	UE_LOG(LogTemp, Warning, TEXT("4S : %s"), *prev);
	//------------------------------------------------------------------------

	//==================load call data
	if (nData.topicPaths.Num() > 0) {
		int i = 0; int x = 0;
		lFourBox->lSetQuestions(nData.topicPaths);

		for (auto& p : lFourBox->lQuestions) {
			//paint color panel
			lFourBox->lSetChoiseBgr(i, nData.ChoiseBgrs[i],false);
			//lFourBox->lUserChoises[i]->lSetMakeSameAt(nData->ChoiseBgrs[i],false);
			TArray<FString> nums{};
			for (auto& b : lFourBox->lUserChoises[i]->lGetButtons())
			{
				//if(idx < nData->textsChoiss.Num())
				nums.Add(nData.textsChoiss[x]);
				x++;
			}

			lFourBox->lSetChoiseTextAt(i, nums);
			i++;
		}
		lFourBox->lClearActionBound();
		lFourBox->lClearChecked();

	}
	BindAction();

}

void UleeFourBox::OnCorrectAnswer(UleeBaseButton* button)
{
	if (AnswerCorrect > 4) return;
	AnswerCorrect++;
	
	lFourBox->lUserChoises[button->Id]->lSetDisable(true);
	if (button) {
		button->lSetChecked(true);
		UGameplayStatics::PlayDialogue2D(GetWorld(), lFourBox->lWaveSound[1], lFourBox->lContext[1]);
	}
	if (AnswerCorrect == 4) {
		/// save data pass to next game lession
		box4S->DataHistoriesStruct.Add(fourdata);
		GameIns->SaveBox4S(box4S);
		WinWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	//debug
}

void UleeFourBox::OnUnCorrectAnswer()
{
	UGameplayStatics::PlayDialogue2D(GetWorld(), lFourBox->lWaveSound[0], lFourBox->lContext[0]);

}

void UleeFourBox::OnIdReCeiveClick()
{
	//lDebug(idsent);
}

void UleeFourBox::OnHistoriesUp()
{
	if (GameHistories) GameHistories->OnOpenUp();	
	GameHistories->CreateGameHistories(m_type);
}

void UleeFourBox::BindAction()
{
	TArray<UleeBaseButton*> buttons{};
	lFourBox->lGetCorrectButtons(buttons);
	for (auto& b : buttons) {
		b->OnCorrect.AddDynamic(this, &UleeFourBox::OnCorrectAnswer);
	}

	for (auto& wb : lFourBox->UnCorrectButtons) {
		wb->lButton->OnClicked.AddDynamic(this, &UleeFourBox::OnUnCorrectAnswer);
	}
}

void UleeFourBox::lSetWinOnOff(bool isOn)
{
	ESlateVisibility vis = isOn ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden;
	return WinWidget->SetVisibility(vis);

}

void UleeFourBox::OnStarUp(int32 valueUp)
{
	if (valueUp <= 0) return;
	//userdata->Star += valueUp;
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
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	box4S = GameIns->Box4s;

	if (lFourBox->GameHistoriesButton) {
		lFourBox->GameHistoriesButton->OnClicked.AddDynamic(this, &UleeFourBox::OnHistoriesUp);
	}
	//GameHistories->OnHistoriesInit(userdata);
	WinWidget->SetVisibility(ESlateVisibility::Hidden);
	return isNewGame ? NewFourBoxInit() : LoadGameAt(GameId);
	//lGetTopicCaculateAt(1);
}

void UleeFourBox::ReloadData()
{
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameIns) { lDebug("Game Instance Nullptr"); return; }
	//load data
	//fourdata = GameIns->Box4s;
	//UE_LOG(LogTemp, Warning, TEXT("load Data : %s"), *userdata->GetAllGames());
}