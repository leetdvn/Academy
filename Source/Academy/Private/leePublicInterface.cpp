// Fill out your copyright notice in the Description page of Project Settings.


#include "leePublicInterface.h"
#include <AssetRegistry/AssetRegistryModule.h>
#include "HAL/FileManagerGeneric.h"


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
	auto Writer = TJsonWriterFactory<>::Create(&OutStr);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	return OutStr;
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
			UE_LOG(LogTemp, Warning, TEXT("Found Folder: %s"), *FoundFolders[i]);
		}
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Path does not Exits: %s"), *directory);
	}
	return FoundFolders;
}

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

TArray<FString> IleePublicInterface::FilterContentFromPath(FString dir, int32 number)
{
	//if(ref.Num() != number) {lDebug("") }
	TArray<FString> files = lGetAllDirectory(dir, true), result{};
	for (int i = 0; i < number; i++) {

		int32 rand = lRand(0, files.Num());
		result.Add(files[rand]);
		files.Remove(files[rand]);
	}
	return result;
}

void IleePublicInterface::lGetRandFilesFromDirectory(FString dir, TArray<FString>& exceptions,int32 number)
{
	TArray<FString> files = lGetAllDirectory(dir, true), result{};
	if (files.Num() < number) { lDebug("folder dont' have enoght files"); return; }
	for (auto& f : files) {
		int rand = lRand(0, files.Num());
		if (exceptions.Num() >= number ) return;
		exceptions.AddUnique(files[rand]);
	}

	//if (exceptions.Num() < number - 1) return lGetRandFilesFromDirectory(dir, exceptions, number);
}

void IleePublicInterface::lGetRandNums(TArray<int32>& nums, int length)
{
#pragma omp parallel for
	for (size_t i = 0; i < length; i++)	{
		int32 rand=lRand(0, length);
		if (nums.Num() == length) return;
		nums.AddUnique(rand);
		lDebug(rand);
	}
	if (nums.Num() < length) return lGetRandNums(nums, length);
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

FVector2D IleePublicInterface::lScreenResolution()
{
	FVector2D viewportSize{};
	if (GEngine) {
		GEngine->GameViewport->GetViewportSize(viewportSize);
		return viewportSize;
	}
	return viewportSize;
}

FVector2D IleePublicInterface::lFitResolutons()
{
	FVector2D v2D = lScreenResolution();
	return lScreenResolution() / lbaseScreenXY;
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
