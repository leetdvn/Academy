// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Image.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ULeeLessionShapesData.generated.h"

/**
 * 
 */
UCLASS()
class ACADEMY_API ULeeLessionShapesData : public UDataAsset
{
	GENERATED_BODY()
	
public:

    UPROPERTY(EditAnywhere)
	FString LessionName;

    /**
	Main Image of Lession
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lession Data")
    TSoftObjectPtr<UTexture2D> mainImg;

	/**
	  Animals Shape Images of Lession
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lession Data", meta = (DisplayName = "Animal Shape"))
    TArray<TSoftObjectPtr<UTexture2D>> AnimalImages;

    /**
        Shapes Images of Lession
	*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lession Data", meta = (DisplayName = "Shadow Shape"))
    TArray<TSoftObjectPtr<UTexture2D>> AnimalShapeImages;

};
