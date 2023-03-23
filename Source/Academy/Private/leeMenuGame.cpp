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

void UleeMenuGame::OnParentClicked()
{
	if (!Settings->isAvalible) 
		Settings->OnOpenUp();
}

//void UleeMenuGame::OnSelectChanged(FString itemname, ESelectInfo::Type SelectionType)
//{
//	if (itemname.IsEmpty()) return;
//	FString culture = itemname == "English" ? "culture=en" : "culture=vi";
//	lDebug("changed");
//	lDebug(culture);
//
//	int32 idx = box->GetSelectedIndex();
//	box->SetSelectedIndex(idx);
//	//if(itemname == "English")
//	UKismetInternationalizationLibrary::SetCurrentCulture(culture);
//	//else
//	UKismetInternationalizationLibrary::SetCurrentLanguage(culture, true);
//	UKismetInternationalizationLibrary::SetCurrentLocale(culture, true);
//	GEngine->Exec(GetWorld(), TEXT("-culture=vi"));
//	//GEngine->Exec(GetWorld(), TEXT("stat Game"));
//
//}

void UleeMenuGame::NativeConstruct()
{
	if (GameMenu) {
		if (GameMenu->lGetButtons().Num() > 0) {
			for (auto& btn : GameMenu->lGetButtons()) 
				btn->OnMenuClick.AddDynamic(this, &UleeMenuGame::OnMenuClick);
		}
	}

	FString map=UGameplayStatics::GetCurrentLevelName(GetWorld());
	lParentsButton->OnClicked.AddDynamic(this, &UleeMenuGame::OnParentClicked);
	//lDebug(map);

	//box->OnSelectionChanged.AddDynamic(this, &UleeMenuGame::OnSelectChanged);
	//for (auto& m : lGetAllMapNames())
	//	lDebug(m);
}
