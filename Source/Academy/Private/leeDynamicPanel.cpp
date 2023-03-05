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

TArray<FGameTopics> UThreeLines::LoadQuestions(TArray<FString> paths, TArray<int32> ids)
{
	if (paths.Num() == 0 || ids.Num() <= 0 || paths.Num() != ids.Num()) return TArray<FGameTopics>();
	TArray<FGameTopics> topics;
	int count{};
	for (auto& q : lQuestions) {
		if (q->GetVisibility() == ESlateVisibility::Hidden)
			q->SetVisibility(ESlateVisibility::Visible);
		FGameTopics topic{};
		q->lSetTexture(paths[count]);
		q->lSetId(ids[count]);
		topic.ImagePath = paths[count];
		topics.Add(topic);
		count++;
	}
	return topics;
}

TArray<UleeDragWidget*> UThreeLines::LoadChoisesAt(TArray<FString> paths,int32 ids, int32 idx)
{
	if (paths.Num() <= 0 || idx <0 && idx > lUserChoises.Num() ) {
		lDebug("Array zero");
		return TArray<UleeDragWidget*>();
	}

	TArray<UleeDragWidget*> btns = lUserChoises[idx]->lGetDragDropButtons();

	for (int i = 0; i < paths.Num(); i++) {
		UleeDragWidget* b = btns.Num() > 0 ? btns[i] :
			lUserChoises[idx]->lCreateDragButton(paths[i], true, true, "", ids);
		b->lSetTexture(paths[i]);
		b->lSetId(ids);
		if (btns.Num() <= 0)
			btns.Add(b);
	}
	return btns;
}

TArray<UleeDragWidget*> UThreeLines::GetAllButtons()
{
	int n = 0;
	TArray<UleeDragWidget*> alls{};
	for (auto& p : lUserChoises) {
		for (int i = 0; i < p->lDragDropButtons.Num(); i++) {
			p->lDragDropButtons[i]->lDelegateClear();
			alls.Add(p->lDragDropButtons[i]);
		}
		n++;
	}
	return TArray<UleeDragWidget*>();
}

void UThreeLines::LoadAllChoise(FGameLession& data)
{
	int n = 0;
	for (auto& c : lUserChoises) {
		TArray<FString> paths = data.Topics[n].Choises;
		TArray<UleeDragWidget*> choises= LoadChoisesAt(paths, n + 1, n);
		for (auto& wd : choises)
		{
			if (wd->lStatusImage->GetVisibility() == ESlateVisibility::Visible)
				wd->lStatusImage->SetVisibility(ESlateVisibility::Hidden);
		}
		n++;
	}
}

