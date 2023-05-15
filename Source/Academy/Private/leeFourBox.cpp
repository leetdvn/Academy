#include "leeFourBox.h"
#include "Kismet/KismetStringLibrary.h"
#include <leeSmartCharacter2D.h>

void UleeFourBox::NewFourBoxInit()
{
	ltopdecor->DecorInit(ltopdecor->lGetPath());
	lbottomdecor->DecorInit(ltopdecor->lGetPath());

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
	lDebug(button->Id);
	if (button) {
		button->lSetChecked(true);
		UGameplayStatics::PlayDialogue2D(GetWorld(), lFourBox->lWaveSound[1], lFourBox->lContext[1]);
	}
	if (AnswerCorrect == 4) {
		/// save data pass to next game lession
		box4S->DataHistoriesStruct.Add(fourdata);

		if (isNewGame) {
			
			UleeUserInfo* udata = GameIns->PlayerInfo;
			udata->AddStar(1);
			GameIns->SaveUserInfo(udata);
			GameIns->SaveBox4S(box4S);
		}
		AleeSmartCharacter2D* character = IGetChacter<AleeSmartCharacter2D>(GetWorld());
		if (character) {
			character->CompletedGameCount++;
		}
		/*neet more vfx star*/

		WinWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		isGameRuning = false;
	}
	button->lActiveSmoke();
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
	if (!GameHistories) return;

	GameHistories->OnOpenUp();
	GameHistories->CreateGameHistories(m_type);
	SetBlackSkyVisible(true);
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

void UleeFourBox::SetBlackSkyVisible(bool isOn)
{
	ESlateVisibility vis = isOn ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	BlackSky->SetVisibility(vis);
}

void UleeFourBox::OnBlackSkyTouch()
{
	if (!GameHistories) return;

	if (GameHistories->isOpened) {
		GameHistories->OnCloseDown();
		SetBlackSkyVisible(false);
	}
}

bool UleeFourBox::isFirebaseLogins()
{
	if (!GameIns) {
		GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}

	FString UID = GameIns->PlayerInfo->lGetUID();

	return  UID != "" ? true : false;
}

bool UleeFourBox::CheckTutorial()
{
	if (!GameIns->PlayerInfo->isFirstBox) {
		UleeUserInfo* info = GameIns->PlayerInfo;
		info->isFirstBox = true;
		GameIns->SaveUserInfo(info);
		return false;
	}
	return true;
}

void UleeFourBox::ToogleConfirmed(bool isOn, FString FeildMessage)
{
	ESlateVisibility vis = isOn ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	ConfirmPopup->SetVisibility(vis);
	ConfirmPopup->isOpen = isOn;
	if (FeildMessage.IsEmpty()) return;

	ConfirmPopup->lMessage->SetText(FText::FromStringTable(GAMETABLE, FeildMessage));

}

void UleeFourBox::OnUnlockDialog()
{
	//if (GameIns->PlayerInfo->Star < 5) return;
	ConfirmPopup->lMessage->SetText(FText::FromStringTable(GAMETABLE, "unlock"));
	ToogleConfirmed(true);
	ConfirmPopup->lButtonYes->OnClicked.Clear();
	ConfirmPopup->lButtonYes->OnClicked.AddDynamic(this, &UleeFourBox::OnPlayerGetWard);

}

void UleeFourBox::OnPlayerGetWard()
{
	/*Not Enoght Star*/
	if (GameIns->PlayerInfo->Star < 5) {
		lDebug("Not Enogh Star");
		ConfirmPopup->lMessage->SetText(FText::FromStringTable(GAMETABLE, "gotoshop"));
		ConfirmPopup->lButtonYes->OnClicked.Clear();
		ConfirmPopup->lButtonYes->OnClicked.AddDynamic(this, &UleeFourBox::OnGoToShop);
		return;
	}

	GameIns->PlayerInfo->Star -= 5;
	/*Go To Unlock close Dialog*/
	ToogleConfirmed(false);
	/*Turn off histories*/
	OnBlackSkyTouch();
	/*Create New Game and Save to Histories*/
	NewFourBoxInit();

	box4S->DataHistoriesStruct.Add(fourdata);
	GameIns->SaveBox4S(box4S);

}

void UleeFourBox::OnGoToShop()
{
	/*Go To Unlock close Dialog*/
	ToogleConfirmed(false);
	/*Turn off histories*/
	OnBlackSkyTouch();

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("AMenu"));

}

bool UleeFourBox::CheckIsAntiAds()
{
	if (!GameIns)
		GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	return GameIns->PlayerInfo->isAntiAds();

}

void UleeFourBox::OnRePlayGame()
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
	Super::NativeConstruct();
	//UUserWidget* widget = Cast<UUserWidget>(this);
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	box4S = GameIns->Box4s;

	/*bind BlackSky Touch*/
	BlackSky->OnMouseButtonDownEvent.BindUFunction(this, TEXT("OnBlackSkyTouch"));
	if (GameHistories)
	{
		GameHistories->lTurnOffButton->OnClicked.AddDynamic(this, &UleeFourBox::OnBlackSkyTouch);
		/*Star*/
		GameHistories->OnNewUnlock.AddDynamic(this, &UleeFourBox::OnUnlockDialog);
		if (ConfirmPopup) {
			ConfirmPopup->lButtonYes->OnClicked.AddDynamic(this, &UleeFourBox::OnPlayerGetWard);
			ConfirmPopup->lButtonNo->OnClicked.AddDynamic(this, &UleeFourBox::CloseDialog);
			//ConfirmPopup->
		}

	}

	if (lFourBox->GameHistoriesButton) {
		lFourBox->GameHistoriesButton->OnClicked.AddDynamic(this, &UleeFourBox::OnHistoriesUp);
	}
	//GameHistories->OnHistoriesInit(userdata);
	WinWidget->SetVisibility(ESlateVisibility::Hidden);
	if (isMakeSound) {
		UGameplayStatics::PlayDialogue2D(GetWorld(), lFourBox->lWaveSound[2], lFourBox->lContext[2]);
		isMakeSound = false;
	}
	isGameRuning = true;
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