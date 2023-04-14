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
		if (!GameHistories->isOpened)
			GameHistories->OnOpenUp();
		else
			GameHistories->OnCloseDown();
	}
	GameHistories->CreateGameHistories(m_type);
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

	if (iCorrectNum == 3) {
		WinPanelOnOff(true);
		iCorrectNum = 0;

		if (isNewGame) {
			AlPhaData->DataHistories.Add(c_Data);
			//AlPhaData->CreateNewData(c_Data,true);
			GameIns->SaveAlpha(AlPhaData, true);
		}
	}
	UGameplayStatics::PlayDialogue2D(GetWorld(), Alpha->lWaveSound[1], Alpha->lContext[1]);

	lDebug(iCorrectNum);
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
	ESlateVisibility vis = Onoff ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden;
	return WinPanel->SetVisibility(vis);

}


void UleeAlphaBet::NativeConstruct()
{
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	AlPhaData = GameIns->Alpha;
	/*generate decorations image*/
	WinPanelOnOff(false);
	topdecor->DecorInit(topdecor->lGetPath());
	botdecor->DecorInit(topdecor->lGetPath());
	iCorrectNum = 0;
	c_Data.GameID = AlPhaData->DataHistories.Num();
	
	//isNewGame = true;
	return isNewGame ? NewGameInitialize() : LoadGameFromData(GameId);
}

