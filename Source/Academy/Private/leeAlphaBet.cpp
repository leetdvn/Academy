// Fill out your copyright notice in the Description page of Project Settings.


#include "leeAlphaBet.h"

UleeAlphaBet::UleeAlphaBet(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UleeAlphaBet::OnHistoriesUp()
{
	//if (!GameHistories->isOpened) return;
	if (GameHistories) {
		GameHistories->OnOpenUp();
		GameHistories->CreateGameHistories(m_type);
		SetBlackSkyVisible(true);
	}
}

void UleeAlphaBet::OnReplay()
{
	isNewGame = false;
}

void UleeAlphaBet::NewGameInitialize()
{
	//WinPanelOnOff(false);
	//Alpha->lClearChecked();
	/*Init Data implantment*/
	c_Data.topicPath =  Alpha->CreateNewTopic();
	Alpha->CreateNewChoises();
	c_Data.ChoiseBgrs = Alpha->GetChoises();
	c_Data.topicNames = Alpha->GetTopicName();

	FString text = FText::FromStringTable(GAMETABLE, "AlphaDesc").ToString() +
		FText::FromStringTable(GAMETABLE, c_Data.topicNames).ToString();
	lDescription->SetText(FText::FromString(text));
	if (isMakeSound) {
		int32 soundIdx = GetSoundIndex();
		if (soundIdx > 0)
			UGameplayStatics::PlayDialogue2D(GetWorld(), Alpha->lWaveSound[soundIdx], Alpha->lContext[soundIdx]);
		isMakeSound = false;
	}
	//FText::FromStringTable(FName(*StrTable)
	//TArray<UleeBaseButton*> correctBtns = Alpha->GetCorrectButtons();
	OnBindAction();
	//iCorrectNum = 0;
}

void UleeAlphaBet::LoadGameFromData(int32 gameSession)
{
	/*Load Game Data from Game ID*/
	c_Data = GameIns->LoadAlphaGameAt(gameSession);
	FString Str{};
	FJsonObjectConverter::UStructToJsonObjectString(c_Data,Str);
	UE_LOG(LogTemp, Warning, TEXT("View : %s  index : %d"), *Str,gameSession);
	Alpha->SetTopicBrush(c_Data.topicPath);
	Alpha->SetChoiseBrush(c_Data.ChoiseBgrs);
	if (isMakeSound) {
		int32 soundIdx = GetSoundIndex();
		if (soundIdx > 0)
			UGameplayStatics::PlayDialogue2D(GetWorld(), Alpha->lWaveSound[soundIdx], Alpha->lContext[soundIdx]);
		isMakeSound = false;
	}
	OnBindAction();
	isNewGame = false;
	//Alpha->topicImg->SetBrushResourceObject(c_Data);
}

void UleeAlphaBet::OnCorrectClick(UleeBaseButton* button)
{
	/*do something when correct click*/
	iCorrectNum++;
	button->lSetChecked(true);
	button->lButton->SetIsEnabled(false);
	button->lActiveSmoke();
	UGameplayStatics::PlayDialogue2D(GetWorld(), Alpha->lWaveSound[1], Alpha->lContext[1]);

	if (iCorrectNum == 3) {

		if (isNewGame) {
			AlPhaData->DataHistories.Add(c_Data);
			//AlPhaData->CreateNewData(c_Data,true);
			GameIns->SaveAlpha(AlPhaData, true);
			GameIns->PlayerInfo->Star++;
			GameIns->PlayerInfo->BaseStar++;
			/*neet more vfx star*/
		}
		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, [this]() {
			WinPanelOnOff(true);
			iCorrectNum = 0;
			}, 3.0f, false, 0.5f);

	}
}

void UleeAlphaBet::OnWrongClicked(UleeBaseButton* button)
{
	UGameplayStatics::PlayDialogue2D(GetWorld(), Alpha->lWaveSound[0], Alpha->lContext[0]);

}

void UleeAlphaBet::OnNextClicked()
{
	WinPanelOnOff(false);
	Alpha->lClearChecked();
	Alpha->ClearAllBound();
	isNewGame = true;
	return NativeConstruct();
	lDebug("Coming Soon!!");
}

void UleeAlphaBet::SetBlackSkyVisible(bool isOn)
{
	ESlateVisibility vis = isOn ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	BlackSky->SetVisibility(vis);

}

void UleeAlphaBet::OnBlackSkyTouch()
{
	if (!GameHistories) return;
	if (GameHistories->isOpened) {
		GameHistories->OnCloseDown();
		SetBlackSkyVisible(false);
	}
}

void UleeAlphaBet::ToogleConfirmed(bool isOn, FString FeildMessage)
{
	ESlateVisibility vis = isOn ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	ConfirmPopup->SetVisibility(vis);
	ConfirmPopup->isOpen = isOn;

	if (FeildMessage.IsEmpty()) return;

	ConfirmPopup->lMessage->SetText(FText::FromStringTable(GAMETABLE, FeildMessage));

}

void UleeAlphaBet::OnUnlockDialog()
{
	//if (GameIns->PlayerInfo->Star < 5) return;
	ConfirmPopup->lMessage->SetText(FText::FromStringTable(GAMETABLE, "unlock"));
	ToogleConfirmed(true);
	ConfirmPopup->lButtonYes->OnClicked.Clear();
	ConfirmPopup->lButtonYes->OnClicked.AddDynamic(this, &UleeAlphaBet::OnPlayerGetWard);

}

void UleeAlphaBet::OnPlayerGetWard()
{
	/*Not Enoght Star*/
	if (GameIns->PlayerInfo->Star < 5) {
		lDebug("Not Enogh Star");
		ConfirmPopup->lMessage->SetText(FText::FromStringTable(GAMETABLE, "gotoshop"));
		ConfirmPopup->lButtonYes->OnClicked.Clear();
		ConfirmPopup->lButtonYes->OnClicked.AddDynamic(this, &UleeAlphaBet::OnGoToShop);
		return;
	}
	GameIns->PlayerInfo->Star -= 5;
	/*Go To Unlock close Dialog*/
	ToogleConfirmed(false);
	/*Turn off histories*/
	OnBlackSkyTouch();
	/*Create New Game and Save to Histories*/
	NewGameInitialize();

	AlPhaData->DataHistories.Add(c_Data);
	//AlPhaData->CreateNewData(c_Data,true);
	GameIns->SaveAlpha(AlPhaData,true);
}

void UleeAlphaBet::OnGoToShop()
{
	/*Go To Unlock close Dialog*/
	ToogleConfirmed(false);
	/*Turn off histories*/
	OnBlackSkyTouch();

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("AMenu"));

}

bool UleeAlphaBet::CheckTutorial()
{
	if (!GameIns->PlayerInfo->isFirstAlpha) {
		UleeUserInfo* info = GameIns->PlayerInfo;
		info->isFirstAlpha = true;
		GameIns->SaveUserInfo(info);
		return false;
	}
	return true;
}

int32 UleeAlphaBet::GetSoundIndex()
{
	int32 result=-1;
	if (c_Data.topicNames == "circle")
		result = 2;
	else if (c_Data.topicNames == "triangle")
		result = 3;
	else if (c_Data.topicNames == "heart")
		result = 4;
	else if (c_Data.topicNames == "rectangle")
		result = 5;
	else if (c_Data.topicNames == "hexagon")
		result = 6;

	return result;
}

void UleeAlphaBet::OnBindAction()
{
	TArray<UleeBaseButton*> buttons = Alpha->ChoiseButtons;
	if (buttons.Num() <= 0) return;
	for (auto& img : buttons) {
		img->OnCorrect.Clear();
		FString tName = img->lGetTextureName();
		FString topicN = c_Data.topicNames;
		if(tName.Left(topicN.Len()) == topicN)
			img->OnCorrect.AddDynamic(this, &UleeAlphaBet::OnCorrectClick);// .BindUFunction(this, TEXT("OnCorrectClick"));
		else {
			img->OnCorrect.AddDynamic(this, &UleeAlphaBet::OnWrongClicked);
		}
	}
}

void UleeAlphaBet::WinPanelOnOff(bool Onoff)
{
	isGameRuning = !Onoff;
	ESlateVisibility vis = Onoff ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden;
	return WinPanel->SetVisibility(vis);

}


void UleeAlphaBet::NativeConstruct()
{
	Super::NativeConstruct();
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	AlPhaData = GameIns->Alpha;
	/*generate decorations image*/
	WinPanelOnOff(false);
	topdecor->DecorInit(topdecor->lGetPath());
	botdecor->DecorInit(topdecor->lGetPath());
	iCorrectNum = 0;
	c_Data.GameID = AlPhaData->DataHistories.Num();
	
	/*bind BlackSky Touch*/
	BlackSky->OnMouseButtonDownEvent.BindUFunction(this, TEXT("OnBlackSkyTouch"));
	if (GameHistories) {
		GameHistories->lTurnOffButton->OnClicked.AddDynamic(this, &UleeAlphaBet::OnBlackSkyTouch);
		/*Star*/
		GameHistories->OnNewUnlock.AddDynamic(this, &UleeAlphaBet::OnUnlockDialog);
		if (ConfirmPopup) {
			ConfirmPopup->lButtonYes->OnClicked.AddDynamic(this, &UleeAlphaBet::OnPlayerGetWard);
			ConfirmPopup->lButtonNo->OnClicked.AddDynamic(this, &UleeAlphaBet::CloseDialog);
			//ConfirmPopup->
		}

	}
	isGameRuning = true;
	//isNewGame = true;
	return isNewGame ? NewGameInitialize() : LoadGameFromData(GameId);
}

