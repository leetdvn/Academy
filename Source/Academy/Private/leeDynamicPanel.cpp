// Fill out your copyright notice in the Description page of Project Settings.


#include "leeDynamicPanel.h"

void UThreeLines::lClearTopics()
{
	//if (lTopics.Num() == 0) return;

	//for (auto& tp : lTopics) {
	//	if (tp.lQuestion) {
	//		tp.lQuestion->ClearButtons();
	//	}
	//}
}

//TArray<UleeDragWidget*> UThreeLines::lCreateDragButtons(TArray<FString> ImagePaths, bool ImgOnly, bool isDrop, TArray<int32> IDs, TArray<FString> texts )
//{
//	TArray<UleeDragWidget*> btnsReults{};
//	if (lTopics.Num() == 0) return TArray<UleeDragWidget*>();
//
//	int count{};
//	for (auto& tp : lTopics) {
//		if (tp.lQuestion) {
//			UleeDragWidget* newButton = tp.lQuestion->lCreateDragButton(ImagePaths[count], ImgOnly, isDrop, texts[count], IDs[count]);
//			btnsReults.Add(newButton);
//		}
//		count++;
//	}
//
//	return btnsReults;
//}
