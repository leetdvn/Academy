// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <PlayerData.h>
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* OpenUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* CloseDown;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnCloseDown() { PlayAnimation(CloseDown); isAvalible = false; }

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
	void lOnEnglish();
	UFUNCTION()
	void lOnVietnam();
	UFUNCTION()
	void lOnChinese();
	//UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
	//	void lOnSinginSuccess(const FString userID,const FString email);
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		UleeGameInstance* GameIns;


	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		bool CheckLinkAccount();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		FString DisplayInfo;


	bool isAvalible;


protected:

	const FString SoundOn="/Game/AcademyAssets/Assets/Textures/UI/Shop/sound_on";
	const FString SoundOff="/Game/AcademyAssets/Assets/Textures/UI/Shop/sound_off";

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnSoundToogle();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnMusicToogle();

	bool soundToogle, MusicToogle;

};
