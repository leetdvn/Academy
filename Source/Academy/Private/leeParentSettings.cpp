// Fill out your copyright notice in the Description page of Project Settings.


#include "leeParentSettings.h"

UleeParentSettings::UleeParentSettings(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UleeParentSettings::NativeConstruct()
{
	//MusicOn = Cast<UTexture2D>(Music->Brush.GetResourceObject());
	//SoundOn = Cast<UTexture2D>(Sound->Brush.GetResourceObject());
	
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
