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
	/*Init Data implantment*/
	c_Data.topicPath =  Alpha->CreateNewTopic();
	Alpha->CreateNewChoises();
	c_Data.ChoiseBgrs = Alpha->GetChoises();
}

void UleeAlphaBet::LoadGameFromData(int32 gameId)
{
	/*Load Game Data from Game ID*/
}

void UleeAlphaBet::OnCorrectClick()
{
	/*do something when correct click*/

}

void UleeAlphaBet::NativeConstruct()
{
	/*generate decorations image*/
	topdecor->DecorInit(topdecor->lGetPath());
	botdecor->DecorInit(topdecor->lGetPath());

	NewGameInitialize();
}

FString UleeAlpha::CreateNewTopic()
{
	topicName = lGetRandFileFromDirectory(FPaths::ProjectContentDir() + ALPHADEFAULT);
	FString imgPath = FString("/Game/") + ALPHADEFAULT + topicName;
	lDebug(imgPath);
	UTexture2D* tex = lGetTextureFromPath(imgPath);
	if (!tex) {
		lDebug("Path Does not Exists ");
		lDebug(imgPath);
		return FString();
	}
	topicImg->SetBrushFromTexture(tex, true);
	return imgPath;
}

TArray<FString> UleeAlpha::GeneratorChoises()
{
	TArray<FString> result{};
	FString basePath = FPaths::ProjectContentDir() + ALPHACHOISES;
	TArray<int32> nums{};
	lGetRandNums(nums, 3, 7);

	FString choise{};
	for (int i = 0; i < nums.Num(); i++) {
		choise = topicName + FString::FromInt(nums[i]);
		FString file = FPaths::ProjectContentDir() + ALPHADEFAULT + "/" + choise;
		//if(lFilesExists(file))
		result.AddUnique(choise);
	}
	lGetRandFilesFromDirectory(basePath, result, 6,topicName);

#pragma omp parallel for
	for (int i = 0; i < result.Num(); i++)
		if(i <= result.Num()/2)
			result.SwapMemory(i, lRand(i + 1, result.Num()));
		
	return result;
}

void UleeAlpha::CreateNewChoises()
{
	TArray<FString> choiseName = GeneratorChoises();
	if (choiseName.Num() <= 0 && choiseName.Num() != ChoisePanels.Num()) return;
	int count{};
	for (auto& iname : choiseName) {
		FString path = FString("/Game/") + ALPHACHOISES + iname;
		choisePath.Add(path);
		UTexture2D* tex = lGetTextureFromPath(path);
		//if (!tex) continue;
		ChoisePanels[count]->SetBrushFromTexture(tex,true);
		count++;
	}
}
