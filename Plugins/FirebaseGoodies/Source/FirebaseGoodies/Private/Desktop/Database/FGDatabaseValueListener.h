// Copyright (c) 2021 Nineva Studios

#pragma once

#include "firebase/database.h"

#include "Async/Async.h"

#include "Database/FGDatabaseRef.h"

class FGDatabaseValueListener : public firebase::database::ValueListener {
public:
	FOnDataChangedDelegate OnValueChangedDelegate;
	FOnCancelledDelegate OnCancelledDelegate;

	virtual void OnValueChanged(const firebase::database::DataSnapshot& snapshot) override
	{
		UFGDataSnapshot* Data = NewObject<UFGDataSnapshot>();
		Data->InitPlatformData(snapshot);

		AsyncTask(ENamedThreads::GameThread, [=]() {
			OnValueChangedDelegate.ExecuteIfBound(Data);
		});
	};

	virtual void OnCancelled(const firebase::database::Error& error, const char* error_message) override
	{
		const FString ErrorMessage(error_message);
		int ErrorCode = (int) error;

		UE_LOG(LogFirebaseGoodies, Error, TEXT("Database operation failed: %s"), *ErrorMessage);
		AsyncTask(ENamedThreads::GameThread, [=]() {
			OnCancelledDelegate.ExecuteIfBound(ErrorCode, ErrorMessage);
		});
	};
};