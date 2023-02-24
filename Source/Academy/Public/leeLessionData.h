// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "leePublicEnum.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "leeLessionData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ACADEMY_API UleeLessionData : public UDataAsset
{
	GENERATED_BODY()

public:
	UleeLessionData();
	UleeLessionData* operator=(UleeLessionData*& other) { return other = *&ins; };

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Lession ID")
		int lGameID;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "is Completed")
		bool IsCompleted;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Title")
		FString llessiontitle;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Title Decor")
		FString lpathtitleDecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Description")
		FString ldescription;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Background Decor")
		FString lpathbgrDecor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Data Row One")
		TArray<FString> ldatarowone;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Data Row Two")
		TArray<FString> ldatarowtwo;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Data Row Three")
		TArray<FString> ldatarowthree;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Game Type")
		TEnumAsByte<lGameType> lGameType;

	bool isNull() { return lGameID > 0 ? true : false; }

	UleeLessionData* GetInstance() { return ins; }
private:

	static UleeLessionData* ins;
};
