// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "leePublicInterface.h"
#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "leeSmartCharacter2D.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ACADEMY_API AleeSmartCharacter2D : public APaperCharacter , public IleePublicInterface
{
	GENERATED_BODY()
	
public:


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Number Game Show Ads Reward")
		int32 NextRewardAds;

	int32 CompletedGameCount;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Delay")
		float AdsDelay{};


	int32 count;

	UFUNCTION()
		void ShowInterestialAds();



protected:
	virtual void BeginPlay() override;

	//virtual void Tick(float Deltatime) override;

};
