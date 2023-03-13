#include "leeFourBox.h"
#include "Kismet/KismetStringLibrary.h"

void UleeFourBox::NewFourBoxInit()
{
	FString sourceDir = FPaths::ProjectContentDir() + lFourBox->lTopicSourceFolder;
	FString choiseDir = FPaths::ProjectContentDir() + lFourBox->lChoiseSourceFolder;
	TArray<FString> topics; //= lGetAllDirectory(sourceDir),questions;
	int count{};
	lGetRandDirsFromDirectory(sourceDir, topics, 4);
	for (auto& t : topics)
		lDebug(t, FColor::Purple, "folder");
	//in it data game---------------------------------
	fourdata.LessionType = FourBox;
	fourdata.GameID = userdata->JsGames.Num() + 1;
	fourdata.GameTitle = ltitle->GetText().ToString();
	fourdata.GameDescriptions = lDescription->GetText().ToString();
	fourdata.GameDecorPath = "";
	//implantation quession;
	int32 t = 0;
	for (auto& quest : lFourBox->lQuestions) {
		FString randSource = sourceDir +"/" + topics[t]; 
		FString sload = lGetRandFileFromDirectory(randSource);
		//lGetRandFilesFromDirectory(sourceDir,questions, 1);
		FString imgQuest = "/Game/" + lFourBox->lTopicSourceFolder + "/" + topics[t] + "/" + sload;
		
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
		t++;
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
		ans->lResetChecked();
		xcount++;
	}
}

void UleeFourBox::lSetChoiseDiffAt(int32 idx,bool isnewgame)
{
	if (idx < 0 || idx > lFourBox->lQuestions.Num()) return ;

	FString qName = lFourBox->lQuestions[idx]->Brush.GetResourceName().ToString();
	FString number = qName.Left(2);
	//FString test = qName.Left(2);
	//convert string to int
	int32 num =UKismetStringLibrary::Conv_StringToInt(number);
	TArray<UleeBaseButton*> buttons = lFourBox->lUserChoises[idx]->lGetButtons();
	if (buttons.Num() <= 0) return ;
	//lDebug(num);
	//get Array numbers diffirence
	TArray<int32> nums{ num };
	lGetRandNums(nums, buttons.Num(),11);

	//conver Array Number to String
	TArray<FString> overText{};
	for (auto& n : nums) {
		overText.AddUnique(FString::FromInt(n));

	}
	//lDebug(overText.Num());
	overText.SwapMemory(0, lRand(1, overText.Num()));
	lFourBox->lUserChoises[idx]->lOverrideTextName(overText, buttons);
	if(isnewgame)
		fourdata.topicNums.Add(num);
	//implantation Buttons and correct click
	int count{};
	for (auto& btn : buttons) {
		int32 idName = UKismetStringLibrary::Conv_StringToInt(overText[count]);
		btn->Id = idName;
		if (idName == num) {
			//bind correct button when action
			//btn->lButton->OnClicked.AddDynamic(this, &UleeFourBox::OnCorrectAnswer);
			btn->Id = idx;
			btn->OnCorrect.AddDynamic(this, &UleeFourBox::OnCorrectAnswer);

		}
		else {
			// case fail to choise
			btn->lButton->OnClicked.AddDynamic(this, &UleeFourBox::OnIdReCeiveClick);
		}
		count++;
	}
	return ;
}

void UleeFourBox::LoadCurrentGame(int dataIndex)
{
	//dont' need reload neet make choise new avaible
	//lDebug("On Replay", FColor::Purple, " ");

	//ResetMapLevel(GetWorld());
	TSharedPtr<FJsonValue> jsVal= userdata->GetGamesAt(userdata->JsGames.Num()-1);
	FFourBoxData* nData=new FFourBoxData();
	FJsonObjectConverter::JsonObjectToUStruct(jsVal->AsObject().ToSharedRef(), nData);
	if (nData->topicPaths.Num() > 0) {
		int i = 0;
		for (auto& p : lFourBox->lQuestions) {
			LoadQuestionsAt(nData->topicPaths[i], i);
			//lSetChoiseDiffAt(i,false);
			i++;
		}
		//OnRePlayGame(fourdata);
			
	}

}

void UleeFourBox::OnCorrectAnswer(UleeBaseButton* button)
{
	if (AnswerCorrect > 4) return;
	AnswerCorrect++;
	
	lFourBox->lUserChoises[button->Id]->lSetDisable(true);
	if (button) {
		button->lSetChecked(true);

	}
	if (AnswerCorrect == 4) {
		/// save data pass to next game lession
		OnSaveData();
	}
	//debug
}

void UleeFourBox::OnIdReCeiveClick()
{
	//lDebug(idsent);
}

void UleeFourBox::LoadQuestionsAt(FString choisePath, int32 idx)
{

	if(idx < 0 && idx >= lFourBox->lQuestions.Num()) return;

	//----------------------------------------------
	UImage* img =lFourBox->lQuestions[idx];

	UTexture2D* tex = lGetTextureFromPath(choisePath);
	FVector2D bSize = lGetSizeTexture(choisePath);
	if (tex) {
		img->SetBrushResourceObject(tex);
		img->SetBrushSize(bSize);
	}
}

void UleeFourBox::LoadChoiseAt(int32 corrects, FString bgrs)
{
	//TArray<>
}

void UleeFourBox::OnRePlayGame(FFourBoxData& odata)
{
	for (auto& p : lFourBox->lUserChoises) {
		p->lSetDisable(false);
		for (auto& b : p->lGetButtons())
			if (b->lGetChecked()) b->lSetChecked(false);
	}
	AnswerCorrect = 0;
}

void UleeFourBox::LoadCurrentQuestions()
{
	//for (int i = 0; i < lFourBox->lQuestions.Num(); i++) 
	//	LoadQuestionsAt(fourdata.topicPaths[i], i);
}

void UleeFourBox::NativeConstruct()
{
	ReloadData();
	lDebug("two");
	return isNewGame ? NewFourBoxInit() : LoadCurrentGame(userdata->JsGames.Num()-1);
	//lGetTopicCaculateAt(1);
}

void UleeFourBox::ReloadData()
{
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameIns) { lDebug("Game Instance Nullptr"); }
	//load data
	GameIns->LoadGameData();
	userdata = GameIns->GameData;
	//UE_LOG(LogTemp, Warning, TEXT("load Data : %s"), *userdata->GetAllGames());
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
