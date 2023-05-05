// Copyright (c) 2022 Nineva Studios

#include "Database/FGMutableData.h"

#include "FirebaseGoodiesLog.h"

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

struct MutableDataPlatformData
{
#if PLATFORM_ANDROID
	jobject JMutableData;
	jmethodID GetKeyMethod;
	jmethodID GetPriorityMethod;
	jmethodID SetPriorityMethod;
	jmethodID GetValueMethod;
	jmethodID SetValueMethod;
	jmethodID ChildMethod;
	jmethodID GetChildrenMethod;
	jmethodID GetChildrenCountMethod;
	jmethodID HasChildMethod;
	jmethodID HasChildrenMethod;
#endif

#if PLATFORM_IOS
	FIRMutableData* MutableData;
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::MutableData* MutableData;
#endif
};

UFGMutableData::UFGMutableData()
	: PlatformData(MakeShared<MutableDataPlatformData>())
{
}

UFGMutableData::~UFGMutableData()
{
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteGlobalRef(PlatformData->JMutableData);
#endif

#if PLATFORM_IOS
	if (PlatformData->MutableData)
		[PlatformData->MutableData release];
#endif
};

#if PLATFORM_ANDROID
void UFGMutableData::InitPlatformData(jobject MutableData)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	PlatformData->JMutableData = Env->NewGlobalRef(MutableData);

	jclass MutableDataClass = FAndroidApplication::FindJavaClass("com/ninevastudios/unrealfirebase/FGMutableData");
	PlatformData->GetKeyMethod = FJavaWrapper::FindMethod(Env, MutableDataClass, "GetKey", "()Ljava/lang/String;", false);
	PlatformData->GetPriorityMethod = FJavaWrapper::FindMethod(Env, MutableDataClass, "GetPriority", "()Ljava/lang/Object;", false);
	PlatformData->SetPriorityMethod = FJavaWrapper::FindMethod(Env, MutableDataClass, "SetPriority", "(Ljava/lang/Object;)V", false);
	PlatformData->GetValueMethod = FJavaWrapper::FindMethod(Env, MutableDataClass, "GetValue", "()Ljava/lang/Object;", false);
	PlatformData->SetValueMethod = FJavaWrapper::FindMethod(Env, MutableDataClass, "SetValue", "(Ljava/lang/Object;)V", false);
	PlatformData->ChildMethod = FJavaWrapper::FindMethod(Env, MutableDataClass, "Child", "(Ljava/lang/String;)Ljava/lang/Object;", false);
	PlatformData->GetChildrenMethod = FJavaWrapper::FindMethod(Env, MutableDataClass, "GetChildren", "()Ljava/util/ArrayList;", false);
	PlatformData->GetChildrenCountMethod = FJavaWrapper::FindMethod(Env, MutableDataClass, "GetChildrenCount", "()J", false);
	PlatformData->HasChildMethod = FJavaWrapper::FindMethod(Env, MutableDataClass, "HasChild", "(Ljava/lang/String;)Z", false);
	PlatformData->HasChildrenMethod = FJavaWrapper::FindMethod(Env, MutableDataClass, "HasChildren", "()Z", false);
}
#endif

#if PLATFORM_IOS
void UFGMutableData::InitPlatformData(FIRMutableData* MutableData)
{
	PlatformData->MutableData = MutableData;
}
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
void UFGMutableData::InitPlatformData(firebase::database::MutableData* data)
{
	PlatformData->MutableData = data;
}
#endif

FString UFGMutableData::GetKey() const
{
	FString KeyString = "";
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jstring Key = static_cast<jstring>(Env->CallObjectMethod(PlatformData->JMutableData, PlatformData->GetKeyMethod));
	KeyString = FJavaHelper::FStringFromLocalRef(Env, Key);
#endif

#if PLATFORM_IOS
	KeyString = FString([PlatformData->MutableData key]);
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	KeyString = PlatformData->MutableData->key();
#endif

	return KeyString;
}

FFGValueVariant UFGMutableData::GetPriority() const
{
	FFGValueVariant PriorityVariant;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jobject Data = Env->CallObjectMethod(PlatformData->JMutableData, PlatformData->GetPriorityMethod);
	PriorityVariant = ValueVariantUtils::JavaObjectToVariant(Env, Data);
	Env->DeleteLocalRef(Data);
#endif

#if PLATFORM_IOS
	id Priority = [PlatformData->MutableData priority];
	PriorityVariant = ValueVariantUtils::IdToVariant(Priority);
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PriorityVariant = FGVariantUtils::FirebaseVariantToValueVariant(PlatformData->MutableData->priority());
#endif

	return PriorityVariant;
}

void UFGMutableData::SetPriority(const FFGValueVariant& Priority)
{
	if (Priority.Type == EValueType::Array || Priority.Type == EValueType::Map || Priority.Type == EValueType::Bool)
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Priority cannot be a collection or boolean. Has to be a numerical or string value"));
		return;
	}

#if PLATFORM_ANDROID
	JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
	jobject JPriority = ValueVariantUtils::VariantToJavaObject(Env, Priority);
	Env->CallVoidMethod(PlatformData->JMutableData, PlatformData->SetPriorityMethod, JPriority);
	Env->DeleteLocalRef(JPriority);
#endif

#if PLATFORM_IOS
	id PriorityObject = ValueVariantUtils::VariantToId(Priority);
	PlatformData->MutableData.priority = PriorityObject;
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PlatformData->MutableData->set_priority(FGVariantUtils::ValueVariantToFirebaseVariant(Priority));
#endif
}

FFGValueVariant UFGMutableData::GetValue()
{
	FFGValueVariant ValueVariant;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jobject Data = Env->CallObjectMethod(PlatformData->JMutableData, PlatformData->GetValueMethod);
	ValueVariant = ValueVariantUtils::JavaObjectToVariant(Env, Data);
	Env->DeleteLocalRef(Data);
#endif

#if PLATFORM_IOS
	id Value = [PlatformData->MutableData value];
	ValueVariant = ValueVariantUtils::IdToVariant(Value);
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	ValueVariant = FGVariantUtils::FirebaseVariantToValueVariant(PlatformData->MutableData->value());
#endif

	return ValueVariant;
}

void UFGMutableData::SetValue(const FFGValueVariant& Value)
{
#if PLATFORM_ANDROID
	JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
	jobject JValue = ValueVariantUtils::VariantToJavaObject(Env, Value);
	Env->CallVoidMethod(PlatformData->JMutableData, PlatformData->SetValueMethod, JValue);
	Env->DeleteLocalRef(JValue);
#endif

#if PLATFORM_IOS
	id ValueObject = ValueVariantUtils::VariantToId(Value);
	PlatformData->MutableData.value = ValueObject;
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PlatformData->MutableData->set_value(FGVariantUtils::ValueVariantToFirebaseVariant(Value));
#endif
}

UFGMutableData* UFGMutableData::Child(const FString& Path) const
{
	UFGMutableData* Child = NewObject<UFGMutableData>();

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	auto JPath = FJavaClassObject::GetJString(Path);
	jobject JChild = Env->CallObjectMethod(PlatformData->JMutableData, PlatformData->ChildMethod, *JPath);
	Child->InitPlatformData(JChild);
#endif

#if PLATFORM_IOS
	Child->InitPlatformData([PlatformData->MutableData childDataByAppendingPath:Path.GetNSString()]);
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::MutableData child = PlatformData->MutableData->Child(TCHAR_TO_ANSI(*Path));
	Child->InitPlatformData(&child);
#endif

	return Child;
}

TArray<UFGMutableData*> UFGMutableData::GetChildren() const
{
	TArray<UFGMutableData*> Children;

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass ListClass = FJavaWrapper::FindClass(Env, "java/util/List", false);
	jmethodID SizeMethod = FJavaWrapper::FindMethod(Env, ListClass, "size", "()I", false);
	jmethodID GeteMethod = FJavaWrapper::FindMethod(Env, ListClass, "get", "(I)Ljava/lang/Object;", false);
	jobject JChildren = Env->CallObjectMethod(PlatformData->JMutableData, PlatformData->GetChildrenMethod);

	const int Size = Env->CallIntMethod(JChildren, SizeMethod);

	for (int i = 0; i < Size; i++)
	{
		jobject JChild = Env->CallObjectMethod(JChildren, GeteMethod, i);
		UFGMutableData* Child = NewObject<UFGMutableData>();
		Child->InitPlatformData(JChild);
		Children.Add(Child);
		Env->DeleteLocalRef(JChild);
	}
	Env->DeleteLocalRef(JChildren);
#endif

#if PLATFORM_IOS
	for (FIRMutableData* Child in [PlatformData->MutableData children])
	{
		UFGMutableData* ChildData = NewObject<UFGMutableData>();
		ChildData->InitPlatformData([Child retain]);
		Children.Add(ChildData);
	}
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	for (auto& child : PlatformData->MutableData->children())
	{
		UFGMutableData* ChildData = NewObject<UFGMutableData>();
		ChildData->InitPlatformData(&child);
		Children.Add(ChildData);
	}
#endif

	return Children;
}

int UFGMutableData::GetChildrenCount() const
{
	int Count = 0;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Count = Env->CallLongMethod(PlatformData->JMutableData, PlatformData->GetChildrenCountMethod);
#endif

#if PLATFORM_IOS
	Count = [PlatformData->MutableData childrenCount];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	Count = PlatformData->MutableData->children_count();
#endif

	return Count;
}

bool UFGMutableData::HasChild(const FString& Path) const
{
	bool bRet = false;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	auto JPath = FJavaClassObject::GetJString(Path);
	bRet = Env->CallBooleanMethod(PlatformData->JMutableData, PlatformData->HasChildMethod, *JPath);
#endif

#if PLATFORM_IOS
	bRet = [PlatformData->MutableData hasChildAtPath:Path.GetNSString()];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	bRet = PlatformData->MutableData->HasChild(TCHAR_TO_ANSI(*Path));
#endif

	return bRet;
}

bool UFGMutableData::HasChildren() const
{
	bool bRet = false;
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	bRet = Env->CallBooleanMethod(PlatformData->JMutableData, PlatformData->HasChildrenMethod);
#endif

#if PLATFORM_IOS
	bRet = [PlatformData->MutableData hasChildren];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	bRet = GetChildrenCount() > 0;
#endif

	return bRet;
}
