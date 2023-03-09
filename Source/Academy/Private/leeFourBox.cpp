#include "leeFourBox.h"
#include "Kismet/KismetStringLibrary.h"

void UleeFourBox::NewFourBoxInit()
{
	FString sourceDir = FPaths::ProjectContentDir() + lFourBox->lTopicSourceFolder;
	FString choiseDir = FPaths::ProjectContentDir() + lFourBox->lChoiseSourceFolder;
	TArray<FString> topics = lGetAllDirectory(sourceDir),questions;
	int count{};

	//in it data game---------------------------------
	fourdata.LessionType = FourBox;
	fourdata.GameID = userdata->JsGames.Num() + 1;
	fourdata.GameTitle = ltitle->GetText().ToString();
	fourdata.GameDescriptions = lDescription->GetText().ToString();
	fourdata.GameDecorPath = "";
	//implantation quession;
	for (auto& quest : lFourBox->lQuestions) {
		int32 rand = lRand(0, topics.Num());
		FString randSource = sourceDir +"/" + topics[rand]; 
		FString sload = lGetRandFileFromDirectory(randSource);
		//lGetRandFilesFromDirectory(sourceDir,questions, 1);
		FString imgQuest = "/Game/" + lFourBox->lTopicSourceFolder + "/" + topics[rand] + "/" + sload;
		
		//get textures--------------------------------------
		UTexture2D *tex = lGetTextureFromPath(imgQuest);
		//set size------------------------------------------
		FVector2D bSize = lGetSizeTexture(imgQuest);
		if (tex) {
			quest->SetBrushResourceObject(tex);
			quest->SetBrushSize(bSize);
		}
		//create data topic---------------------------
		fourdata.topicPaths.Add(imgQuest);
	}
	
	//get player choise bgr buttons
	TArray<FString> cDir = lGetAllDirectory(choiseDir,true);
	TArray<int32> wrap = { 0,1,2,3 };
	wrap.SwapMemory(0, lRand(1,wrap.Num()));
	//initialization player choise
	int xcount=0;
	for (auto& ans : lFourBox->lUserChoises) {
		//cDir.SwapMemory(xcount, );
		FString cPath = "/Game/" + lFourBox->lChoiseSourceFolder +  "/" + cDir[wrap[xcount]];
		fourdata.ChoiseBgrs.Add(cPath);
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
	for (auto& n : nums) {
		overText.AddUnique(FString::FromInt(n));

	}
	//lDebug(overText.Num());

	lFourBox->lUserChoises[idx]->lOverrideTextName(overText, buttons);
	fourdata.topicNums.Add(num);
	//implantation Buttons and correct click
	int count{};
	for (auto& btn : buttons) {
		int32 idName = UKismetStringLibrary::Conv_StringToInt(overText[count]);
		btn->Id = idName;
		if (idName == num) {
			//bind correct button when action
			btn->lButton->OnClicked.AddDynamic(this, &UleeFourBox::OnCorrectAnswer);
		}
		else {
			// case fail to choise
			btn->OnIdSent.AddDynamic(this, &UleeFourBox::OnIdReCeiveClick);
		}
		count++;
	}
	return ;
}

void UleeFourBox::LoadCurrentGame()
{
	//dont' need reload neet make choise new avaible
	lDebug("On Replay", FColor::Purple, " ");
	
}

void UleeFourBox::OnCorrectAnswer()
{
	AnswerCorrect++;
	if (AnswerCorrect == 4) {
		AnswerCorrect = 0;

		/// save data pass to next game lession
		OnSaveData();
	}
	//debug
	lDebug("Correct yeah..!!");
}

void UleeFourBox::OnIdReCeiveClick(int idsent)
{
	lDebug(idsent);
}

void UleeFourBox::LoadQuestionsAt(FString choisePath, int32 idx)
{

	if(!lFilesExists(choisePath) || idx < 0 && idx >= lFourBox->lQuestions.Num()) return;

	//----------------------------------------------
	UImage* img =lFourBox->lQuestions[idx];

	UTexture2D* tex = lGetTextureFromPath(choisePath);
	FVector2D bSize = lGetSizeTexture(choisePath);
	if (tex) {
		img->SetBrushResourceObject(tex);
		img->SetBrushSize(bSize);
	}
}

void UleeFourBox::LoadChoiseAt(FString topicsPath, int32 idx)
{
}

void UleeFourBox::LoadCurrentQuestions()
{
	AnswerCorrect = 0;
	//for (int i = 0; i < lFourBox->lQuestions.Num(); i++) 
	//	LoadQuestionsAt(fourdata.topicPaths[i], i);
}

void UleeFourBox::NativeConstruct()
{
	ReloadData();
	NewFourBoxInit();
	//lGetTopicCaculateAt(1);
}

void UleeFourBox::ReloadData()
{
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameIns) { lDebug("Game Instance Nullptr"); }
	//load data
	GameIns->LoadGameData();
	userdata = GameIns->GameData;

	UE_LOG(LogTemp, Warning, TEXT("load Data : %s"), *userdata->GetAllGames());
}

void UleeFourBox::OnSaveData()
{
	ReloadData();
	TSharedPtr<FJsonObject> game = FJsonObjectConverter::UStructToJsonObject<FFourBoxData>(fourdata, 0, 0);
	userdata->JsGames.Add(MakeShareable(new FJsonValueObject(game)));

	//save
	if (GameIns)
		GameIns->SaveCurrentGameData(userdata);
}
