// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "leePublicInterface.generated.h"

#define lDebug(...) lDebugStr(__VA_ARGS__)


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCorrectDrop, FString, ShapeName);


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UleePublicInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACADEMY_API IleePublicInterface
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	FORCEINLINE TArray<FString> lGetAllMapNames();

	bool lMapExists(FString mapname);

	template<class T>
	void lBaseDebugStr(T message, FColor color = FColor::Red, FString startStr = "");

	void lDebugStr(FString message, FColor color =FColor::Red, FString startStr="");

	void lDebugStr(int message, FColor color = FColor::Red, FString startStr = "");
	
	void lDebugStr(bool& message, FColor color = FColor::Red, FString startStr = "");

	void lDebugStr(FVector vector, FColor color = FColor::Red, FString startStr = "");

	template<class T>
	FORCEINLINE FString ShowScreen(void* info);

	/// <summary>
	/// get FString from Json file
	/// </summary>
	/// <param name="jsFilePath"></param>
	/// <returns></returns>
	FORCEINLINE FString lGetStrFromJsonFile(FString jsFilePath);

	/// <summary>
	/// Read Json file From File Path
	/// </summary>
	/// <param name="jsFilePath"></param>
	/// <returns></returns>
	FORCEINLINE TSharedPtr<FJsonObject> lGetJsObjectFromFile(FString jsFilePath);

	/// <summary>
	/// Get data type FString from JsonArray
	/// </summary>
	/// <param name="jsObj"></param>
	/// <param name="FieldName"></param>
	/// <returns></returns>
	FORCEINLINE FString lGetStrFromJsArray(TArray<TSharedPtr<FJsonValue>> jsArray, FString FieldName);

	/// <summary>
	/// convert JsonObject to String
	/// </summary>
	/// <param name="JsonObject"></param>
	/// <returns></returns>
	FORCEINLINE FString lJsontoStr(const TSharedPtr<FJsonObject> JsonObject);

	/// <summary>
	/// Get All directory dir form directory
	/// </summary>
	/// <param name="directory"></param>
	/// <returns></returns>
	FORCEINLINE TArray<FString> lGetAllDirectory(const FString directory, bool isfile = false);

	template<class T>
	FORCEINLINE T* lGetAssetFromContent(FName referencePath, bool &success);

	template<class T>
	FORCEINLINE T* lGetAssetFromContent(FString referencePath,bool &success);

	FORCEINLINE float lRand(float min, float max) { return FMath::RandRange(min, max); }

	FORCEINLINE int32 lRand(int32 min, int32 max) { return FMath::RandRange(min, max-1); }

	FORCEINLINE int64 lRand(int64 min, int64 max) { return FMath::RandRange(min, max-1); }

	FORCEINLINE bool isNull(void* ptr, FString message);

	FORCEINLINE FString FindContentFromPath(FString dir, FString filename);

	//FORCEINLINE TArray<FString> RemoveContentFromPath(FString dir, FString filename);

	FORCEINLINE TArray<FString> FilterContentFromPath(FString dir, int32 number) ;

	/// <summary>
	/// get number files diffirent in the directory
	/// </summary>
	/// <param name="dir"></param>
	/// <param name="exceptions"></param>
	/// <param name="number"></param>
	FORCEINLINE void lGetRandFilesFromDirectory(FString dir, TArray<FString> &exceptions,int32 number);

	FORCEINLINE void lGetRandNums(TArray<int32> &nums,int length);

};
