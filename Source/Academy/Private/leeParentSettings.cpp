// Fill out your copyright notice in the Description page of Project Settings.


#include "leeParentSettings.h"
#include <Kismet/KismetInternationalizationLibrary.h>

UleeParentSettings::UleeParentSettings(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UleeParentSettings::OnOpenUp()
{
	PlayAnimation(OpenUp); isAvalible = true;
	FString language = UKismetInternationalizationLibrary::GetCurrentLanguage();
	lDebug(language);
	if (language == "vi") lOnVietnam();
	else if (language == "en") lOnEnglish();
	else lOnChinese();

}

void UleeParentSettings::lAccountLoginToogle()
{
	ESlateVisibility vis = AccountLogin->GetVisibility() == ESlateVisibility::Hidden ? 
		ESlateVisibility::SelfHitTestInvisible : 
		ESlateVisibility::Hidden;
	return AccountLogin->SetVisibility(vis);
	//UFirebaseAuthenticationSubsystem::FacebookSignIn();
}

void UleeParentSettings::lSaveLinkUser(FString UserId, FString Email, FString dispname)
{
	///Save link User
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UleeUserInfo* data = GameIns->LoadPlayerInfo();
	data->DisplayName = dispname;
	data->UserID = UserId;
	GameIns->SaveUserInfo(data);
}

void UleeParentSettings::lSetImageTexture2D(UImage* image, UTexture2D* newtexture)
{
	if (!image || !newtexture) return;
	image->SetBrushFromTexture(newtexture,true);
}

#pragma region On Language Changed
void UleeParentSettings::lOnEnglish()
{
	Language_Chinese->SetBrushFromTexture(uncheckImg, true);
	Language_Vietnamese->SetBrushFromTexture(uncheckImg, true);
	Language_English->SetBrushFromTexture(checkedImg, true);
	UKismetInternationalizationLibrary::SetCurrentLanguage("en", true);
}

void UleeParentSettings::lOnVietnam()
{
	Language_Chinese->SetBrushFromTexture(uncheckImg, true);
	Language_Vietnamese->SetBrushFromTexture(checkedImg, true);
	Language_English->SetBrushFromTexture(uncheckImg, true);
	UKismetInternationalizationLibrary::SetCurrentLanguage("vi", true);

}

void UleeParentSettings::lOnChinese()
{
	Language_Chinese->SetBrushFromTexture(checkedImg, true);
	Language_Vietnamese->SetBrushFromTexture(uncheckImg, true);
	Language_English->SetBrushFromTexture(uncheckImg, true);
	UKismetInternationalizationLibrary::SetCurrentLanguage("cn", true);

}
#pragma endregion //On Language Changed

bool UleeParentSettings::CheckLinkAccount()
{
	//check link Account Uuser
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UleeUserInfo* data = GameIns->PlayerInfo;

	FString DisplayName = data->DisplayName;
	DisplayInfo = data->DisplayName;
	lDebug(DisplayName);
	Displayname->SetText(FText::FromString(DisplayName));
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

	//on English
	if (Language_English)
		Language_English->OnMouseButtonDownEvent.BindUFunction(this, FName("lOnEnglish"));
	//on Vietname
	if (Language_Vietnamese)
		Language_Vietnamese->OnMouseButtonDownEvent.BindUFunction(this, FName("lOnVietnam"));

	//on Chinese
	if (Language_Chinese)
		Language_Chinese->OnMouseButtonDownEvent.BindUFunction(this, FName("lOnChinese"));


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
