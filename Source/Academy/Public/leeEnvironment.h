// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "lee3LinesData.h"
#include "leePublicEnum.h"
#include "leePublicInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "leeEnvironment.generated.h"

/**
 * 
 */
UCLASS()
class ACADEMY_API UleeEnvironment : public Ulee3LinesData
{
	GENERATED_BODY()

public:

	UleeEnvironment(const FObjectInitializer& ObjectInitializer);

	//virtual UleeEnvironment* operator=(Ulee3LinesData* other);

}; 
