#include "leeLibraries.h"

// Add default functionality here for any IMyInterface functions that are not pure virtual.

void IleeLibraries::IShowScreen(FString message, FColor color, FString startStr, float TimeDisplay)
{
	return IBaseDebugStr<FString>(message, color, startStr, TimeDisplay);
}

void IleeLibraries::IShowScreen(const char* message, FColor color, FString startStr, float TimeDisplay)
{
	IBaseDebugStr<FString>(message, color, startStr, TimeDisplay);
}

void IleeLibraries::IShowScreen(float message, FColor color, FString startStr, float TimeDisplay)
{
	return IBaseDebugStr<float>(message, color, startStr, TimeDisplay);

}

void IleeLibraries::IShowScreen(bool message, FColor color, FString startStr, float TimeDisplay)
{
	return IBaseDebugStr<bool>(message, color, startStr, TimeDisplay);
}

void IleeLibraries::IShowScreen(FVector message, FColor color, FString startStr, float TimeDisplay)
{
	return IBaseDebugStr<FString>(message.ToString(), color, startStr, TimeDisplay);

}

inline UTexture2D* IleeLibraries::IGetTextureFromDir(FString path)
{
	if (path.IsEmpty()) return nullptr;
	UTexture2D* tex = LoadObject<UTexture2D>(nullptr, *path);
	if (tex) return tex;
	return nullptr;
}

inline void IleeLibraries::ICreateFileFromStr(FString content, FString& filepath)
{
	 FFileHelper::SaveStringToFile(content, *filepath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Silent);
}

inline void IleeLibraries::ICreateFileJSon(TSharedPtr<FJsonObject> InjsObject, FString& filepath)
{
	FString JSonStr = IConvertJSonToSTr(InjsObject);
	ICreateFileFromStr(JSonStr, filepath);
}

inline FString IleeLibraries::IConvertJSonToSTr(TSharedPtr<FJsonObject> InjsObject)
{
	FString OutStr;
	if (!InjsObject) return FString();
	auto Writer = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&OutStr);
	FJsonSerializer::Serialize(InjsObject.ToSharedRef(), Writer);
	return OutStr;
}

inline TArray<FString> IleeLibraries::IGetAllFileInDir(const FString directory, bool isfile)
{
	TArray<FString> FoundFolders, temp;
	if (FPaths::DirectoryExists(directory)) {
		FFileManagerGeneric::Get().FindFilesRecursive(FoundFolders, *directory, TEXT("*"), isfile, !isfile, true);
		for (int i = 0; i < FoundFolders.Num(); i++)
		{
			FoundFolders[i].ParseIntoArray(temp, TEXT("/"), true);
			FoundFolders[i] = temp[temp.Num() - 1];
			if (isfile) {
				FoundFolders[i].ParseIntoArray(temp, TEXT("."), true);
				FoundFolders[i] = temp[0];
			}
			//UE_LOG(LogTemp, Warning, TEXT("Found Folder: %s"), *FoundFolders[i]);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Path does not Exits: %s"), *directory);
	}
	return FoundFolders;
}

UDataTable* IleeLibraries::ICreateDataTableRuntime(FString objName, FString InProjectPath, FString savePath, UScriptStruct* script)
{
	//example Path
	//FString AssetPath = FPaths::ProjectContentDir() + "Data/TestingAsset.uasset";
	//FString PackagePath = FString("/Game/Data/TestingAsset");

	//--------------------------------
	UDataTable* TestAsset{};
	UPackage* Package = ICreateAssetRuntime<UDataTable>(objName, InProjectPath, savePath, TestAsset);
	TestAsset->RowStruct = script;
	bool bSuccess = UPackage::SavePackage(Package, nullptr, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *savePath, GError, nullptr, false, true, ESaveFlags::SAVE_NoError);

	return TestAsset;
}

void IleeLibraries::IGetFilesFromDir(FString dir, TArray<FString>& OutFiles, int32 number, bool isDir, FString exception)
{
	TArray<FString> files = IGetAllFileInDir(dir, isDir);
	if (files.Num() < number) { IINFO("folder dont' have enoght files"); return; }
	for (auto& f : files) {
		if (OutFiles.Num() >= number) return;
		int rand = IRand(0, files.Num());
		if (files[rand].Left(exception.Len()) == exception) continue;
		OutFiles.AddUnique(files[rand]);
	}

	if (OutFiles.Num() < number) return IGetFilesFromDir(dir, OutFiles, number,isDir,exception);

}

FString IleeLibraries::IGetRanDomFileFromDir(FString dir, bool fullpathname)
{
	TArray<FString> files = IGetAllFileInDir(dir, true);
	int32 rand = IRand(0, files.Num());
	if (files.Num() > 0) return fullpathname ? dir + "/" + files[rand] : files[rand];
	return FString();
}

void IleeLibraries::IGetRanDomFilesFromDir(FString dir, TArray<FString>& exceptions, int32 number, FString withoutStr)
{
	TArray<FString> files = IGetAllFileInDir(dir, true);
	if (files.Num() < number) { IINFO("folder dont' have enoght files"); return; }
	for (auto& f : files) {
		int rand = IRand(0, files.Num());
		if (exceptions.Num() >= number) return;
		if (files[rand].Left(withoutStr.Len()) == withoutStr) {
			//UE_LOG(LogTemp, Warning, TEXT(" 1 : %s \n 2 : %s "), *f.Left(withoutStr.Len()), *withoutStr);
			continue;
		}
		exceptions.AddUnique(files[rand]);
	}

	if (exceptions.Num() < number) return IGetRanDomFilesFromDir(dir, exceptions, number, withoutStr);
}

bool IleeLibraries::IExists(FString path, bool isDir, bool iGame)
{
	if (path.IsEmpty()) return false;
	FString pjDir{}, filepath{};
	
	pjDir = FPaths::ProjectContentDir();
	if (iGame) {
		filepath = isDir ?
			path.Replace(TEXT("/Game/"), *pjDir) :
			path.Replace(TEXT("/Game/"), *pjDir) + ".uasset";
	}
	else {
		filepath = path;
	}

	return isDir ? FPaths::DirectoryExists(filepath) : FPaths::FileExists(filepath);
}

UTexture2D* IleeLibraries::IGetTextureFromRef(FName ref)
{
	 bool success{};
	 UTexture2D* tex = IGetAssetFromRef<UTexture2D>(ref, success);
	 return success ? tex : nullptr;
}

void IleeLibraries::IGetRandNums(TArray<int32>& Outnums, int32 maxArray, int32 maxValue)
{
#pragma omp parallel for
	for (size_t i = 0; i < maxArray; i++) {
		int32 rand = IRand(1, maxValue);
		if (Outnums.Num() == maxArray) return;
		Outnums.AddUnique(rand);
	}
	if (Outnums.Num() < maxArray) return IGetRandNums(Outnums, maxArray, maxValue);
}

FString IleeLibraries::IConvertPathToOriginal(FString& gamePath)
{
	if (gamePath.IsEmpty() || !gamePath.StartsWith(TEXT("/Game/"))) return gamePath;

	return gamePath.Replace(TEXT("/Game/"), *FPaths::ProjectContentDir());
}

AHUD* IleeLibraries::IGetHUB(UWorld* world)
{
	if (!world) return nullptr;
	return world->GetFirstPlayerController()->GetHUD();
}

template<class T>
inline void IleeLibraries::IBaseDebugStr(T message, FColor color, FString startStr, float TimeDisplay)
{
	TArray< FStringFormatArg > args;
	if (!startStr.IsEmpty())
		args.Add(FStringFormatArg(startStr));
	else {
		args.Add(FStringFormatArg("Infolee :"));
	}
	args.Add(message);
	FString logInfo = FString::Format(TEXT("{0} : {1}"), args);

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			-1,
			TimeDisplay,
			color,
			*logInfo
		);
	}

}

template<class T>
inline UPackage* IleeLibraries::ICreateAssetRuntime(FString objName, FString InProjectPath, FString savePath, T*& OutObject) {
	
	//example Path
	//FString AssetPath = FPaths::ProjectContentDir() + "Data/TestingAsset.uasset";
	//FString PackagePath = FString("/Game/Data/TestingAsset");

	//create Package
	UPackage* Package = CreatePackage(*InProjectPath);
	//asset type of Package
	T* TestAsset = NewObject<T>(Package, T::StaticClass(), *objName, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone);
	OutObject = TestAsset;
	//register Asset
	FAssetRegistryModule::AssetCreated(TestAsset);

	//out log debug
	FString FilePath = FString::Printf(TEXT("%s%s%s"), *savePath, *objName, *FPackageName::GetAssetPackageExtension());
	UE_LOG(LogTemp, Warning, TEXT("Saved Package: %s"), *FilePath);
	return Package;
}

template<class T>
T* IleeLibraries::IGetAssetFromRef(FName referenpath, bool& success)
{
	FStringAssetReference MyAssetPath(referenpath);
	UObject* MyAsset = MyAssetPath.TryLoad();
	T* result = Cast<T>(MyAsset);
	success = result ? true : false ;
	return result;
}

template<class T>
T IleeLibraries::IGetEnumFromStr(const FString NameType, const FString enumStr)
{
	T result{};
	const UEnum* iEnum = FindObject<UEnum>(ANY_PACKAGE, *NameType, true);
	if (iEnum) {
		int32 Index = iEnum->GetIndexByName(*enumStr);
		result = TEnumAsByte<T>((uint8)Index);
		return result;
	}
	return result;
}
