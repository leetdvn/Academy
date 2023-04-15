#include "CanvasFourBox.h"
#include <Kismet/KismetStringLibrary.h>

UCanvasFourBox::UCanvasFourBox(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//init something
	//UE_LOG(LogTemp, Warning, TEXT("4 box init"));
}

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
	if (idx < 0 || idx > lUserChoises.Num())
		return;
	
	return lUserChoises[idx]->lSetMakeSameAt(path, isDragButton);
}

void UCanvasFourBox::lSetQuestions(TArray<FString> &paths)
{
	if (paths.Num() <= 0) return;
	//set size-------------------------------------------------
	int i = 0;
	for (auto& img : lQuestions) {
		UTexture2D* tex = lGetTextureFromPath(paths[i]);
		//set size---------------------------------------------
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
	if (idx < 0 || idx > lUserChoises.Num()) return;

	return lUserChoises[idx]->lOverrideTextName(texts);

}

void UCanvasFourBox::CreateGenerator(FFourBoxData& outData) {

	//clear if old data
	lClearChecked();
	lClearActionBound();
	//generator topic
	TArray<FString> topics = lGeneratorTopics(outData);
	//genrator topic
	lSetQuestions(topics);
	//lGeneratorChoiseBgr(outData);
	lGeneratorNumber(outData);
}

void UCanvasFourBox::OnLoadFromData(FFourBoxData& outData)
{
	//data Questions
	lSetQuestions(outData.topicPaths);
	//data background
	int32 i = 0;
	for (auto& bgr : lUserChoises) {
		bgr->lSetMakeSameAt(outData.ChoiseBgrs[i],false);
		//load data choise
		bgr->lOverrideTextName(outData.textsChoiss);
		//clear
		//bgr->lsetch
		i++;
	}
	lClearChecked();
	//data choise
}

int32 UCanvasFourBox::lGetCorrectNumberAt(int32 idx)
{
	if (idx > lQuestions.Num() - 1 || idx < 0) return 0;

	TArray<int32> correctNums{};
	//convert string to int
	FString qName = lQuestions[idx]->Brush.GetResourceName().ToString();
	FString number = qName.Left(2);
	int32 num = UKismetStringLibrary::Conv_StringToInt(number);
	return num;
}

/*Create topics and bgr Buttons  from generat*/
TArray<FString> UCanvasFourBox::lGeneratorTopics(FFourBoxData& outData)
{
	FString sourceDir = FPaths::ProjectContentDir() + lTopicSourceFolder;
	FString choiseDir = FPaths::ProjectContentDir() + lChoiseSourceFolder;
	TArray<FString> topics{}, result{}; //= lGetAllDirectory(sourceDir),questions;
	int count{};
	lGetRandDirsFromDirectory(sourceDir, topics, 4);
	TArray<FString> choiseBgr = lGeneratorChoiseBgr(outData);
	int32 t = 0;
#pragma omp parallel for
	for (auto& quest : lQuestions) {
		FString randSource = sourceDir + "/" + topics[t];
		FString sload = lGetRandFileFromDirectory(randSource);
		FString imgQuest = "/Game/" + lTopicSourceFolder + "/" + topics[t] + "/" + sload;
		result.Add(imgQuest);
		//set bgr
		lUserChoises[t]->lSetMakeSameAt(choiseBgr[t], false);
		t++;
	}
	lDebug(choiseBgr.Num());
	lTopics = result;
	outData.topicPaths = result;

	return result;
}

TArray<FString> UCanvasFourBox::lGeneratorChoiseBgr(FFourBoxData& outData)
{
	//if (lTopics.Num() <= 0) return TArray<FString>();
	FString choiseDir = FPaths::ProjectContentDir() + lChoiseSourceFolder;
	TArray<FString> cDir = lGetAllDirectory(choiseDir, true);
	TArray<FString> results{};
	TArray<int32> wrap = { 0,1,2,3 };
	wrap.SwapMemory(0, lRand(1, wrap.Num()));
	//initialization player choise
	int xcount = 0;
#pragma omp parallel for
	for (auto& ans : lUserChoises) {
		//cDir.SwapMemory(xcount, );
		FString cPath = "/Game/" + lChoiseSourceFolder + "/" + cDir[wrap[xcount]];
		ans->lSetMakeSameAt(cPath, false);
		outData.ChoiseBgrs.Add(cPath);
		results.Add(cPath);
		ans->lSetPanelId(xcount);
		xcount++;
	}
	return results;
}

void UCanvasFourBox::lGetCorrectButtons(TArray<UleeBaseButton*> &buttons)
{
	int32 i = 0;
//#pragma omp parallel for
	for (auto& t : lUserChoises) {
		int32 correctnum = lGetCorrectNumberAt(i);
		for (auto& b : t->lGetButtons())
		{
			if (b->lGetText() == FString::FromInt(correctnum))
				buttons.Add(b);
		}
		i++;
	}
}

void UCanvasFourBox::lClearChecked() {
	for (auto& ans : lUserChoises) {
		ans->lResetChecked();
	}
}

void UCanvasFourBox::lClearActionBound()
{
	for (auto& b : lUserChoises) {
		for (auto& btn : b->lGetButtons())
			if (btn->OnCorrect.IsBound())
				btn->OnCorrect.Clear();
	}
}

void UCanvasFourBox::lGeneratorNumber(FFourBoxData& outData) {
	int32 i = 0;
//#pragma omp parallel for
	for (auto& ans : lUserChoises) {
		
		int32 correctNum = lGetCorrectNumberAt(i);
		TArray<int32> outNums = { correctNum };
		lGetRandNums(outNums, 3, 11);
		outNums.SwapMemory(0, lRand(1, outNums.Num()));
		TArray<FString> result{};
		for (auto& num : outNums) {
			FString str = FString::FromInt(num);
			result.Add(str);
			outData.textsChoiss.Add(str);

		}
		lSetChoiseTextAt(i, result);

		for (auto& b : ans->lGetButtons()) {
			if (b->lGetText() == FString::FromInt(correctNum)) {
				//lDebug(b->lGetText());
				CorrectButtons.Add(b);
			}
			else { UnCorrectButtons.Add(b); }
		}

		i++;
	}
}
