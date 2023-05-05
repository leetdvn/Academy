// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <AssetRegistry/AssetRegistryModule.h>
#include <Engine/DataTable.h>
#include <JsonUtilities/Public/JsonObjectConverter.h>
#include "HAL/FileManagerGeneric.h"
#include <Kismet/GameplayStatics.h>
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "leeLibraries.generated.h"



#define IINFO(...) IShowScreen(__VA_ARGS__)

template<class T>
T* IGetChacter(UWorld* world,int32 idx) {
	if (!world) return nullptr;
	ACharacter* fCharacter = UGameplayStatics::GetPlayerCharacter(world, idx);
	if (fCharacter)
		return Cast<T>(fCharacter);
	return nullptr;
}

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UleeLibraries : public UInterface
{
	GENERATED_BODY()
};

class LEEULTILITIES_API IleeLibraries
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

#pragma region DEBUG CUSTOM

	template<class T>
	void IBaseDebugStr(T message, FColor color = FColor::Red, FString startStr = "",float TimeDisplay=5);

	void IShowScreen(FString message, FColor color = FColor::Red, FString startStr = "", float TimeDisplay = 5);

	void IShowScreen(const char* message, FColor color = FColor::Red, FString startStr = "", float TimeDisplay = 5);

	void IShowScreen(float message, FColor color = FColor::Red, FString startStr = "", float TimeDisplay = 5);

	void IShowScreen(bool message, FColor color = FColor::Red, FString startStr = "", float TimeDisplay = 5);

	void IShowScreen(FVector message, FColor color = FColor::Red, FString startStr = "", float TimeDisplay = 5);

#pragma endregion

#pragma region File Data IO
	
	//get Texture from path
	//UTexture2D* IGetTextureFromDir(FString &path);

	/* Get Texture from Directory*/
	FORCEINLINE UTexture2D* IGetTextureFromDir(FString path);

	/*	Create file write content save to path	*/
	FORCEINLINE void ICreateFileFromStr(FString content, FString& filepath);

	/*	Create file Json Save to path	*/
	FORCEINLINE void ICreateFileJSon(TSharedPtr<FJsonObject> InjsObject, FString& filepath);

	/*	Convert FJsonObject to FString	*/
	FORCEINLINE FString IConvertJSonToSTr(TSharedPtr<FJsonObject> InjsObject);

	/*	Get return all file or dir from directorys	*/
	FORCEINLINE TArray<FString> IGetAllFileInDir(const FString directory, bool isfile = false);

	/*	Create Asset Runtime Save to project path*/
	template<class T>
	FORCEINLINE UPackage* ICreateAssetRuntime(FString objName, FString InProjectPath, FString savePath, T*& OutObject);

	/*	create data table Runtimes	*/
	UDataTable* ICreateDataTableRuntime(FString objName, FString InProjectPath, FString savePath, UScriptStruct* script);

	/**get Files from Dir*/
	void IGetFilesFromDir(FString dir, TArray<FString>& OutFiles, int32 number,bool isDir=false,FString exception="");

	/**get Random A Single Files from Dir*/
	FString IGetRanDomFileFromDir(FString dir,bool fullpathname);

	/**get Random Multi Files from Dir*/
	void IGetRanDomFilesFromDir(FString dir, TArray<FString>& exceptions, int32 number, FString withoutStr="");

	/*Check File or Directories Exists*/
	bool IExists(FString path, bool isDir = false,bool iGame=false);

	/*Get Asset From Reference*/
	template<class T>
	T* IGetAssetFromRef(FName referenpath,bool &success);

	UTexture2D* IGetTextureFromRef(FName ref);
#pragma endregion


#pragma region RANDOM

	/*return Random float Range from min to max */
	float IRand(float min, float max) { return FMath::RandRange(min, max); }

	/*	return Random interger Range from min to max -1	*/
	int32 IRand(int32 min, int32 max) { return FMath::RandRange(min, max - 1); }

	/*	return Random interger Range from min to max -1	*/
	int64 IRand(int64 min, int64 max) { return FMath::RandRange(min, max - 1); }

	/*	get lists number by recursive functions	*/
	void IGetRandNums(TArray<int32>& Outnums, int32 maxArray, int32 maxValue);

#pragma endregion


#pragma region LeeUltilities 

	/*Convert Path /Game/ To Original Path */
	FString IConvertPathToOriginal(FString& gamePath);

	/*Get AHUB From WORLD*/
	AHUD* IGetHUB(UWorld* world);

	/*Get Enum From FString*/
	template<class T>
	FORCEINLINE T IGetEnumFromStr(const FString NameType, const FString enumStr);
#pragma endregion


#pragma region My Draft
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "abc")
	//	void OnInterRaction();

#pragma endregion

};