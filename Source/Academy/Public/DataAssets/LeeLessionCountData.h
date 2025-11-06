// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LeeLessionCountData.generated.h"

/**
 * 
 */

USTRUCT()
struct FQuesAns : public FTableRowBase
{
	GENERATED_BODY()

public:
    // Add this include to fix the error
	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<UTexture2D>> QuesAns;
};

UCLASS()
class ACADEMY_API ULeeLessionCountData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	ULeeLessionCountData();

	UPROPERTY(EditAnywhere)
	FString LessionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lession Data")
	TSoftObjectPtr<UTexture2D> mainImg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lession Data")
	TArray<FQuesAns> QuesAnses;


};
