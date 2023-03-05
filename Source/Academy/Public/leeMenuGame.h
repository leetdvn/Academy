// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Kismet/GameplayStatics.h"
#include "leePanelBase.h"
#include "leePublicInterface.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeMenuGame.generated.h"

/**
 * 
 */
UCLASS()
class ACADEMY_API UleeMenuGame : public UUserWidget, public IleePublicInterface
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnMenuClick(FString menuName);
protected:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils", DisplayName = "Menu" ,meta=(BindWidget));
		UleePanelBase* GameMenu;
	
	virtual void NativeConstruct() override;

	FString mapOpen;
};
