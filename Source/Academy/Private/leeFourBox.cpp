#include "leeFourBox.h"
#include "Kismet/KismetStringLibrary.h"

void UleeFourBox::NewFourBoxInit()
{
	FString sourceDir = FPaths::ProjectContentDir() + lFourBox->lTopicSourceFolder;
	FString choiseDir = FPaths::ProjectContentDir() + lFourBox->lChoiseSourceFolder;
	TArray<FString> topics = lGetAllDirectory(sourceDir),questions;
	int count{};
	for (auto& quest : lFourBox->lQuestions) {
		int32 rand = lRand(0, topics.Num());
		FString randSource = sourceDir +"/" + topics[rand]; 
		FString sload = lGetRandFileFromDirectory(randSource);
		//lGetRandFilesFromDirectory(sourceDir,questions, 1);

		FString imgQuest = "/Game/" + lFourBox->lTopicSourceFolder + "/" + topics[rand] + "/" + sload;
		UTexture2D *tex = lGetTextureFromPath(imgQuest);
		FVector2D bSize = lGetSizeTexture(imgQuest);
		if (tex) {
			quest->SetBrushResourceObject(tex);
			quest->SetBrushSize(bSize);
		}
	}
	
	//"AcademyAssets/Assets/Textures/Caculate/number";
	TArray<FString> cDir = lGetAllDirectory(choiseDir,true);
	//lDebug(cDir.Num()); lDebug(choiseDir,FColor::Green);
	//return;
	TArray<int32> wrap = { 0,1,2,3 };
	wrap.SwapMemory(0, lRand(1,wrap.Num()));
	int xcount=0;
	for (auto& ans : lFourBox->lUserChoises) {
		//cDir.SwapMemory(xcount, );
		FString cPath = "/Game/" + lFourBox->lChoiseSourceFolder +  "/" + cDir[wrap[xcount]];
		//lDebug(cDir[xcount], FColor::Green);
		ans->lSetMakeSameAt(cPath, false);
		lSetChoiseDiffAt(xcount);
		xcount++;
	}
}

void UleeFourBox::lSetChoiseDiffAt(int32 idx)
{
	if (idx < 0 || idx > lFourBox->lQuestions.Num()) return ;

	FString qName = lFourBox->lQuestions[idx]->Brush.GetResourceName().ToString();
	FString number = qName.Left(1);
	//convert string to int
	int32 num =UKismetStringLibrary::Conv_StringToInt(number);
	TArray<UleeBaseButton*> buttons = lFourBox->lUserChoises[idx]->lGetButtons();
	if (buttons.Num() <= 0) return ;

	//get Array numbers diffirence
	TArray<int32> nums{ num };
	lGetRandNums(nums, buttons.Num(),11);

	//conver Array Number to String
	TArray<FString> overText{};
	for (auto& n : nums)
		overText.AddUnique(FString::FromInt(n));

	//lDebug(overText.Num());

	lFourBox->lUserChoises[idx]->lOverrideTextName(overText, buttons);


	return ;
}

void UleeFourBox::NativeConstruct()
{
	NewFourBoxInit();
	//lGetTopicCaculateAt(1);
}
