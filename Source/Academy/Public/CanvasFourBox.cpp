#include "CanvasFourBox.h"

UleePanelBase* UCanvasFourBox::lGetChoiseAt(int32 idx)
{
	if (idx <= 0 || idx > lUserChoises.Num())
		return nullptr;
	return lUserChoises[idx];
}

UImage* UCanvasFourBox::lGetQuestionAt(int32 idx)
{
	if (idx <= 0 || idx > lQuestions.Num())
		return nullptr;
	return lQuestions[idx];
}

void UCanvasFourBox::lSetChoiseBgr(int32 idx, FString& path, bool isDragButton)
{
	if (idx <= 0 || idx > lUserChoises.Num())
		return;
	
	return lUserChoises[idx]->lSetMakeSameAt(path, isDragButton);
}

void UCanvasFourBox::lSetQuestions(TArray<FString> &paths)
{
	if (paths.Num() <= 0) return;
	//set size------------------------------------------
	int i = 0;
	for (auto& img : lQuestions) {
		UTexture2D* tex = lGetTextureFromPath(paths[i]);
		//set size------------------------------------------
		FVector2D bSize = lGetSizeTexture(paths[i]);
		if (tex) {
			img->SetBrushResourceObject(tex);
			img->SetBrushSize(bSize);
		}
		i++;
	}
}

void UCanvasFourBox::lSetChoiseTextAt(int32 idx, TArray<FString> texts)
{
	if (idx <= 0 || idx > lUserChoises.Num()) return;

	return lUserChoises[idx]->lOverrideTextName(texts);

}
