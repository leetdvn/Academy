// Fill out your copyright notice in the Description page of Project Settings.


#include "leePublicInterface.h"
#include <AssetRegistry/AssetRegistryModule.h>
#include "HAL/FileManagerGeneric.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/UserWidget.h>

// Add default functionality here for any IleeInterface functions that are not pure virtual.

template<class T>
inline void IleePublicInterface::lBaseDebugStr(T message, FColor color, FString startStr)
{
	TArray< FStringFormatArg > args;
	if (!startStr.IsEmpty())
		args.Add(FStringFormatArg(startStr));
	else {
		args.Add(FStringFormatArg("lee Debug"));
	}
	args.Add(message);
	FString logInfo = FString::Format(TEXT("{0} : {1}"), args);

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			-1,
			3,
			color,
			*logInfo
		);
	}
}

template<class T>
FString IleePublicInterface::ShowScreen(void* info)
{
	FString jsFilePath = *(T*)info;
	//leeTdDebug(jsFilePath);
	TSharedPtr<FJsonObject> result = lGetJsObjectFromFile(jsFilePath);
	TArray<TSharedPtr<FJsonValue>> Array = result->GetArrayField("dataAttrs");
	FString mStr = lGetStrFromJsArray(Array, "cbAttr0");
	//leeTdDebug(mStr);
	FString log = lJsontoStr(result);
	//leeTdDebug(log);
	return FString();
}

template<class T>
T* IleePublicInterface::lGetAssetFromContent(FName referencePath, bool& success)
{
	FStringAssetReference MyAssetPath(referencePath);
	UObject* MyAsset = MyAssetPath.TryLoad();
	T* result = Cast<T>(MyAsset);
	if (result) success = true;
	return result;
}

template<class T>
T* IleePublicInterface::lGetAssetFromContent(FString referencePath, bool& success)
{
	return lGetAssetFromContent<T>(FName(*referencePath),success);
}

template<class T>
UPackage* IleePublicInterface::lCreateAssetRuntime(FString objName, FString InProjectPath, FString savePath,T*&OutObject)
{
	//create Package
	UPackage* Package=CreatePackage(*InProjectPath);
	//asset type of Package
	T* TestAsset = NewObject<T>(Package, T::StaticClass(), *objName, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone);
	OutObject = TestAsset;
	//register Asset
	FAssetRegistryModule::AssetCreated(TestAsset);

	//out log debug
	FString FilePath = FString::Printf(TEXT("%s%s%s"), *savePath, *objName, *FPackageName::GetAssetPackageExtension());
	UE_LOG(LogTemp, Warning, TEXT("Saved Package: %s"),*FilePath);
	return Package;

}

void IleePublicInterface::lDebugStr(FString message, FColor color, FString startStr)
{
	return lBaseDebugStr<FString>(message, color, startStr);
}

void IleePublicInterface::lDebugStr(int message, FColor color, FString startStr)
{
	return lBaseDebugStr<int>(message, color, startStr);
}

void IleePublicInterface::lDebugStr(bool& message, FColor color, FString startStr)
{
	return lBaseDebugStr<bool>(message, color, startStr);
}

void IleePublicInterface::lDebugStr(FVector vector, FColor color, FString startStr)
{
	return lBaseDebugStr<FString>(vector.ToString(), color, startStr);
}

FString IleePublicInterface::lGetStrFromJsonFile(FString jsFilePath)
{
	FString data;
	if (jsFilePath.IsEmpty()) return data;
	FFileHelper::LoadFileToString(data, *jsFilePath);
	return data;
}

TSharedPtr<FJsonObject> IleePublicInterface::lGetJsObjectFromFile(FString jsFilePath)
{
	if (jsFilePath.IsEmpty()) {
		lDebug(FString("file is empty : " + jsFilePath));
		return TSharedPtr<FJsonObject>();
	}

	FString data;
	TSharedPtr<FJsonObject> obj;
	FFileHelper::LoadFileToString(data, *jsFilePath);
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(data);
	bool Success = FJsonSerializer::Deserialize(Reader, obj);

	lDebug(Success);
	return obj;
}

void IleePublicInterface::CreateJSonFile(FString jsFilepath, TSharedPtr<FJsonObject>& obj)
{
	FString data;
	//create file
	//FFileHelper::SaveStringToFile(jsFilepath, *jsFilepath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Silent);
	//FFileManagerGeneric* file = new FFileManagerGeneric();
	//file->CreateFileWriter(*jsFilepath);

	//write to file
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(& jsFilepath);
	bool Success = FJsonSerializer::Serialize(obj.ToSharedRef(), Writer);

	if (Success) {
		lDebug("Json Created.");

	}
	else {
		lDebug("Json Failures");
	}
}

FString IleePublicInterface::lGetStrFromJsArray(TArray<TSharedPtr<FJsonValue>> jsArray, FString FieldName)
{
	if (jsArray.Num() <=0 || jsArray.Num() <= 0) return FString();
	FString OutStr;

#pragma omp parallel for
	for (int i = 0; i < jsArray.Num(); i++) {
		TSharedPtr<FJsonObject> obj = jsArray[i]->AsObject();
		if (obj->TryGetStringField(FieldName, OutStr))
			return OutStr;
	}
	return FString();
}

FString IleePublicInterface::lJsontoStr(const TSharedPtr<FJsonObject> JsonObject)
{
	FString OutStr;
	if (!JsonObject) return FString();
	auto Writer = TJsonWriterFactory<TCHAR,TPrettyJsonPrintPolicy<TCHAR>>::Create(&OutStr);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	return OutStr;
}

TArray <TSharedPtr<FJsonObject>> IleePublicInterface::lGetArrayObjFromObject(TSharedPtr<FJsonObject> InjsObject, FString FieldName)
{
	TArray <TSharedPtr<FJsonObject>> obj;
	for (auto& js : InjsObject->GetArrayField(FieldName)) {
		if (js) {
			obj.Add(js->AsObject());
			lDebug(js->AsString());
		}
	}
	return obj;
}

TArray<FString> IleePublicInterface::lGetAllDirectory(const FString directory,bool isfile)
{
	//FString templatepath = "C:/UEProjects/KidAcademy/Content/AcademyAssets";
	TArray<FString> FoundFolders, temp;
	if (FPaths::DirectoryExists(directory)) {
		FFileManagerGeneric::Get().FindFilesRecursive(FoundFolders, *directory, TEXT("*"), isfile, !isfile, true);
		for (int i = 0; i < FoundFolders.Num(); i++)
		{
			FoundFolders[i].ParseIntoArray(temp, TEXT("/"), true);
			FoundFolders[i] = temp[temp.Num()-1];
			if (isfile) {
				FoundFolders[i].ParseIntoArray(temp, TEXT("."), true);
				FoundFolders[i] = temp[0];
			}
			//UE_LOG(LogTemp, Warning, TEXT("Found Folder: %s"), *FoundFolders[i]);
		}
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Path does not Exits: %s"), *directory);
	}
	return FoundFolders;
}

void IleePublicInterface::lCreateFileFromString(FString content, FString & filepath)
{
	//TSharedPtr<FJsonObject> JsObject = MakeShareable(new FJsonObject());
	/*TSharedPtr<FJsonObject> JsObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&filepath, 0);
	bool succes = FJsonSerializer::Serialize(JsObject.ToSharedRef(), FPrettyJsonStringWriterFactory::Create(&filepath,0));
	if (succes) lDebug(" success");*/
	FFileHelper::SaveStringToFile(content, *filepath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Silent);
	//TSharedRef< FPrettyJsonStringWriter > Writer = FPrettyJsonStringWriterFactory::Create(&filepath);
}

//void IleePublicInterface::lCreateFileFromString(FString content, FString filepath)
//{
//	FFileHelper::SaveStringToFile(content, *filepath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Silent);
//
//}

bool IleePublicInterface::isNull(void* ptr, FString message)
{
	if (ptr) {
		return true;
	}
	lDebug(message);
	return false;
}

FString IleePublicInterface::FindContentFromPath(FString dir, FString filename)
{
	TArray<FString> files = lGetAllDirectory(dir, true);
	for (auto &f : files)
	{
		if (f.EndsWith(filename)) {
			return f;
		}
	}
	return FString();
}

void IleePublicInterface::lGetRandomFromPath(FString dir, TArray<FString>& OutArray, int32 number)
{
	//if(ref.Num() != number) {lDebug("") }
	TArray<FString> files = lGetAllDirectory(dir, true), result{};
	for (int i = 0; i < number; i++) {
		if (OutArray.Num() >= number) return;
		int32 rand = lRand(0, files.Num());
		result.AddUnique(files[rand]);
	}
	if (result.Num() < number) return lGetRandomFromPath(dir, OutArray,number);
}

void IleePublicInterface::lGetRandFilesFromDirectory(FString dir, TArray<FString>& exceptions,int32 number)
{
	TArray<FString> files = lGetAllDirectory(dir, true);
	if (files.Num() < number) { lDebug("folder dont' have enoght files"); return; }
	for (auto& f : files) {
		int rand = lRand(0, files.Num());
		if (exceptions.Num() >= number ) return;
		exceptions.AddUnique(files[rand]);
	}

	if (exceptions.Num() < number) return lGetRandFilesFromDirectory(dir, exceptions, number);
}

void IleePublicInterface::lGetRandDirsFromDirectory(FString dir, TArray<FString>& exceptions, int32 number)
{
	TArray<FString> files = lGetAllDirectory(dir);
	if (files.Num() < number) { lDebug("folder dont' have enoght files"); return; }
	for (auto& f : files) {
		int rand = lRand(0, files.Num());
		if (exceptions.Num() >= number) return;
		exceptions.AddUnique(files[rand]);
	}

	if (exceptions.Num() < number) return lGetRandDirsFromDirectory(dir, exceptions, number);
}

void IleePublicInterface::lGetRandNums(TArray<int32>& Outnums, int32 maxArray, int32 maxValue)
{
#pragma omp parallel for
	for (size_t i = 0; i < maxArray; i++)	{
		int32 rand=lRand(1, maxValue);
		if (Outnums.Num() == maxArray) return;
		Outnums.AddUnique(rand);
		//lDebug(rand);
	}
	if (Outnums.Num() < maxArray) return lGetRandNums(Outnums, maxArray,maxValue);
}

UTexture2D* IleePublicInterface::lGetTextureFromPath(FString imgPath)
{
	if (imgPath.IsEmpty()) return nullptr;
	UTexture2D* tex = LoadObject<UTexture2D>(nullptr, *imgPath);
	if (tex) return tex;

	lDebug("texture loading fail");
	return nullptr;
}

bool IleePublicInterface::lFilesExists(FString iPath)
{
	FString path = FPaths::ProjectContentDir() + iPath;

	return FPaths::FileExists(path);
}

FVector2D IleePublicInterface::lGetSizeTexture(FString imgPath)
{
	FVector2D v2d{};
	if (imgPath.IsEmpty()) return v2d;
	UTexture2D* tex = lGetTextureFromPath(imgPath);
	v2d.X = tex->GetSizeX();
	v2d.Y = tex->GetSizeY();
	return v2d;

}

void IleePublicInterface::lSetUpdateSizeRules(UPanelSlot*&panelSlot, ESlateSizeRule::Type ruleType)
{
	if (panelSlot == nullptr) return;

	FString slotName = panelSlot->GetClass()->GetName();
	if (slotName.StartsWith("Vertical"))
	{
		//lDebug("Vertical..Slot..");
		UVerticalBoxSlot* panel = Cast<UVerticalBoxSlot>(panelSlot);
		if (panel) {
			FSlateChildSize cSize = panel->Size;
			cSize.SizeRule = ruleType;
			panel->SetSize(cSize);
		}
	}
	else if (slotName.StartsWith("Horizontal"))
	{
		//lDebug("Horizontal..Slot..");
		UHorizontalBoxSlot* panel = Cast<UHorizontalBoxSlot>(panelSlot);
		if (panel) {

			FSlateChildSize cSize = panel->Size;
			cSize.SizeRule = ruleType;
			panel->SetSize(cSize);
		}

	}
	else {
		//lDebug("Support Only Vertical Panel and Horizontal Panel.");
	}
}

FString IleePublicInterface::lGetRandFileFromDirectory(FString dir)
{
	TArray<FString> files = lGetAllDirectory(dir, true);
	int32 rand = lRand(0, files.Num());
	if (files.Num() > 0) return files[rand];
	lDebug(" file is zero");
	return "";
}

UDataTable* IleePublicInterface::lCreateDataTableRuntime(FString objName, FString InProjectPath, FString savePath, UScriptStruct* script)
{
	//example Path
	//FString AssetPath = FPaths::ProjectContentDir() + "Data/TestingAsset.uasset";
	//FString PackagePath = FString("/Game/Data/TestingAsset");

	//--------------------------------
	UDataTable* TestAsset{};
	UPackage* Package =lCreateAssetRuntime<UDataTable>(objName, InProjectPath, savePath, TestAsset);
	TestAsset->RowStruct = script;
	bool bSuccess = UPackage::SavePackage(Package, nullptr, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *savePath, GError, nullptr, false, true, ESaveFlags::SAVE_NoError);

	return TestAsset;
}

bool IleePublicInterface::lMapExists(FString mapname)
{
#pragma omp parallel for
	for (auto map : lGetAllMapNames())
		if (map == mapname) return true;
	return false;
}

TArray<FString> IleePublicInterface::lGetAllMapNames()
{
	TArray<FString> temp, Lista;
	IFileManager::Get().FindFilesRecursive(Lista, *FPaths::ProjectContentDir(), TEXT("*.umap"), true, false, false);
	for (int i = 0; i < Lista.Num(); i++) {
		Lista[i].ParseIntoArray(temp, TEXT("Maps/"), true);
		Lista[i] = temp[1];
		Lista[i].ParseIntoArray(temp, TEXT("."), true);
		Lista[i] = temp[0];
	}
	return Lista;
}

//template<typename T>
//void IleePublicInterface::lDelayFunction(UWorld*world, float delay, T& name) {
//	FTimerHandle timer;
//	if (world) {
//		world->GetTimerManager().SetTimer(timer, name, false, delay);
//	}
//}

//template<class T>
//T* IleePublicInterface::lExistsWidget(UPanelWidget* Parent, FString& name, bool status)
//{
//	//check file exits
//	bool Success{};
//	TArray<UWidget*> widgets = Parent->GetAllChildren();
//	if (widgets.Num() <= 0) return nullptr;
//
//	//loop find
//#pragma omp parallel for
//	for (auto wd : widgets) {
//		FString wName = wd->GetFName().ToString();
//		if (wName == name) { return Cast<T>(wd); }
//		UPanelWidget* box = Cast<UPanelWidget>(wd);
//
//		if (box) {
//			Success = lExistsWidget<T>(box, name, status);
//			if (Success) { return nullptr; }
//
//		}
//	}
//	return nullptr;
//}

void IleePublicInterface::ResetMapLevel(UWorld* world) {

	FString map = UGameplayStatics::GetCurrentLevelName(world);
	return UGameplayStatics::OpenLevel(world, FName(*map));
}

//int32  IleePublicInterface::lGetEnumFromStr(const FString name, FString enumStr) {
//	const UEnum* iEnum = FindObject<UEnum>(ANY_PACKAGE, *name, true);
//	if (iEnum) {
//		int32 Index = iEnum->GetIndexByName(*enumStr);
//		return Index;
//	}
//	return 0;
//
//}

#pragma region Animations

void IleePublicInterface::FillAnimationsMap(TMap<FString, UWidgetAnimation*>& AnimationsMap, UUserWidget* Widget)
{
	
	//UWidgetBlueprintGeneratedClass* WidgetClass = Widget->GetWidgetTreeOwningClass();

	//AnimationsMap.Empty();

	//for (int i = 0; i < WidgetClass->Animations.Num(); i++) {

	//	FString Name = WidgetClass->Animations[i]->GetDisplayName().ToString();
	//	AnimationsMap.Add(Name, WidgetClass->Animations[i]);
	//}

	//if (WidgetClass->Animations[0] != NULL) {

	//	UE_LOG(LogTemp, Warning, TEXT("Yes,this is Name is = %s"), *WidgetClass->Animations[0]->GetName());
	//}
	//else {

	//	UE_LOG(LogTemp, Warning, TEXT("aa"));
	//}
}
#pragma endregion
