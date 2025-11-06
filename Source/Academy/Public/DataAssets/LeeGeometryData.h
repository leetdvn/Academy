// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LeeGeometryData.generated.h"

/**
 * 
 */
UCLASS()
class ACADEMY_API ULeeGeometryData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString LessionName;
	/**
	title image of lession
	**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lession Data")
	TSoftObjectPtr<UTexture2D> MainImg;

	/****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lession Data")
	TArray<TSoftObjectPtr<UTexture2D>> RandImages;

	/****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lession Data")
	TMap<int32, TSoftObjectPtr<UTexture2D>> Triangles;

	/****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lession Data")
	TMap<int32, TSoftObjectPtr<UTexture2D>> Rectangles;

	/****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lession Data")
	TMap<int32, TSoftObjectPtr<UTexture2D>> Hexagons;

	/****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lession Data")
	TMap<int32, TSoftObjectPtr<UTexture2D>> Circles;

	/****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lession Data")
	TMap<int32, TSoftObjectPtr<UTexture2D>> Hearts;

};
