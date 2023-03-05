// Fill out your copyright notice in the Description page of Project Settings.


#include "leeMenuGame.h"

void UleeMenuGame::OnMenuClick(FString menuName)
{
	if (menuName.IsEmpty()) return;
	lDebug(menuName);
	if (menuName.EndsWith("count") || menuName.EndsWith("numbers")) {
		mapOpen = "ThreeLines";
	}
	else if (menuName.StartsWith("match") || menuName.StartsWith("shape"))
		mapOpen = "FourBox";

	if (mapOpen.IsEmpty()) return;

	UGameplayStatics::OpenLevel(GetWorld(),FName(*mapOpen));
}

void UleeMenuGame::NativeConstruct()
{
	if (GameMenu) {
		if (GameMenu->lGetButtons().Num() > 0) {
			for (auto& btn : GameMenu->lGetButtons()) 
				btn->OnMenuClick.AddDynamic(this, &UleeMenuGame::OnMenuClick);
		}
	}

	FString map=UGameplayStatics::GetCurrentLevelName(GetWorld());
	//lDebug(map);

	for (auto& m : lGetAllMapNames())
		lDebug(m);
}
