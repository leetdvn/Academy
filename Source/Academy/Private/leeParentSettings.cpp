// Fill out your copyright notice in the Description page of Project Settings.


#include "leeParentSettings.h"
#include <Kismet/KismetInternationalizationLibrary.h>

UleeParentSettings::UleeParentSettings(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UleeParentSettings::OnCloseDown()
{
	if (!isAvalible) return;
	PlayAnimation(CloseDown);
	isAvalible = false;

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

void UleeParentSettings::lSaveLinkUser(FString UserId, FString Email, FString dispname)
{
	///Save link User
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	data = GameIns->PlayerInfo;
	data->DisplayName = dispname;
	data->UserID = UserId;
	GameIns->SaveUserInfo(data);
}

void UleeParentSettings::lSetImageTexture2D(UImage* image, UTexture2D* newtexture)
{
	if (!image || !newtexture) return;
	image->SetBrushFromTexture(newtexture,true);
}

#pragma region On Language Changed Localizations
void UleeParentSettings::lOnEnglish(bool isReset)
{
	UKismetInternationalizationLibrary::SetCurrentLanguage("en", true);
	ResetMapLevel(GetWorld());
}

void UleeParentSettings::lOnVietnam(bool isReset)
{
	UKismetInternationalizationLibrary::SetCurrentLanguage("vi", true);
	ResetMapLevel(GetWorld());

}

void UleeParentSettings::lOnChinese(bool isReset)
{
	UKismetInternationalizationLibrary::SetCurrentLanguage("zh", true);
	ResetMapLevel(GetWorld());

}
#pragma endregion 

bool UleeParentSettings::CheckLinkAccount()
{
	//check link Account Uuser
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	data = GameIns->PlayerInfo;

	FString DisplayName = data->DisplayName;
	DisplayInfo = data->DisplayName;
	Displayname->SetText(FText::FromString(DisplayName));
	FString tex = FString::FromInt(data->Star) + FText::FromStringTable(SETTINGTABLE, "Star").ToString();
	KidStar->SetText(FText::FromString(tex));
	if (!data->DisplayName.IsEmpty()) {
		AccountLink->SetVisibility(ESlateVisibility::Hidden);
		return true;
	}
	return false;
}

void UleeParentSettings::lLanguageInitialize()
{
	FString language = UKismetInternationalizationLibrary::GetCurrentLanguage();
	UTexture2D* viTex = language == "vi" ? checkedImg : uncheckImg;
	UTexture2D* enTex = language == "en" ? checkedImg : uncheckImg;
	UTexture2D* zhTex = language == "zh" ? checkedImg : uncheckImg;
	Language_Chinese->SetBrushFromTexture(zhTex, true);
	Language_Vietnamese->SetBrushFromTexture(viTex, true);
	Language_English->SetBrushFromTexture(enTex, true);

}

void UleeParentSettings::InItSoundClass()
{
	//FStringAssetReference MyAssetPath("SoundClass'/Game/Audio/KidSound.KidSound'");
	//UObject* MyAsset = MyAssetPath.TryLoad();
	//KidSound = Cast<USoundClass>(MyAsset);

	UTexture2D* tex = soundToogle ?
		lGetTextureFromPath(SoundOn) :
		lGetTextureFromPath(SoundOff);
	Sound->SetBrushResourceObject(tex);
	float volume = !soundToogle ? 0 : 1;
	SetSoundVolume(volume);
}

void UleeParentSettings::InItMusicClass()
{
	UTexture2D* tex = MusicToogle ?
		lGetTextureFromPath(SoundOn) :
		lGetTextureFromPath(SoundOff);
	Music->SetBrushResourceObject(tex);

	//AHUD* hub = lGetHub(GetWorld());
	//AleeHub *leeHub = Cast<AleeHub>(H)
	float volume = !MusicToogle ? 0 : 1;
	SetMusicVolume(volume);

}

void UleeParentSettings::NativeConstruct()
{
	Super::NativeConstruct();
	GameIns = Cast<UleeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	data = GameIns->PlayerInfo;
	soundToogle = data->Sound;
	MusicToogle = data->Music;

	//UGameplayStatics::PlayDialogue2D(GetWorld(), lKidMusic, lMusic, vol);
	//bind function
	if (Sound) {
		InItSoundClass();
		Sound->OnMouseButtonDownEvent.BindUFunction(this, FName("OnSoundToogle"));
	}

	if (Music) {
		InItMusicClass();
		Music->OnMouseButtonDownEvent.BindUFunction(this, FName("OnMusicToogle"));

	}

	//if (lClosed)
	//	lClosed->OnClicked.AddDynamic(this, &UleeParentSettings::OnCloseDown);

	//if (lBgr)
	//	lBgr->OnMouseButtonDownEvent.BindUFunction(this, FName("OnCloseDown"));

	//on English
	if (Language_English)
		Language_English->OnMouseButtonDownEvent.BindUFunction(this, FName("lOnEnglish"));
	//on Vietname
	if (Language_Vietnamese)
		Language_Vietnamese->OnMouseButtonDownEvent.BindUFunction(this, FName("lOnVietnam"));

	//on Chinese
	if (Language_Chinese)
		Language_Chinese->OnMouseButtonDownEvent.BindUFunction(this, FName("lOnChinese"));

	///check box init tialize
	lLanguageInitialize();


}

void UleeParentSettings::NativeDestruct()
{
	/*clear event */
	//Sound->OnMouseButtonDownEvent.Clear();
	//Music->OnMouseButtonDownEvent.Clear();
	//Language_English->OnMouseButtonDownEvent.Clear();
	//Language_Chinese->OnMouseButtonDownEvent.Clear();
	//Language_Vietnamese->OnMouseButtonDownEvent.Clear();
}

void UleeParentSettings::OnSoundToogle()
{
	/*Sound Toogle CLickc*/
	soundToogle = !soundToogle;
	float volume = !soundToogle ? 0 : 1;
	KidSound->Properties.Volume = volume;
	data->Sound = soundToogle;
	GameIns->SaveUserInfo(data);
	InItSoundClass();
}

void UleeParentSettings::OnMusicToogle()
{
	/*Music Toogle CLickc*/
	MusicToogle = !MusicToogle;
	float volume = !soundToogle ? 0 : 0.5f;
	KidMusic->Properties.Volume = volume;
	data->Music = MusicToogle;
	GameIns->SaveUserInfo(data);
	InItMusicClass();
}
