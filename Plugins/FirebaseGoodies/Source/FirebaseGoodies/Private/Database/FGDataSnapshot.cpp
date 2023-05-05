// Copyright (c) 2022 Nineva Studios

#include "Database/FGDataSnapshot.h"

#if PLATFORM_ANDROID
#include "Android/Utils/FGValueVariantUtils.h"
#include "Android/Utils/FGMethodCallUtils.h"
#endif

#if PLATFORM_IOS
#include "IOS/Utils/FGValueVariantUtils.h"

#import <FirebaseDatabase/FirebaseDatabase.h>
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
#include "Desktop/FGVariantUtils.h"
#endif

struct DataSnapshotPlatformData
{
#if PLATFORM_ANDROID
	jobject JDataSnapshot;
	jmethodID GetKeyMethod;
	jmethodID GetPriorityMethod;
	jmethodID GetValueMethod;
	jmethodID ExistsMethod;
	jmethodID ChildMethod;
	jmethodID GetChildrenMethod;
	jmethodID GetChildrenCountMethod;
	jmethodID HasChildMethod;
	jmethodID HasChildrenMethod;
#endif

#if PLATFORM_IOS
	FIRDataSnapshot* DataSnapshot;
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DataSnapshot DataSnapshot;
#endif
};

UFGDataSnapshot::UFGDataSnapshot()
	: PlatformData(MakeShared<DataSnapshotPlatformData>())
{
}

UFGDataSnapshot::~UFGDataSnapshot()
{
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteGlobalRef(PlatformData->JDataSnapshot);
#endif

#if PLATFORM_IOS
	if (PlatformData->DataSnapshot)
		[PlatformData->DataSnapshot release];
#endif
};

#if PLATFORM_ANDROID
void UFGDataSnapshot::InitPlatformData(jobject DataSnapshot)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	PlatformData->JDataSnapshot = Env->NewGlobalRef(DataSnapshot);

	jclass DataSnapshotClass = FAndroidApplication::FindJavaClass("com/ninevastudios/unrealfirebase/FGDataSnapshot");
	PlatformData->GetKeyMethod = FJavaWrapper::FindMethod(Env, DataSnapshotClass, "GetKey", "()Ljava/lang/String;", false);
	PlatformData->GetPriorityMethod = FJavaWrapper::FindMethod(Env, DataSnapshotClass, "GetPriority", "()Ljava/lang/Object;", false);
	PlatformData->GetValueMethod = FJavaWrapper::FindMethod(Env, DataSnapshotClass, "GetValue", "()Ljava/lang/Object;", false);
	PlatformData->ExistsMethod = FJavaWrapper::FindMethod(Env, DataSnapshotClass, "Exists", "()Z", false);
	PlatformData->ChildMethod = FJavaWrapper::FindMethod(Env, DataSnapshotClass, "Child", "(Ljava/lang/String;)Ljava/lang/Object;", false);
	PlatformData->GetChildrenMethod = FJavaWrapper::FindMethod(Env, DataSnapshotClass, "GetChildren", "()Ljava/util/ArrayList;", false);
	PlatformData->GetChildrenCountMethod = FJavaWrapper::FindMethod(Env, DataSnapshotClass, "GetChildrenCount", "()J", false);
	PlatformData->HasChildMethod = FJavaWrapper::FindMethod(Env, DataSnapshotClass, "HasChild", "(Ljava/lang/String;)Z", false);
	PlatformData->HasChildrenMethod = FJavaWrapper::FindMethod(Env, DataSnapshotClass, "HasChildren", "()Z", false);
}
#endif

#if PLATFORM_IOS
void UFGDataSnapshot::InitPlatformData(FIRDataSnapshot* DataSnapshot)
{
	PlatformData->DataSnapshot = DataSnapshot;
}
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
void UFGDataSnapshot::InitPlatformData(firebase::database::DataSnapshot DataSnapshot)
{
	PlatformData->DataSnapshot = DataSnapshot;
}
#endif

FString UFGDataSnapshot::GetKey() const
{
	FString KeyString = "";
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jstring Key = static_cast<jstring>(Env->CallObjectMethod(PlatformData->JDataSnapshot, PlatformData->GetKeyMethod));
	KeyString = FJavaHelper::FStringFromLocalRef(Env, Key);
#endif

#if PLATFORM_IOS
	KeyString = FString([PlatformData->DataSnapshot key]);
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	KeyString = PlatformData->DataSnapshot.key();
#endif

	return KeyString;
}

FFGValueVariant UFGDataSnapshot::GetPriority() const
{
	FFGValueVariant PriorityVariant;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jobject Data = Env->CallObjectMethod(PlatformData->JDataSnapshot, PlatformData->GetPriorityMethod);
	PriorityVariant = ValueVariantUtils::JavaObjectToVariant(Env, Data);
	Env->DeleteLocalRef(Data);
#endif

#if PLATFORM_IOS
	id Priority = [PlatformData->DataSnapshot priority];
	PriorityVariant = ValueVariantUtils::IdToVariant(Priority);
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PriorityVariant = FGVariantUtils::FirebaseVariantToValueVariant(PlatformData->DataSnapshot.priority());
#endif

	return PriorityVariant;
}

FFGValueVariant UFGDataSnapshot::GetValue()
{
	FFGValueVariant ValueVariant;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jobject Data = Env->CallObjectMethod(PlatformData->JDataSnapshot, PlatformData->GetValueMethod);
	ValueVariant = ValueVariantUtils::JavaObjectToVariant(Env, Data);
	Env->DeleteLocalRef(Data);
#endif

#if PLATFORM_IOS
	id Value = [PlatformData->DataSnapshot value];
	ValueVariant = ValueVariantUtils::IdToVariant(Value);
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	ValueVariant = FGVariantUtils::FirebaseVariantToValueVariant(PlatformData->DataSnapshot.value());
#endif

	return ValueVariant;
}

bool UFGDataSnapshot::Exists() const
{
	bool bRet = false;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	bRet = Env->CallBooleanMethod(PlatformData->JDataSnapshot, PlatformData->ExistsMethod);
#endif

#if PLATFORM_IOS
	bRet = [PlatformData->DataSnapshot exists];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	bRet = PlatformData->DataSnapshot.exists();
#endif

	return bRet;
}

UFGDataSnapshot* UFGDataSnapshot::Child(const FString& Path) const
{
	UFGDataSnapshot* Child = NewObject<UFGDataSnapshot>();

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	auto JPath = FJavaClassObject::GetJString(Path);
	jobject JChild = Env->CallObjectMethod(PlatformData->JDataSnapshot, PlatformData->ChildMethod, *JPath);
	Child->InitPlatformData(JChild);
#endif

#if PLATFORM_IOS
	Child->InitPlatformData([PlatformData->DataSnapshot childSnapshotForPath:Path.GetNSString()]);
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	Child->InitPlatformData(PlatformData->DataSnapshot.Child(TCHAR_TO_ANSI(*Path)));
#endif

	return Child;
}

TArray<UFGDataSnapshot*> UFGDataSnapshot::GetChildren() const
{
	TArray<UFGDataSnapshot*> Children;

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass ListClass = FJavaWrapper::FindClass(Env, "java/util/List", false);
	jmethodID SizeMethod = FJavaWrapper::FindMethod(Env, ListClass, "size", "()I", false);
	jmethodID GeteMethod = FJavaWrapper::FindMethod(Env, ListClass, "get", "(I)Ljava/lang/Object;", false);
	jobject JChildren = Env->CallObjectMethod(PlatformData->JDataSnapshot, PlatformData->GetChildrenMethod);

	const int Size = Env->CallIntMethod(JChildren, SizeMethod);

	for (int i = 0; i < Size; i++)
	{
		jobject JChild = Env->CallObjectMethod(JChildren, GeteMethod, i);
		UFGDataSnapshot* Child = NewObject<UFGDataSnapshot>();
		Child->InitPlatformData(JChild);
		Children.Add(Child);
		Env->DeleteLocalRef(JChild);
	}
	Env->DeleteLocalRef(JChildren);
#endif

#if PLATFORM_IOS
	for (FIRDataSnapshot* Child in [PlatformData->DataSnapshot children])
	{
		UFGDataSnapshot* ChildSnapshot = NewObject<UFGDataSnapshot>();
		ChildSnapshot->InitPlatformData([Child retain]);
		Children.Add(ChildSnapshot);
	}
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	for (const auto& child : PlatformData->DataSnapshot.children())
	{
		UFGDataSnapshot* ChildSnapshot = NewObject<UFGDataSnapshot>();
		ChildSnapshot->InitPlatformData(child);
		Children.Add(ChildSnapshot);
	}
#endif

	return Children;
}

int UFGDataSnapshot::GetChildrenCount() const
{
	int Count = 0;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Count = Env->CallLongMethod(PlatformData->JDataSnapshot, PlatformData->GetChildrenCountMethod);
#endif

#if PLATFORM_IOS
	Count = [PlatformData->DataSnapshot childrenCount];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	Count = PlatformData->DataSnapshot.children_count();
#endif

	return Count;
}

bool UFGDataSnapshot::HasChild(const FString& Path) const
{
	bool bRet = false;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	auto JPath = FJavaClassObject::GetJString(Path);
	bRet = Env->CallBooleanMethod(PlatformData->JDataSnapshot, PlatformData->HasChildMethod, *JPath);
#endif

#if PLATFORM_IOS
	bRet = [PlatformData->DataSnapshot hasChild:Path.GetNSString()];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	bRet = PlatformData->DataSnapshot.HasChild(TCHAR_TO_ANSI(*Path));
#endif

	return bRet;
}

bool UFGDataSnapshot::HasChildren() const
{
	bool bRet = false;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	bRet = Env->CallBooleanMethod(PlatformData->JDataSnapshot, PlatformData->HasChildrenMethod);
#endif

#if PLATFORM_IOS
	bRet = [PlatformData->DataSnapshot hasChildren];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	bRet = PlatformData->DataSnapshot.has_children();
#endif

	return bRet;
}
