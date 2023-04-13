#include "leeAlpha.h"



void UleeAlpha::CreateNewChoises()
{
	TArray<FString> choiseName = GeneratorChoises();
	if (choiseName.Num() <= 0 && choiseName.Num() != ChoiseButtons.Num()) return;
	choisePath = TArray<FString>();
	int count{};
	for (auto& iname : choiseName) {
		FString path = FString("/Game/") + ALPHACHOISES + iname;
		choisePath.Add(path);
		UTexture2D* tex = lGetTextureFromPath(path);
		//ChoisePanels[count]->SetBrushFromTexture(tex,true);
		float sX = tex->GetSizeX();
		float sY = tex->GetSizeY();
		FVector2D size2D = FVector2D(sX, sY);
		ChoiseButtons[count]->lSetTexture2D(tex);
		count++;
	}
	CorrectButtons = GetCorrectButtons();
}

bool UleeAlpha::isCorrectName(FString name)
{
	if (name.IsEmpty() || CorrectNames.Num() <= 0) return false;
	for (auto& n : CorrectNames) {
		if (n == name || name.EndsWith(n)) return true;
	}
	return false;
}

void UleeAlpha::lClearChecked()
{
	if (ChoiseButtons.Num() <= 0) return;

#pragma omp parallel for
	for (auto &btn : ChoiseButtons) {
		btn->lSetChecked(false);
		if (!btn->lButton->GetIsEnabled())
			btn->lButton->SetIsEnabled(true);
	}

}

void UleeAlpha::ClearAllBound()
{
#pragma omp parallel for
	for (auto& btn : ChoiseButtons) {
		btn->lClearCorrectBound();
	}

	CorrectButtons = TArray<UleeBaseButton*>();
}

void UleeAlpha::SetTopicBrush(UTexture2D *tex)
{
	if (!tex) return;

	topicImg->SetBrushFromTexture(tex, true);
}

void UleeAlpha::SetTopicBrush(FString Path)
{
	if (!lFilesRelativeExists(Path)) {
		lDebug("Path Does'nt Exists.");
		lDebug(Path);
		return;
	}
	/*---------------------------*/

	UTexture2D* tex = lGetTextureFromPath(Path);
	if (tex) {
		return SetTopicBrush(tex);
	}

}

void UleeAlpha::SetChoiseBrush(TArray<FString> paths)
{
	if (paths.Num() <= 0) return;

	int32 count{};
	for (auto& files : paths) {
		if (lFilesRelativeExists(files)) {
			UTexture2D* tex = lGetTextureFromPath(files);
			if(tex){
				ChoiseButtons[count]->lSetTexture2D(tex);
			}
		}
		count++;
	}
}

TArray<UleeBaseButton*> UleeAlpha::GetCorrectButtons()
{
	TArray<UleeBaseButton*> result= TArray<UleeBaseButton*>();
	for (auto*&btn : ChoiseButtons) {
		FString tName = btn->lGetTextureName();
		if (tName.Left(topicName.Len()) == topicName) {
			result.Add(btn);
			//UE_LOG(LogTemp, Warning, TEXT("Tex 1 : %s \n Tex 2 : %s"), *topicName, *tName.Left(topicName.Len()));
		}
	}
	return result;
}


TArray<FString> UleeAlpha::GeneratorChoises()
{
	TArray<FString> result{};
	FString basePath = FPaths::ProjectContentDir() + ALPHACHOISES;
	TArray<int32> nums{};
	lGetRandNums(nums, 3, 6);

	FString choise{};
	for (int i = 0; i < nums.Num(); i++) {
		choise = topicName + FString::FromInt(nums[i]);
		FString file = FPaths::ProjectContentDir() + ALPHADEFAULT + "/" + choise;
		//if(lFilesExists(file))
		result.Add(choise);
	}
	CorrectNames = result;
	lGetRandFilesFromDirectory(basePath, result, 6, topicName);

#pragma omp parallel for
	for (int i = 0; i < result.Num(); i++)
		if (i <= result.Num() / 2)
			result.SwapMemory(i, lRand(i + 1, result.Num()));

	return result;
}


UleeAlpha::UleeAlpha(const FObjectInitializer& ObjectInitializer)
{
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

