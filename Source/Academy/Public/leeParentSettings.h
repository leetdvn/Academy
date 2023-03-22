// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
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

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Sounds Off");
		UTexture2D* SoundOff;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Closed Button", meta = (BindWidget));
		UButton* lClosed;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "AccountName", meta = (BindWidget));
		class UTextBlock* AccountName;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Star", meta = (BindWidget));
		class URichTextBlock* KidStar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* OpenUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* CloseDown;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnCloseDown() { PlayAnimation(CloseDown); }

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnOpenUp() { PlayAnimation(OpenUp); }


protected:

	class UTexture2D* SoundOn;

	class UTexture2D* MusicOn;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnSoundToogle();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnMusicToogle();



	bool soundToogle, MusicToogle;
};
