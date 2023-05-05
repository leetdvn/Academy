// Copyright (c) 2022 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Common/FGValueVariant.h"

#include "FGDatabaseLibrary.generated.h"

UCLASS()
class FIREBASEGOODIES_API UFGDatabaseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Shuts down the connection to the Firebase Database.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Realtime Database")
	static void GoOffline();

	/**
	* Resumes the connection to the Firebase Database.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Realtime Database")
	static void GoOnline();

	/**
	* Abandon all pending writes.
	*/
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Realtime Database")
	static void PurgeOutstandingWrites();


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Firebase Goodies|Realtime Database")
	static FFGValueVariant RealtimeDatabaseTimestamp();

	static void SetPersistenceCacheSizeBytes(int SizeInBytes);
	static void SetPersistenceEnabled(bool bEnabled);
};
