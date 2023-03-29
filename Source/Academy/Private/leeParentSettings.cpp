// Fill out your copyright notice in the Description page of Project Settings.


#include "leeParentSettings.h"

UleeParentSettings::UleeParentSettings(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UleeParentSettings::OnOpenUp()
{
	PlayAnimation(OpenUp); isAvalible = true;
}

void UleeParentSettings::lAccountLoginToogle()
{
	ESlateVisibility vis = AccountLogin->GetVisibility() == ESlateVisibility::Hidden ? 
		ESlateVisibility::SelfHitTestInvisible : 
		ESlateVisibility::Hidden;
	return AccountLogin->SetVisibility(vis);
	//UFirebaseAuthenticationSubsystem::FacebookSignIn();
}

void UleeParentSettings::lSaveLinkUser(FString UserId, FString Email, FString displayname)
{
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UPlayerData* data = GameIns->LoadCurrentGameData();
	data->DisplayName = displayname;
	data->Email = Email;
	data->UserID = UserId;
	GameIns->SaveCurrentGameData(data);

}

bool UleeParentSettings::CheckLinkAccount()
{
	//check link Account
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameIns) {
		lDebug("Game Instance Nullptr"); return false; 
		
	}
	UPlayerData* data = GameIns->LoadCurrentGameData();
	FString DisplayName = "Account :   " + data->DisplayName;
	AccountName->SetText(FText::FromString(DisplayName));
	if (!data->DisplayName.IsEmpty()) {
		AccountLink->SetVisibility(ESlateVisibility::Hidden);
		return true;
	}
	return false;
}


void UleeParentSettings::NativeConstruct()
{

	//bind function
	if (Sound) {
		Sound->OnMouseButtonDownEvent.BindUFunction(this, FName("OnSoundToogle"));
	}

	if (Music) {
		Music->OnMouseButtonDownEvent.BindUFunction(this, FName("OnMusicToogle"));

	}

	if (lClosed)
		lClosed->OnClicked.AddDynamic(this, &UleeParentSettings::OnCloseDown);

	if (lBgr)
		lBgr->OnMouseButtonDownEvent.BindUFunction(this, FName("OnCloseDown"));
}

void UleeParentSettings::OnSoundToogle()
{
	//lDebug(Sound->Brush.GetResourceObject()->GetPathName());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Sound->Brush.GetResourceObject()->GetPathName());
	soundToogle = !soundToogle;
	UTexture2D* tex = !soundToogle ? 
		lGetTextureFromPath(SoundOn) :
		lGetTextureFromPath(SoundOff);
	Sound->SetBrushResourceObject(tex);
}

void UleeParentSettings::OnMusicToogle()
{
	//lDebug("Music clickd");
	MusicToogle = !MusicToogle;
	UTexture2D* tex = !MusicToogle ? 
		lGetTextureFromPath(SoundOn) :
		lGetTextureFromPath(SoundOff);
	Music->SetBrushResourceObject(tex);

}
