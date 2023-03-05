#include "leeFourBox.h"

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
		lDebug(cDir[xcount], FColor::Green);
		ans->lSetMakeSameAt(cPath, false);
		xcount++;
	}
}

void UleeFourBox::NativeConstruct()
{
	NewFourBoxInit();
}
