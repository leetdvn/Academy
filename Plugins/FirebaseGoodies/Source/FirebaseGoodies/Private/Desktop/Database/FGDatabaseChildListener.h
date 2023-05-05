// Copyright (c) 2021 Nineva Studios

#pragma once

#include "firebase/database.h"

#include "Async/Async.h"

#include "Database/FGDatabaseRef.h"

class FGDatabaseChildListener : public firebase::database::ChildListener {
public:

    FOnChildEventDelegate OnChildEventCallback;
    FOnCancelledDelegate OnCancelledCallback;

    virtual void OnChildAdded(const firebase::database::DataSnapshot& snapshot, const char* previous_sibling_key) override
    {
        UFGDataSnapshot* Data = NewObject<UFGDataSnapshot>();
        Data->InitPlatformData(snapshot);
        FString PrevKeyString = previous_sibling_key ? FString(previous_sibling_key) : FString();
        AsyncTask(ENamedThreads::GameThread, [=]() {
            OnChildEventCallback.ExecuteIfBound(EChileEventType::Added, Data, PrevKeyString);
        });
    }

    virtual void OnChildChanged(const firebase::database::DataSnapshot& snapshot, const char* previous_sibling_key) override
    {
        UFGDataSnapshot* Data = NewObject<UFGDataSnapshot>();
        Data->InitPlatformData(snapshot);
        FString PrevKeyString = previous_sibling_key ? FString(previous_sibling_key) : FString();
        AsyncTask(ENamedThreads::GameThread, [=]() {
            OnChildEventCallback.ExecuteIfBound(EChileEventType::Changed, Data, PrevKeyString);
        });
    }

    virtual void OnChildMoved(const firebase::database::DataSnapshot& snapshot, const char* previous_sibling_key) override
    {
        UFGDataSnapshot* Data = NewObject<UFGDataSnapshot>();
        Data->InitPlatformData(snapshot);
        FString PrevKeyString = previous_sibling_key ? FString(previous_sibling_key) : FString();
        AsyncTask(ENamedThreads::GameThread, [=]() {
            OnChildEventCallback.ExecuteIfBound(EChileEventType::Moved, Data, PrevKeyString);
        });
    }

    virtual void OnChildRemoved(const firebase::database::DataSnapshot& snapshot) override
    {
        UFGDataSnapshot* Data = NewObject<UFGDataSnapshot>();
        Data->InitPlatformData(snapshot);

        AsyncTask(ENamedThreads::GameThread, [=]() {
            OnChildEventCallback.ExecuteIfBound(EChileEventType::Added, Data, TEXT(""));
        });
    }

    virtual void OnCancelled(const firebase::database::Error& error, const char* error_message) override
    {
        const FString ErrorMessage(error_message);
        int ErrorCode = (int)error;

        UE_LOG(LogFirebaseGoodies, Error, TEXT("Database operation failed: %s"), *ErrorMessage);
        AsyncTask(ENamedThreads::GameThread, [=]() {
            OnCancelledCallback.ExecuteIfBound(ErrorCode, ErrorMessage);
        });
    }
};