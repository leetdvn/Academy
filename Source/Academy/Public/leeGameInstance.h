// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leeUserInfo.h"
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

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Info")
		FString SlotGame;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Slot Info")
		FString SlotInfo;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "SaveGame")
		UPlayerData* GameData;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Player Info")
		UleeUserInfo* PlayerInfo;

	void SaveCurrentGameData(UPlayerData*& data);

	UPlayerData* LoadGameData();

	UPlayerData* GameDataInit();

	UleeUserInfo* LoadPlayerInfo();

	void SaveUserInfo(UleeUserInfo*& info);

protected:
	FString previewStr;

};
