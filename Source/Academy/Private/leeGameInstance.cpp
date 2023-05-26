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
	lineEnvi = DataInitialize<UleeEnvironment>(ENVIRONMENT);
	//UE_LOG(LogTemp, Warning, TEXT("Data is Loaded : %s"), *GameData->GetAllGames());
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

void UleeGameInstance::AddStarValue(int32 addvalue)
{
	return PlayerInfo->AddStar(addvalue);
}

void UleeGameInstance::SaveLine3S(Ulee3LinesData*& lineData)
{
	UGameplayStatics::SaveGameToSlot(lineData, LINE3S ,0);
	//SavePreview<FGameLession>(Line3s->DataHistoriesStruct);

}

void UleeGameInstance::SaveLineEnvi(UleeEnvironment*& env)
{
	UGameplayStatics::SaveGameToSlot(env, ENVIRONMENT, 0);
	SavePreview<FGameLession>(env->DataHistoriesStruct);

}

void UleeGameInstance::SaveBox4S(Ulee4BoxData*& boxData)
{
	UGameplayStatics::SaveGameToSlot(boxData, BOX4S, 0);
	//SavePreview<FFourBoxData>(Box4s->DataHistoriesStruct);

}

void UleeGameInstance::SaveAlpha(UleeAlphaData*& alphaData,bool createjS)
{
	UGameplayStatics::SaveGameToSlot(alphaData, ALPHA, 0);
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

FGameLession UleeGameInstance::LoadEnvironmentGame(int32 idx)
{

	FGameLession result{};
	UE_LOG(LogTemp, Warning, TEXT("Index : %d Idx 2 : %d"), idx, Line3s->DataHistoriesStruct.Num());
	if (idx < 0)
		return FGameLession();
	result = lineEnvi->GetLinesAt(idx);
	return result;
}

FAlphaBetData UleeGameInstance::LoadAlphaGameAt(int32 idx)
{
	return idx < 0 ? FAlphaBetData() : Alpha->GetLinesAt(idx);
}


