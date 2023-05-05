// Copyright (c) 2022 Nineva Studios

#include "FirebaseSubsystem.h"

#include "FirebaseGoodies.h"
#include "FirebaseGoodiesSettings.h"
#include "Database/FGDatabaseLibrary.h"

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
#include "firebase/app.h"
#include "firebase/analytics.h"
#include "firebase/messaging.h"

#include "FirebaseGoodiesLog.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"

#include "Desktop/Messaging/FGMessagingListener.h"
#endif


void UFirebaseSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UFirebaseGoodiesSettings* Settings = FFirebaseGoodiesModule::Get().GetSettings();

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT

	FFilePath Path;

	if(Settings->bUseGoogleServicesJsonForDesktop)
	{
		Path = Settings->bIsGoogleServicesJsonInThePluginRootFolder
			? FFilePath { FPaths::Combine(FFirebaseGoodiesModule::Get().GetPluginDirAbsPath(), TEXT("Source/FirebaseGoodies/google-services.json")) }
			: Settings->GoogleServicesJsonPath;
	}
	else
	{
		Path = Settings->GoogleServicesPlistPath;
	}

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	const FString FilePath = Path.FilePath;

	if (!FileManager.FileExists(*FilePath)) {
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Please, provide the correct path to the google-services.json or GoogleServices.plist file in the Plugin Settings."));
		return;
	}

	FString FileName, DirectoryPath;
	if (FilePath.Split("/", &DirectoryPath, &FileName, ESearchCase::IgnoreCase, ESearchDir::FromEnd))
	{
		UE_LOG(LogFirebaseGoodies, Verbose, TEXT("Directory path: %s"), *DirectoryPath);
		firebase::App::SetDefaultConfigPath(TCHAR_TO_ANSI(*DirectoryPath));
	}
	else
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Could not split the file path."));
		return;
	}

	const firebase::App* App = firebase::App::Create();

	firebase::analytics::Initialize(*App);

	FGMessagingListener* Listener = new FGMessagingListener();
	firebase::messaging::Initialize(*App, Listener);
#endif

	UFGDatabaseLibrary::SetPersistenceEnabled(Settings->bIsPersistenceEnabled);
	UFGDatabaseLibrary::SetPersistenceCacheSizeBytes(Settings->DatabaseCacheSize * 1024);
}

bool UFirebaseSubsystem::IsAppValid() const
{
#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	return firebase::App::GetInstance() != nullptr;
#else
	return true;
#endif
}
