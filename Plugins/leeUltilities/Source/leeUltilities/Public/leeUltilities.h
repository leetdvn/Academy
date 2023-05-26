// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "leetdSettings.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

//class UleetdSettings;

class FleeUltilitiesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static inline FleeUltilitiesModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FleeUltilitiesModule>("leeUltilities");
	}


	UleetdSettings* LeeUltilities;
};
