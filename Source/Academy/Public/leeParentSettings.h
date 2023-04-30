// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <leeGameInstance.h>
#include "leeAccoutAuthenication.h"
#include "Components/Button.h"
#include "leePublicInterface.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeParentSettings.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ACADEMY_API UleeParentSettings : public UUserWidget, public IleePublicInterface
{
	GENERATED_BODY()
	
public:
	UleeParentSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Sounds", meta = (BindWidget));
		UImage* Sound;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Mucis", meta = (BindWidget));
		UImage* Music;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Bgr", meta = (BindWidget));
		UImage* lBgr;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "English", meta = (BindWidget));
		UImage* Language_English;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Vietnamese", meta = (BindWidget));
		UImage* Language_Vietnamese;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Chinese", meta = (BindWidget));
		UImage* Language_Chinese;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "disable image");
		UTexture2D* uncheckImg;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "enable image");
		UTexture2D* checkedImg;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Closed Button", meta = (BindWidget));
		UButton* lClosed;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Sign In", meta = (BindWidget));
		UButton* AccountLink;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Login Widget", meta = (BindWidget));
		UleeAccoutAuthenication* AccountLogin;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Displayname", meta = (BindWidget));
		class UTextBlock* Displayname;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Star", meta = (BindWidget));
		class URichTextBlock* KidStar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils")
		USoundClass* KidSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils")
		USoundClass* KidMusic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* OpenUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* CloseDown;


	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnCloseDown();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnOpenUp();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool lGetSoundToogle() { return soundToogle; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool lGetMusicToogle() { return MusicToogle; }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lAccountLoginToogle();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSaveLinkUser(FString UserId, FString Email,FString dispname);

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lSetImageTexture2D(UImage* image, UTexture2D* newtexture);

	UFUNCTION()
	void lOnEnglish(bool isReset=true);
	UFUNCTION()
	void lOnVietnam(bool isReset = true);
	UFUNCTION()
	void lOnChinese(bool isReset = true);
	//UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
	//	void lOnSinginSuccess(const FString userID,const FString email);
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		UleeGameInstance* GameIns;


	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool CheckLinkAccount();


	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lLanguageInitialize();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		FString DisplayInfo;

	UPROPERTY()
		UleeUserInfo* data;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Status")
		bool isAvalible;

	void InItSoundClass();

	void InItMusicClass();


	void SetSoundVolume(float volume) { 
		if (volume < 0 || volume > 1) return;
		KidSound->Properties.Volume = volume;
	}

	void SetMusicVolume(float volume) { 
		if (volume < 0 || volume > 1) return;
		KidMusic->Properties.Volume = volume; 
	};

protected:

	const FString SoundOn="/Game/AcademyAssets/Assets/Textures/UI/Shop/sound_on";
	const FString SoundOff="/Game/AcademyAssets/Assets/Textures/UI/Shop/sound_off";

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
	/*Sound Toogle CLickc*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnSoundToogle();

	/*Music Toogle CLickc*/
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnMusicToogle();

	bool soundToogle, MusicToogle;

};
