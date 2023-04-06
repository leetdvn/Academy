// Fill out your copyright notice in the Description page of Project Settings.


#include "leeGameInstance.h"

void UleeGameInstance::Init()
{
	SlotGame = "leeGameData";
	SlotInfo = "PlayerInfo";

	lDebug("Count ");
	Line3s= DataInitialize<Ulee3LinesData>(LINE3S);
	Box4s= DataInitialize<Ulee4BoxData>(BOX4S);
	PlayerInfo= DataInitialize< UleeUserInfo>(USERINFO);
	Alpha = DataInitialize<UleeAlphaData>(ALPHA);
	//UE_LOG(LogTemp, Warning, TEXT("Data is Loaded : %s"), *GameData->GetAllGames());
}

void UleeGameInstance::SaveCurrentGameData(UPlayerData*& data)
{
	if (!GameData) { return; }

	FString fileAbc = FString(FPaths::ProjectSavedDir() + "SaveGames/ACademyPreview.json");
	FString outStr;
	//Construct Data
	data->SaveConstruct();
	UGameplayStatics::DeleteGameInSlot(SlotGame, 0);
	UGameplayStatics::SaveGameToSlot(data, SlotGame, 0);
}

void UleeGameInstance::SaveUserInfo(UleeUserInfo*& info)
{

	UGameplayStatics::SaveGameToSlot(info, SlotInfo, 0);

}

void UleeGameInstance::SaveGameData(TEnumAsByte<lGameType> gtype)
{
	switch (gtype)
	{
	case None:
		break;
	case Threelines:
		break;
	case FourBox:
		break;
	case AlphaBet:
		break;
	}
}

void UleeGameInstance::SaveLine3S(Ulee3LinesData*& lineData)
{
	UGameplayStatics::SaveGameToSlot(lineData, LINE3S ,0);

}

void UleeGameInstance::SaveBox4S(Ulee4BoxData*& boxData)
{
	UGameplayStatics::SaveGameToSlot(boxData, BOX4S, 0);

}

void UleeGameInstance::Save3LinesGame(FGameLession& data)
{
}

FGameLession UleeGameInstance::Load3LinesGame(int32 idx)
{
	//Line3s = DataInitialize<Ulee3LinesData>(LINE3S);

	FGameLession result{};
	UE_LOG(LogTemp, Warning, TEXT("Index : %d Idx 2 : %d"), idx,Line3s->DataHistoriesStruct.Num());
	if(idx <0)
		return FGameLession();
	result = Line3s->GetLinesAt(idx);
	return result;
}



