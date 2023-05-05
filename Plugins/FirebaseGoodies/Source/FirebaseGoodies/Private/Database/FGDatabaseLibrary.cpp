// Copyright (c) 2022 Nineva Studios

#include "Database/FGDatabaseLibrary.h"

#if PLATFORM_ANDROID
#include "Android/Utils/FGMethodCallUtils.h"
#include "Android/Utils/FGValueVariantUtils.h"
#endif

#if PLATFORM_IOS
#import <FirebaseDatabase/FirebaseDatabase.h>
#include "IOS/Utils/FGValueVariantUtils.h"
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
#include "firebase/database.h"
#include "Desktop/FGVariantUtils.h"
#endif

static const ANSICHAR* FGDatabaseLibraryClassName = "com/ninevastudios/unrealfirebase/FGDatabaseLibrary";

void UFGDatabaseLibrary::GoOffline()
{
#if PLATFORM_ANDROID
	FGMethodCallUtils::CallStaticVoidMethod(FGDatabaseLibraryClassName, "GoOffline", "()V");
#elif PLATFORM_IOS
	[[FIRDatabase database] goOffline];
#elif (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::Database* database = firebase::database::Database::GetInstance(firebase::App::GetInstance());

	database->GoOffline();
#endif
}

void UFGDatabaseLibrary::GoOnline()
{
#if PLATFORM_ANDROID
	FGMethodCallUtils::CallStaticVoidMethod(FGDatabaseLibraryClassName, "GoOnline", "()V");
#elif PLATFORM_IOS
	[[FIRDatabase database] goOnline];
#elif (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::Database* database = firebase::database::Database::GetInstance(firebase::App::GetInstance());

	database->GoOnline();
#endif
}

void UFGDatabaseLibrary::PurgeOutstandingWrites()
{
#if PLATFORM_ANDROID
	FGMethodCallUtils::CallStaticVoidMethod(FGDatabaseLibraryClassName, "PurgeOutstandingWrites", "()V");
#elif PLATFORM_IOS
	[[FIRDatabase database] purgeOutstandingWrites];
#elif (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::Database* database = firebase::database::Database::GetInstance(firebase::App::GetInstance());

	database->PurgeOutstandingWrites();
#endif
}

void UFGDatabaseLibrary::SetPersistenceCacheSizeBytes(int SizeInBytes)
{
#if PLATFORM_ANDROID
	FGMethodCallUtils::CallStaticVoidMethod(FGDatabaseLibraryClassName, "SetPersistenceCacheSizeBytes", "(J)V", (jlong)SizeInBytes);
#elif PLATFORM_IOS
	[FIRDatabase database].persistenceCacheSizeBytes = SizeInBytes;
#endif
}

void UFGDatabaseLibrary::SetPersistenceEnabled(bool bEnabled)
{
#if PLATFORM_ANDROID
	FGMethodCallUtils::CallStaticVoidMethod(FGDatabaseLibraryClassName, "SetPersistenceEnabled", "(Z)V", bEnabled);
#elif PLATFORM_IOS
	[FIRDatabase database].persistenceEnabled = bEnabled;
#elif (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::Database* database = firebase::database::Database::GetInstance(firebase::App::GetInstance());

	database->set_persistence_enabled(bEnabled);
#endif
}

FFGValueVariant UFGDatabaseLibrary::RealtimeDatabaseTimestamp()
{
	FFGValueVariant Result;
#if PLATFORM_ANDROID
	jobject javaTimestamp = FGMethodCallUtils::CallStaticObjectMethod(FGDatabaseLibraryClassName, "Timestamp", "()Ljava/util/HashMap;");

	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	Result = ValueVariantUtils::JavaObjectToVariant(JEnv, javaTimestamp);
#elif PLATFORM_IOS
	Result = ValueVariantUtils::IdToVariant([FIRServerValue timestamp]);
#elif (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	Result = FGVariantUtils::FirebaseVariantToValueVariant(firebase::database::ServerTimestamp());
#endif
	return Result;
}
