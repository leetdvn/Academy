// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <JsonUtilities/Public/JsonObjectConverter.h>
#include <Engine/DataTable.h>
#include <Components/CanvasPanelSlot.h>
#include <Components/VerticalBoxSlot.h>
#include <Components/ScrollBoxSlot.h>
#include <Components/HorizontalBoxSlot.h>
#include <Components/PanelSlot.h>
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Blueprint/UserWidget.h"
#include "leePublicInterface.generated.h"

#define lDebug(...) lDebugStr(__VA_ARGS__)
#define GAMEDIR 
#define GAMETABLE  "/Game/Stringtable/Games"
#define SETTINGTABLE  "/Game/Stringtable/Settings"
#define HOMETABLE  "/Game/Stringtable/HomeMenu"


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

#pragma region Lee CUSTOM DEBUG
	template<class T>
	void lBaseDebugStr(T message, FColor color = FColor::Red, FString startStr = "");

	void lDebugStr(FString message, FColor color =FColor::Red, FString startStr="");

	void lDebugStr(int message, FColor color = FColor::Red, FString startStr = "");
	
	void lDebugStr(bool& message, FColor color = FColor::Red, FString startStr = "");

	void lDebugStr(FVector vector, FColor color = FColor::Red, FString startStr = "");

	template<class T>
	FORCEINLINE FString ShowScreen(void* info);

#pragma endregion 
	
#pragma region DATA IO JSON
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


	void CreateJSonFile(FString jsFilepath, TSharedPtr<FJsonObject> &obj);

	/// <summary>
	/// Get data type FString from JsonArray
	/// </summary>
	/// <param name="jsObj"></param>
	/// <param name="FieldName"></param>
	/// <returns></returns>
	FORCEINLINE FString lGetStrFromJsArray(TArray<TSharedPtr<FJsonValue>> jsArray, FString FieldName);

	FORCEINLINE TArray <TSharedPtr<FJsonObject>> lGetArrayObjFromObject(TSharedPtr<FJsonObject> InjsObject, FString FieldName);
	/// <summary>
	/// convert JsonObject to String
	/// </summary>
	/// <param name="JsonObject"></param>
	/// <returns></returns>
	FString lJsontoStr(const TSharedPtr<FJsonObject> JsonObject);

	/// <summary>
	/// Get All directory dir form directory
	/// </summary>
	/// <param name="directory"></param>
	/// <returns></returns>
	TArray<FString> lGetAllDirectory(const FString directory, bool isfile = false);

	void lCreateFileFromString(FString content,FString &filepath);

	//void lCreateFileFromString(FString content, FString filepath);


	template<class T>
	T* lGetAssetFromContent(FName referencePath, bool &success);

	template<class T>
	T* lGetAssetFromContent(FString referencePath,bool &success);

	FString FindContentFromPath(FString dir, FString filename);

	FORCEINLINE TArray<FString> lGetAllMapNames();

	FString GameDir = FPaths::ProjectContentDir();

	void lGetRandomFromPath(FString dir, TArray<FString>& OutArray, int32 number);

	/// <summary>
	/// get number files diffirent in the directory
	/// </summary>
	/// <param name="dir"></param>
	/// <param name="exceptions"></param>
	/// <param name="number"></param>
	void lGetRandFilesFromDirectory(FString dir, TArray<FString>& exceptions, int32 number);

	void lGetRandDirsFromDirectory(FString dir, TArray<FString>& exceptions, int32 number);

	FString lGetRandFileFromDirectory(FString dir);

	UTexture2D* lGetTextureFromPath(FString imgPath);
	bool lFilesExists(FString iPath);

	FVector2D lGetSizeTexture(FString imgPath);
	bool lExistsDirectory(FString& dir) {
		FString nDir = GameDir + dir;
		//UE_LOG(LogTemp, Warning, TEXT("dir : %s"), *nDir);
		return FPaths::DirectoryExists(nDir);
	}

	/// <summary>
	/// Create Data Table 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="other"></param>
	/// <param name=""></param>
	/// <param name="savePath"></param>
	/// <param name=""></param>
	/// <returns></returns>
	UDataTable* lCreateDataTableRuntime(FString objName, FString InProjectPath, FString savePath, UScriptStruct* script);


	/// <summary>
	/// Create Runtime Asset , return Package Register out class T
	/// </summary>
	template<class T>
	UPackage* lCreateAssetRuntime(FString objName, FString InProjectPath, FString savePath, T*& OutObject);


#pragma endregion

#pragma region GLOBAL VALUE
	const FVector2D lbaseScreenXY = FVector2D(768, 1024);
	const int lbaseScreenX = 768;
	const int lbaseScreenY = 1024;

#pragma endregion

	float lRand(float min, float max) { return FMath::RandRange(min, max); }

	int32 lRand(int32 min, int32 max) { return FMath::RandRange(min, max-1); }

	int64 lRand(int64 min, int64 max) { return FMath::RandRange(min, max-1); }

	bool isNull(void* ptr, FString message);


	bool lMapExists(FString mapname);

	//FORCEINLINE TArray<FString> RemoveContentFromPath(FString dir, FString filename);

	void lGetRandNums(TArray<int32> &Outnums,int32 maxArray, int32 maxValue);

	void lSetUpdateSizeRules(UPanelSlot* &panelSlot, ESlateSizeRule::Type ruleType);


	//template<typename T>
	//void lDelayFunction(UWorld* world,float delay, T &name);

	//template<class T>
	//T* lExistsWidget(UPanelWidget* Parent, FString& name, bool status = false);

	void ResetMapLevel(UWorld* world);

	int32 lGetEnumFromStr(const FString name,FString enumStr);

	//FString lGetEnumToString(UEnum ipEnum);

#pragma region Animations
	void FillAnimationsMap(TMap<FString, UWidgetAnimation*>& AnimationsMap,UUserWidget* Widget);

#pragma endregion

};
