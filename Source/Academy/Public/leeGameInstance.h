// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leePublicEnum.h"
#include "leePublicInterface.h"
#include "PlayerData.h"
#include <Kismet/GameplayStatics.h>
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "leeGameInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ACADEMY_API UleeGameInstance : public UGameInstance ,public IleePublicInterface
{
	GENERATED_BODY()

	void Init() override;


public:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Save SlotName")
		FString SaveSlot;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "SaveGame")
		UPlayerData* GameData;

	void SaveCurrentGameData(FGameLession &data);

	UPlayerData* LoadGameData();

	UPlayerData* LoadCurrentGameData();


protected:
	FString previewStr;
};
