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
}

void UleeAlphaBet::NewGameInitialize()
{
	//WinPanelOnOff(false);
	//Alpha->lClearChecked();
	/*Init Data implantment*/
	c_Data.topicPath =  Alpha->CreateNewTopic();
	Alpha->CreateNewChoises();
	c_Data.ChoiseBgrs = Alpha->GetChoises();
	OnBindAction();
	//iCorrectNum = 0;
}

void UleeAlphaBet::LoadGameFromData(int32 gameSession)
{
	/*Load Game Data from Game ID*/

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
		AlPhaData->DataHistories.Add(c_Data);
		//AlPhaData->CreateNewData(c_Data,true);
		GameIns->SaveAlpha(AlPhaData,true);
	}
	lDebug(iCorrectNum);
}

void UleeAlphaBet::OnNextClicked()
{
	WinPanelOnOff(false);
	Alpha->lClearChecked();
	Alpha->ClearAllBound();
	return NativeConstruct();
	lDebug("Coming Soon!!");
}

void UleeAlphaBet::OnBindAction(bool isUnbind)
{
	if (Alpha->CorrectButtons.Num() <= 0) return;
	for (auto& img : Alpha->CorrectButtons) {
		img->OnCorrect.Clear();
		img->OnCorrect.AddDynamic(this, &UleeAlphaBet::OnCorrectClick);// .BindUFunction(this, TEXT("OnCorrectClick"));
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
	
	isNewGame = true;
	return isNewGame ? NewGameInitialize() : LoadGameFromData(GameId);
}

