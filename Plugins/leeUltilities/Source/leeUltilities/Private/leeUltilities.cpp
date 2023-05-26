// Copyright Epic Games, Inc. All Rights Reserved.

#include "leeUltilities.h"
#include "CoreMinimal.h"
#include "ISettingsModule.h"


#define LOCTEXT_NAMESPACE "FleeUltilitiesModule"


void FleeUltilitiesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (!SettingsModule) return;

	LeeUltilities = NewObject<UleetdSettings>(GetTransientPackage(), "leetdSettings", RF_Standalone);
	LeeUltilities->AddToRoot();

	// IOS
	SettingsModule->RegisterSettings("Project", "Plugins", "leetdSettings",
		LOCTEXT("leetdSettings", "leeultilities"),
		LOCTEXT("leetdSettings", "Configure leeultilities plugin"),
		LeeUltilities);

}

void FleeUltilitiesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "leeUltis", "leetdSettings");
	}

	if (!GExitPurge)
	{
		// If we're in exit purge, this object has already been destroyed
		LeeUltilities->RemoveFromRoot();
	}
	else
	{
		LeeUltilities = nullptr;
	}

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FleeUltilitiesModule, leeUltilities)