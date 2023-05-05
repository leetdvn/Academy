// Copyright (c) 2022 Nineva Studios

#include "Database/FGDatabaseRef.h"

#include "Async/Async.h"
#include "Database/FGDataSnapshot.h"
#include "Database/FGMutableData.h"
#include "Database/FGTransactionHandler.h"
#include "Database/FGTransactionTask.h"
#include "FirebaseGoodiesLog.h"

#if PLATFORM_ANDROID
#include "Android/Utils/FGValueVariantUtils.h"
#endif

#if PLATFORM_IOS
#include "IOS/Utils/FGValueVariantUtils.h"

#import <FirebaseDatabase/FirebaseDatabase.h>
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
#include "firebase/database.h"

#include "Desktop/FGVariantUtils.h"
#include "Common/FGValueVariantConv.h"

#include "Desktop/Database/FGDatabaseChildListener.h"
#include "Desktop/Database/FGDatabaseValueListener.h"
#endif

struct DatabaseRefPlatformData
{
#if PLATFORM_ANDROID
	TSharedPtr<FJavaClassObject> DatabaseRefJObject;
	FJavaClassMethod SetValueMethod;
	FJavaClassMethod SetTimestampMethod;
	FJavaClassMethod SetPriorityMethod;
	FJavaClassMethod GetKeyMethod;
	FJavaClassMethod GetValueMethod;
	FJavaClassMethod PushMethod;
	FJavaClassMethod RemoveValueMethod;
	FJavaClassMethod UpdateChildrenMethod;
	FJavaClassMethod AddValueListenerMethod;
	FJavaClassMethod RemoveValueListenerMethod;
	FJavaClassMethod AddChildListenerMethod;
	FJavaClassMethod RemoveChildListenerMethod;
	FJavaClassMethod KeepSyncedMethod;
	FJavaClassMethod RunTransactionMethod;
	FJavaClassMethod OrderByChildMethod;
	FJavaClassMethod OrderByKeyMethod;
	FJavaClassMethod OrderByPriorityMethod;
	FJavaClassMethod OrderByValueMethod;
	FJavaClassMethod StartAtFloatMethod;
	FJavaClassMethod StartAtStringMethod;
	FJavaClassMethod EndAtFloatMethod;
	FJavaClassMethod EndAtStringMethod;
	FJavaClassMethod EqualToFloatMethod;
	FJavaClassMethod EqualToBoolMethod;
	FJavaClassMethod EqualToStringMethod;
	FJavaClassMethod LimitToFirstMethod;
	FJavaClassMethod LimitToLastMethod;
	FJavaClassMethod OnDisconnectSetValueMethod;
	FJavaClassMethod OnDisconnectSetTimestampMethod;
	FJavaClassMethod OnDisconnectRemoveValueMethod;
	FJavaClassMethod OnDisconnectUpdateChildrenMethod;
	FJavaClassMethod CancelDisconnectOpsMethod;
#endif

#if PLATFORM_IOS
	FIRDatabaseReference* DbRef;
	FIRDatabaseQuery* DbQuery;
	FIRDatabaseHandle ValueChangedEventHandle;
	FIRDatabaseHandle ChildAddedEventHandle;
	FIRDatabaseHandle ChildChangedEventHandle;
	FIRDatabaseHandle ChildRemovedEventHandle;
	FIRDatabaseHandle ChildMovedEventHandle;
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference DbRef;
	firebase::database::DatabaseReference::Query Query;
	FGDatabaseValueListener* ValueListener;
	FGDatabaseChildListener* ChildListener;
#endif
};

UFGDatabaseRef::UFGDatabaseRef()
	: PlatformData(MakeShared<DatabaseRefPlatformData>())
{
}

UFGDatabaseRef::~UFGDatabaseRef()
{
#if PLATFORM_IOS
	if (PlatformData->DbRef) [PlatformData->DbRef release];
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	if (PlatformData->ValueListener) delete(PlatformData->ValueListener);
	if (PlatformData->ChildListener) delete(PlatformData->ChildListener);
#endif
};

void UFGDatabaseRef::InitPlatformData(const FString& DatabaseUrl, const FString& InitialPath)
{
#if PLATFORM_ANDROID
	auto JUrl = FJavaClassObject::GetJString(DatabaseUrl);
	auto JPath = FJavaClassObject::GetJString(InitialPath);
	PlatformData->DatabaseRefJObject = MakeShared<FJavaClassObject>(
		"com/ninevastudios/unrealfirebase/FGDatabaseRef", "(Ljava/lang/String;Ljava/lang/String;J)V", *JUrl , *JPath, (jlong)this);

	PlatformData->SetValueMethod = PlatformData->DatabaseRefJObject->GetClassMethod("SetValue", "(Ljava/lang/Object;Ljava/lang/Object;)V");
	PlatformData->SetTimestampMethod = PlatformData->DatabaseRefJObject->GetClassMethod("SetTimestamp", "()V");
	PlatformData->SetPriorityMethod = PlatformData->DatabaseRefJObject->GetClassMethod("SetPriority", "(Ljava/lang/Object;)V");
	PlatformData->GetKeyMethod = PlatformData->DatabaseRefJObject->GetClassMethod("GetKey", "()Ljava/lang/String;");
	PlatformData->GetValueMethod = PlatformData->DatabaseRefJObject->GetClassMethod("GetValue", "()V");
	PlatformData->PushMethod = PlatformData->DatabaseRefJObject->GetClassMethod("Push", "()Ljava/lang/String;");
	PlatformData->RemoveValueMethod = PlatformData->DatabaseRefJObject->GetClassMethod("RemoveValue", "()V");
	PlatformData->UpdateChildrenMethod = PlatformData->DatabaseRefJObject->GetClassMethod("UpdateChildren", "(Ljava/util/HashMap;)V");
	PlatformData->AddValueListenerMethod = PlatformData->DatabaseRefJObject->GetClassMethod("AddValueListener", "()V");
	PlatformData->RemoveValueListenerMethod = PlatformData->DatabaseRefJObject->GetClassMethod("RemoveValueListener", "()V");
	PlatformData->AddChildListenerMethod = PlatformData->DatabaseRefJObject->GetClassMethod("AddChildListener", "()V");
	PlatformData->RemoveChildListenerMethod = PlatformData->DatabaseRefJObject->GetClassMethod("RemoveChildListener", "()V");
	PlatformData->KeepSyncedMethod = PlatformData->DatabaseRefJObject->GetClassMethod("KeepSynced", "(Z)V");
	PlatformData->RunTransactionMethod = PlatformData->DatabaseRefJObject->GetClassMethod("RunTransaction", "()V");
	PlatformData->OrderByChildMethod = PlatformData->DatabaseRefJObject->GetClassMethod("OrderByChild", "(Ljava/lang/String;)V");
	PlatformData->OrderByKeyMethod = PlatformData->DatabaseRefJObject->GetClassMethod("OrderByKey", "()V");
	PlatformData->OrderByPriorityMethod = PlatformData->DatabaseRefJObject->GetClassMethod("OrderByPriority", "()V");
	PlatformData->OrderByValueMethod = PlatformData->DatabaseRefJObject->GetClassMethod("OrderByValue", "()V");
	PlatformData->StartAtFloatMethod = PlatformData->DatabaseRefJObject->GetClassMethod("StartAtFloat", "(DLjava/lang/String;)V");
	PlatformData->StartAtStringMethod = PlatformData->DatabaseRefJObject->GetClassMethod("StartAtString", "(Ljava/lang/String;Ljava/lang/String;)V");
	PlatformData->EndAtFloatMethod = PlatformData->DatabaseRefJObject->GetClassMethod("EndAtFloat", "(DLjava/lang/String;)V");
	PlatformData->EndAtStringMethod = PlatformData->DatabaseRefJObject->GetClassMethod("EndAtString", "(Ljava/lang/String;Ljava/lang/String;)V");
	PlatformData->EqualToFloatMethod = PlatformData->DatabaseRefJObject->GetClassMethod("EqualToFloat", "(DLjava/lang/String;)V");
	PlatformData->EqualToBoolMethod = PlatformData->DatabaseRefJObject->GetClassMethod("EqualToBool", "(ZLjava/lang/String;)V");
	PlatformData->EqualToStringMethod = PlatformData->DatabaseRefJObject->GetClassMethod("EqualToString", "(Ljava/lang/String;Ljava/lang/String;)V");
	PlatformData->LimitToFirstMethod = PlatformData->DatabaseRefJObject->GetClassMethod("LimitToFirst", "(I)V");
	PlatformData->LimitToLastMethod = PlatformData->DatabaseRefJObject->GetClassMethod("LimitToLast", "(I)V");
	PlatformData->OnDisconnectSetValueMethod = PlatformData->DatabaseRefJObject->GetClassMethod("OnDisconnectSetValue", "(Ljava/lang/Object;)V");
	PlatformData->OnDisconnectSetTimestampMethod = PlatformData->DatabaseRefJObject->GetClassMethod("OnDisconnectSetTimestamp", "()V");
	PlatformData->OnDisconnectRemoveValueMethod = PlatformData->DatabaseRefJObject->GetClassMethod("OnDisconnectRemoveValue", "()V");
	PlatformData->OnDisconnectUpdateChildrenMethod = PlatformData->DatabaseRefJObject->GetClassMethod("OnDisconnectUpdateChildren", "(Ljava/util/HashMap;)V");
	PlatformData->CancelDisconnectOpsMethod = PlatformData->DatabaseRefJObject->GetClassMethod("CancelDisconnectOperations", "()V");
#endif

#if PLATFORM_IOS
	FIRDatabase* database = DatabaseUrl.IsEmpty() ? [FIRDatabase database] : [FIRDatabase databaseWithURL:DatabaseUrl.GetNSString()];
	if (InitialPath.IsEmpty())
	{
		PlatformData->DbRef = [database reference];
		[PlatformData->DbRef retain];
	}
	else
	{
		PlatformData->DbRef = [database referenceWithPath:InitialPath.GetNSString()];
		[PlatformData->DbRef retain];
	}
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::Database* database;
	if (DatabaseUrl.IsEmpty()) 
	{
		database = firebase::database::Database::GetInstance(firebase::App::GetInstance());
	}
	else
	{
		database = firebase::database::Database::GetInstance(firebase::App::GetInstance(), TCHAR_TO_ANSI(*DatabaseUrl));
	}

	if (InitialPath.IsEmpty())
	{
		PlatformData->DbRef = database->GetReference();
	}
	else
	{
		PlatformData->DbRef = database->GetReference(TCHAR_TO_ANSI(*InitialPath));
	}
#endif

	RefPath = InitialPath.Right(1) == TEXT("/") ? InitialPath.LeftChop(InitialPath.Len() - 1) : InitialPath;
}

UFGDatabaseRef* UFGDatabaseRef::MakeDatabaseRootRef()
{
	UFGDatabaseRef* dbRef = NewObject<UFGDatabaseRef>();
	dbRef->InitPlatformData("", "");
	return dbRef;
}

UFGDatabaseRef* UFGDatabaseRef::MakeDatabaseRefFromPath(const FString& Path)
{
	UFGDatabaseRef* dbRef = NewObject<UFGDatabaseRef>();
	dbRef->InitPlatformData("", Path);
	return dbRef;
}

UFGDatabaseRef* UFGDatabaseRef::MakeDatabaseReference(const FString& DatabaseUrl, const FString& Path)
{
	UFGDatabaseRef* dbRef = NewObject<UFGDatabaseRef>();
	dbRef->InitPlatformData(DatabaseUrl, Path);
	return dbRef;
}

UFGDatabaseRef* UFGDatabaseRef::Child(const FString& Path) const
{
	FString NewPath = RefPath / Path;
	return UFGDatabaseRef::MakeDatabaseRefFromPath(NewPath);
}

UFGDatabaseRef* UFGDatabaseRef::Parent() const
{
	return UFGDatabaseRef::MakeDatabaseRefFromPath(GetPathToParent());
}

UFGDatabaseRef* UFGDatabaseRef::Root() const
{
	return UFGDatabaseRef::MakeDatabaseRootRef();
}

void UFGDatabaseRef::SetValue(const FFGValueVariant& Value, const FFGValueVariant& Priority)
{
	if (Priority.Type == EValueType::Array || Priority.Type == EValueType::Map || Priority.Type == EValueType::Bool)
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Priority cannot be a collection or boolean. Has to be a numerical or string value"));
		return;
	}

#if PLATFORM_ANDROID
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	jobject JVal = ValueVariantUtils::VariantToJavaObject(JEnv, Value);
	jobject JPriority = ValueVariantUtils::VariantToJavaObject(JEnv, Priority);

	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->SetValueMethod, JVal, JPriority);

	JEnv->DeleteLocalRef(JVal);
	JEnv->DeleteLocalRef(JPriority);
#endif

#if PLATFORM_IOS
	id ValueObject = ValueVariantUtils::VariantToId(Value);
	id PriorityObject = ValueVariantUtils::VariantToId(Priority);

	[PlatformData->DbRef setValue:ValueObject andPriority:PriorityObject];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::Future<void> task;
	if (Priority.Type == EValueType::Null)
	{
		task = PlatformData->DbRef.SetValue(FGVariantUtils::ValueVariantToFirebaseVariant(Value));
	}
	else
	{
		task = PlatformData->DbRef.SetValueAndPriority(FGVariantUtils::ValueVariantToFirebaseVariant(Value), FGVariantUtils::ValueVariantToFirebaseVariant(Priority));
	}
	
	task.AddOnCompletion([=](const ::firebase::Future<void>& callback) {
		if (callback.status() == firebase::FutureStatus::kFutureStatusComplete)
		{
			UE_LOG(LogFirebaseGoodies, Verbose, TEXT("Set Value success!"));
		}
		else
		{
			FString ErrorMessage = FString(callback.error_message());
			UE_LOG(LogFirebaseGoodies, Error, TEXT("Set Value error: %s"), *ErrorMessage);
		}
	});
#endif
}

void UFGDatabaseRef::SetTimestamp()
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->SetTimestampMethod);
#endif

#if PLATFORM_IOS
	[PlatformData->DbRef setValue:[FIRServerValue timestamp]];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	auto task = PlatformData->DbRef.SetValue(firebase::database::ServerTimestamp());
	task.AddOnCompletion([=](const ::firebase::Future<void>& callback) {
		if (callback.status() == firebase::FutureStatus::kFutureStatusComplete)
		{
			UE_LOG(LogFirebaseGoodies, Verbose, TEXT("Set Timestamp success!"));
		}
		else
		{
			FString ErrorMessage = FString(callback.error_message());
			UE_LOG(LogFirebaseGoodies, Error, TEXT("Set Timestamp error: %s"), *ErrorMessage);
		}
	});
#endif
}

void UFGDatabaseRef::SetPriority(const FFGValueVariant& Priority)
{
	if (Priority.Type == EValueType::Array || Priority.Type == EValueType::Map || Priority.Type == EValueType::Bool)
	{
		UE_LOG(LogFirebaseGoodies, Error, TEXT("Priority cannot be a collection or boolean. Has to be a numerical or string value"));
		return;
	}

#if PLATFORM_ANDROID
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	jobject JPriority = ValueVariantUtils::VariantToJavaObject(JEnv, Priority);

	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->SetPriorityMethod, JPriority);

	JEnv->DeleteLocalRef(JPriority);
#endif

#if PLATFORM_IOS
	id PriorityObject = ValueVariantUtils::VariantToId(Priority);
	[PlatformData->DbRef setPriority:PriorityObject];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	auto task = PlatformData->DbRef.SetPriority(FGVariantUtils::ValueVariantToFirebaseVariant(Priority));
	task.AddOnCompletion([=](const ::firebase::Future<void>& callback) {
		if (callback.status() == firebase::FutureStatus::kFutureStatusComplete)
		{
			UE_LOG(LogFirebaseGoodies, Verbose, TEXT("Set Priority success!"));
		}
		else
		{
			FString ErrorMessage = FString(callback.error_message());
			UE_LOG(LogFirebaseGoodies, Error, TEXT("Set Priority error: %s"), *ErrorMessage);
		}
	});
#endif
}

FString UFGDatabaseRef::GetKey() const
{
	FString KeyString = "";

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jstring Key = static_cast<jstring>(PlatformData->DatabaseRefJObject->CallMethod<jobject>(PlatformData->GetKeyMethod));
	KeyString = FJavaHelper::FStringFromGlobalRef(Env, Key);
#endif

#if PLATFORM_IOS
	KeyString = FString([PlatformData->DbRef key]);
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	KeyString = PlatformData->DbRef.key();
#endif

	return KeyString;
}

void UFGDatabaseRef::GetValue(const FOnDataChangedDelegate& OnDataReceived, const FOnCancelledDelegate& OnCancelled)
{
	OnDataChangedDelegate = OnDataReceived;
	OnCancelledDelegate = OnCancelled;

#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->GetValueMethod);
#endif

#if PLATFORM_IOS
	typedef void (^TCallbackBlock)(FIRDataSnapshot* _Nonnull);
	typedef void (^TErrorBlock)(NSError* _Nonnull);

	TCallbackBlock CallbackBlock = ^(FIRDataSnapshot* _Nonnull Snapshot) {
		UFGDataSnapshot* Data = NewObject<UFGDataSnapshot>();
		Data->InitPlatformData([Snapshot retain]);
		AsyncTask(ENamedThreads::GameThread, [=]() {
			OnDataChangedDelegate.ExecuteIfBound(Data);
		});
	};
	TErrorBlock ErrorBlock = ^(NSError* _Nonnull Error) {
		const FString ErrorMessage([Error localizedDescription]);
		int ErrorCode = [Error code];

		UE_LOG(LogFirebaseGoodies, Error, TEXT("Database operation failed: %s"), *ErrorMessage);
		AsyncTask(ENamedThreads::GameThread, [=]() {
			OnCancelledDelegate.ExecuteIfBound(ErrorCode, ErrorMessage);
		});
	};

	[PlatformData->DbRef observeSingleEventOfType:FIRDataEventTypeValue
										withBlock:CallbackBlock
								  withCancelBlock:ErrorBlock];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	auto task = PlatformData->DbRef.GetValue();
	task.AddOnCompletion([=](const ::firebase::Future<firebase::database::DataSnapshot>& callback) {
		if (callback.status() == firebase::FutureStatus::kFutureStatusComplete)
		{
			UFGDataSnapshot* Data = NewObject<UFGDataSnapshot>();
			Data->InitPlatformData(*callback.result());

			AsyncTask(ENamedThreads::GameThread, [=]() {
				OnDataChangedDelegate.ExecuteIfBound(Data);
			});
		}
		else
		{
			FString ErrorMessage = FString(callback.error_message());
			int ErrorCode = callback.error();

			UE_LOG(LogFirebaseGoodies, Error, TEXT("Database operation failed: %s"), *ErrorMessage);
			AsyncTask(ENamedThreads::GameThread, [=]() {
				OnCancelledDelegate.ExecuteIfBound(ErrorCode, ErrorMessage);
			});
		}
		});
#endif
}

UFGDatabaseRef* UFGDatabaseRef::Push()
{
	FString ChildString = "";

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jstring NewChild = static_cast<jstring>(PlatformData->DatabaseRefJObject->CallMethod<jobject>(PlatformData->PushMethod));
	ChildString = FJavaHelper::FStringFromGlobalRef(Env, NewChild);
#endif

#if PLATFORM_IOS
	FIRDatabaseReference* NewRef = [PlatformData->DbRef childByAutoId];
	ChildString = FString([NewRef key]);
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference NewRef = PlatformData->DbRef.PushChild();
	ChildString = NewRef.key();
#endif

	return Child(ChildString);
}

void UFGDatabaseRef::RemoveValue()
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->RemoveValueMethod);
#endif

#if PLATFORM_IOS
	[PlatformData->DbRef removeValue];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PlatformData->DbRef.RemoveValue();
#endif
}

void UFGDatabaseRef::UpdateChildren(const TMap<FString, FFGValueVariant>& Update)
{
	FFGValueVariant MapWrapper;
	MapWrapper.Type = EValueType::Map;
	MapWrapper.Value = Update;
#if PLATFORM_ANDROID
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	jobject JMap = ValueVariantUtils::VariantToJavaObject(JEnv, MapWrapper);

	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->UpdateChildrenMethod, JMap);

	JEnv->DeleteLocalRef(JMap);
#endif

#if PLATFORM_IOS
	id UpdateDict = ValueVariantUtils::VariantToId(MapWrapper);
	[PlatformData->DbRef updateChildValues:UpdateDict];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	auto task = PlatformData->DbRef.UpdateChildren(FGVariantUtils::ValueVariantMapToFirebaseVariant(Update));
	task.AddOnCompletion([=](const ::firebase::Future<void>& callback) {
		if (callback.status() == firebase::FutureStatus::kFutureStatusComplete)
		{
			UE_LOG(LogFirebaseGoodies, Verbose, TEXT("Update Children success!"));
		}
		else
		{
			FString ErrorMessage = FString(callback.error_message());
			UE_LOG(LogFirebaseGoodies, Error, TEXT("Update Children error: %s"), *ErrorMessage);
		}
	});
#endif
}

void UFGDatabaseRef::AddValueListener(const FOnDataChangedDelegate& OnDataChanged, const FOnCancelledDelegate& OnCancelled)
{
	OnDataChangedDelegate = OnDataChanged;
	OnCancelledDelegate = OnCancelled;

#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->AddValueListenerMethod);
#endif

#if PLATFORM_IOS
	typedef void (^TCallbackBlock)(FIRDataSnapshot* _Nonnull);
	typedef void (^TErrorBlock)(NSError* _Nonnull);

	TCallbackBlock CallbackBlock = ^(FIRDataSnapshot* _Nonnull Snapshot) {
		UFGDataSnapshot* Data = NewObject<UFGDataSnapshot>();
		Data->InitPlatformData([Snapshot retain]);
		AsyncTask(ENamedThreads::GameThread, [=]() {
			OnDataChangedDelegate.ExecuteIfBound(Data);
		});
	};
	TErrorBlock ErrorBlock = ^(NSError* _Nonnull Error) {
		const FString ErrorMessage([Error localizedDescription]);
		int ErrorCode = [Error code];

		UE_LOG(LogFirebaseGoodies, Error, TEXT("Database operation failed: %s"), *ErrorMessage);
		AsyncTask(ENamedThreads::GameThread, [=]() {
			OnCancelledDelegate.ExecuteIfBound(ErrorCode, ErrorMessage);
		});
	};

	RemoveValueListener();
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	PlatformData->ValueChangedEventHandle = [Query observeEventType:FIRDataEventTypeValue
														  withBlock:CallbackBlock
													withCancelBlock:ErrorBlock];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	FGDatabaseValueListener* Listener = new FGDatabaseValueListener();
	Listener->OnValueChangedDelegate = OnDataChangedDelegate;
	Listener->OnCancelledDelegate = OnCancelledDelegate;

	PlatformData->ValueListener = Listener;

	PlatformData->DbRef.AddValueListener(PlatformData->ValueListener);
#endif
}

void UFGDatabaseRef::RemoveValueListener()
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->RemoveValueListenerMethod);
#endif

#if PLATFORM_IOS
	if (PlatformData->ValueChangedEventHandle > 0)
	{
		FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
		[Query removeObserverWithHandle:PlatformData->ValueChangedEventHandle];
		PlatformData->ValueChangedEventHandle = 0;
	}
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PlatformData->DbRef.RemoveValueListener(PlatformData->ValueListener);
	delete(PlatformData->ValueListener);
	PlatformData->ValueListener = nullptr;
#endif
}

void UFGDatabaseRef::AddChildListener(const FOnChildEventDelegate& OnChildEvent, const FOnCancelledDelegate& OnCancelled)
{
	OnChildEventDelegate = OnChildEvent;
	OnChildCancelledDelegate = OnCancelled;

#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->AddChildListenerMethod);
#endif

#if PLATFORM_IOS
	typedef void (^TCallbackBlock)(FIRDataSnapshot* _Nonnull, NSString* _Nullable);
	typedef void (^TErrorBlock)(NSError* _Nonnull);

	TCallbackBlock ChildAddedBlock = ^(FIRDataSnapshot* _Nonnull Snapshot, NSString* _Nullable PrevKey) {
		UFGDataSnapshot* Data = NewObject<UFGDataSnapshot>();
		Data->InitPlatformData([Snapshot retain]);
		FString PrevKeyString = PrevKey ? FString(PrevKey) : FString();
		AsyncTask(ENamedThreads::GameThread, [=]() {
			OnChildEventDelegate.ExecuteIfBound(EChileEventType::Added, Data, PrevKeyString);
		});
	};
	TCallbackBlock ChildChangedBlock = ^(FIRDataSnapshot* _Nonnull Snapshot, NSString* _Nullable PrevKey) {
		UFGDataSnapshot* Data = NewObject<UFGDataSnapshot>();
		Data->InitPlatformData([Snapshot retain]);
		FString PrevKeyString = PrevKey ? FString(PrevKey) : FString();
		AsyncTask(ENamedThreads::GameThread, [=]() {
			OnChildEventDelegate.ExecuteIfBound(EChileEventType::Changed, Data, PrevKeyString);
		});
	};
	TCallbackBlock ChildRemovedBlock = ^(FIRDataSnapshot* _Nonnull Snapshot, NSString* _Nullable PrevKey) {
		UFGDataSnapshot* Data = NewObject<UFGDataSnapshot>();
		Data->InitPlatformData([Snapshot retain]);
		FString PrevKeyString = PrevKey ? FString(PrevKey) : FString();
		AsyncTask(ENamedThreads::GameThread, [=]() {
			OnChildEventDelegate.ExecuteIfBound(EChileEventType::Removed, Data, PrevKeyString);
		});
	};
	TCallbackBlock ChildMovedBlock = ^(FIRDataSnapshot* _Nonnull Snapshot, NSString* _Nullable PrevKey) {
		UFGDataSnapshot* Data = NewObject<UFGDataSnapshot>();
		Data->InitPlatformData([Snapshot retain]);
		FString PrevKeyString = PrevKey ? FString(PrevKey) : FString();
		AsyncTask(ENamedThreads::GameThread, [=]() {
			OnChildEventDelegate.ExecuteIfBound(EChileEventType::Moved, Data, PrevKeyString);
		});
	};
	TErrorBlock ErrorBlock = ^(NSError* _Nonnull Error) {
		const FString ErrorMessage([Error localizedDescription]);
		int ErrorCode = [Error code];

		UE_LOG(LogFirebaseGoodies, Error, TEXT("Database operation failed: %s"), *ErrorMessage);
		AsyncTask(ENamedThreads::GameThread, [=]() {
			OnChildCancelledDelegate.ExecuteIfBound(ErrorCode, ErrorMessage);
		});
	};

	RemoveChildListener();
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;

	PlatformData->ChildAddedEventHandle = [Query observeEventType:FIRDataEventTypeChildAdded
								   andPreviousSiblingKeyWithBlock:ChildAddedBlock
												  withCancelBlock:ErrorBlock];
	PlatformData->ChildChangedEventHandle = [Query observeEventType:FIRDataEventTypeChildChanged
									 andPreviousSiblingKeyWithBlock:ChildChangedBlock
													withCancelBlock:ErrorBlock];
	PlatformData->ChildRemovedEventHandle = [Query observeEventType:FIRDataEventTypeChildRemoved
									 andPreviousSiblingKeyWithBlock:ChildRemovedBlock
													withCancelBlock:ErrorBlock];
	PlatformData->ChildMovedEventHandle = [Query observeEventType:FIRDataEventTypeChildMoved
								   andPreviousSiblingKeyWithBlock:ChildMovedBlock
												  withCancelBlock:ErrorBlock];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	FGDatabaseChildListener* Listener = new FGDatabaseChildListener();
	Listener->OnChildEventCallback = OnChildEventDelegate;
	Listener->OnCancelledCallback = OnChildCancelledDelegate;

	PlatformData->ChildListener = Listener;
	PlatformData->DbRef.AddChildListener(PlatformData->ChildListener);
#endif
}

void UFGDatabaseRef::RemoveChildListener()
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->RemoveChildListenerMethod);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->ChildAddedEventHandle > 0) [Query removeObserverWithHandle:PlatformData->ChildAddedEventHandle];
	if (PlatformData->ChildChangedEventHandle > 0) [Query removeObserverWithHandle:PlatformData->ChildChangedEventHandle];
	if (PlatformData->ChildRemovedEventHandle > 0) [Query removeObserverWithHandle:PlatformData->ChildRemovedEventHandle];
	if (PlatformData->ChildMovedEventHandle > 0) [Query removeObserverWithHandle:PlatformData->ChildMovedEventHandle];

	PlatformData->ChildAddedEventHandle = 0;
	PlatformData->ChildChangedEventHandle = 0;
	PlatformData->ChildRemovedEventHandle = 0;
	PlatformData->ChildMovedEventHandle = 0;
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PlatformData->DbRef.RemoveChildListener(PlatformData->ChildListener);
	delete(PlatformData->ChildListener);
	PlatformData->ChildListener = nullptr;
#endif
}

void UFGDatabaseRef::KeepSynced(bool Sync)
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->KeepSyncedMethod, Sync);
#endif

#if PLATFORM_IOS
	[PlatformData->DbRef keepSynced:Sync];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PlatformData->DbRef.SetKeepSynchronized(Sync);
#endif
}

UFGDatabaseRef* UFGDatabaseRef::OrderByChild(const FString& Path)
{
#if PLATFORM_ANDROID
	auto JPath = FJavaClassObject::GetJString(Path);
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->OrderByChildMethod, *JPath);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	PlatformData->DbQuery = [Query queryOrderedByChild:Path.GetNSString()];
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;

	query = query.OrderByChild(TCHAR_TO_ANSI(*Path));
#endif

	return this;
}

UFGDatabaseRef* UFGDatabaseRef::OrderByKey()
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->OrderByKeyMethod);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	PlatformData->DbQuery = [Query queryOrderedByKey];
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;

	query = query.OrderByKey();
#endif

	return this;
}

UFGDatabaseRef* UFGDatabaseRef::OrderByPriority()
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->OrderByPriorityMethod);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	PlatformData->DbQuery = [Query queryOrderedByPriority];
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;

	query = query.OrderByPriority();
#endif

	return this;
}

UFGDatabaseRef* UFGDatabaseRef::OrderByValue()
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->OrderByValueMethod);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	PlatformData->DbQuery = [Query queryOrderedByValue];
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;

	query = query.OrderByValue();
#endif

	return this;
}

UFGDatabaseRef* UFGDatabaseRef::EndAtFloat(float Value, const FString& Key)
{
#if PLATFORM_ANDROID
	auto JKey = FJavaClassObject::GetJString(Key);
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->EndAtFloatMethod, Value, *JKey);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	if (Key.IsEmpty())
	{
		PlatformData->DbQuery = [Query queryEndingAtValue:[NSNumber numberWithFloat:Value]];
	}
	else
	{
		PlatformData->DbQuery = [Query queryEndingAtValue:[NSNumber numberWithFloat:Value] childKey:Key.GetNSString()];
	}
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;
	if (Key.IsEmpty())
	{
		query = query.EndAt(firebase::Variant::FromDouble(Value));
	}
	else
	{
		query = query.EndAt(firebase::Variant::FromDouble(Value), TCHAR_TO_ANSI(*Key));
	}	
#endif

	return this;
}

UFGDatabaseRef* UFGDatabaseRef::EndAtString(const FString& Value, const FString& Key)
{
#if PLATFORM_ANDROID
	auto JValue = FJavaClassObject::GetJString(Value);
	auto JKey = FJavaClassObject::GetJString(Key);
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->EndAtStringMethod, *JValue, *JKey);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	if (Key.IsEmpty())
	{
		PlatformData->DbQuery = [Query queryEndingAtValue:Value.GetNSString()];
	}
	else
	{
		PlatformData->DbQuery = [Query queryEndingAtValue:Value.GetNSString() childKey:Key.GetNSString()];
	}
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;
	if (Key.IsEmpty())
	{
		query = query.EndAt(firebase::Variant::FromStaticString(TCHAR_TO_ANSI(*Value)));
	}
	else
	{
		query = query.EndAt(firebase::Variant::FromStaticString(TCHAR_TO_ANSI(*Value)), TCHAR_TO_ANSI(*Key));
	}	
#endif

	return this;
}

UFGDatabaseRef* UFGDatabaseRef::StartAtFloat(float Value, const FString& Key)
{
#if PLATFORM_ANDROID
	auto JKey = FJavaClassObject::GetJString(Key);
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->StartAtFloatMethod, Value, *JKey);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	if (Key.IsEmpty())
	{
		PlatformData->DbQuery = [Query queryStartingAtValue:[NSNumber numberWithFloat:Value]];
	}
	else
	{
		PlatformData->DbQuery = [Query queryStartingAtValue:[NSNumber numberWithFloat:Value] childKey:Key.GetNSString()];
	}
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;
	if (Key.IsEmpty())
	{
		query = query.StartAt(firebase::Variant::FromDouble(Value));
	}
	else
	{
		query = query.StartAt(firebase::Variant::FromDouble(Value), TCHAR_TO_ANSI(*Key));
	}
#endif

	return this;
}

UFGDatabaseRef* UFGDatabaseRef::StartAtString(const FString& Value, const FString& Key)
{
#if PLATFORM_ANDROID
	auto JValue = FJavaClassObject::GetJString(Value);
	auto JKey = FJavaClassObject::GetJString(Key);
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->StartAtStringMethod, *JValue, *JKey);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	if (Key.IsEmpty())
	{
		PlatformData->DbQuery = [Query queryStartingAtValue:Value.GetNSString()];
	}
	else
	{
		PlatformData->DbQuery = [Query queryStartingAtValue:Value.GetNSString() childKey:Key.GetNSString()];
	}
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;
	if (Key.IsEmpty())
	{
		query = query.StartAt(firebase::Variant::FromStaticString(TCHAR_TO_ANSI(*Value)));
	}
	else
	{
		query = query.StartAt(firebase::Variant::FromStaticString(TCHAR_TO_ANSI(*Value)), TCHAR_TO_ANSI(*Key));
	}	
#endif

	return this;
}

UFGDatabaseRef* UFGDatabaseRef::EqualToFloat(float Value, const FString& Key)
{
#if PLATFORM_ANDROID
	auto JKey = FJavaClassObject::GetJString(Key);
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->EqualToFloatMethod, Value, *JKey);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	if (Key.IsEmpty())
	{
		PlatformData->DbQuery = [Query queryEqualToValue:[NSNumber numberWithFloat:Value]];
	}
	else
	{
		PlatformData->DbQuery = [Query queryEqualToValue:[NSNumber numberWithFloat:Value] childKey:Key.GetNSString()];
	}
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;
	if (Key.IsEmpty())
	{
		query = query.EqualTo(firebase::Variant::FromDouble(Value));
	}
	else
	{
		query = query.EqualTo(firebase::Variant::FromDouble(Value), TCHAR_TO_ANSI(*Key));
	}
#endif

	return this;
}

UFGDatabaseRef* UFGDatabaseRef::EqualToBool(bool Value, const FString& Key)
{
#if PLATFORM_ANDROID
	auto JKey = FJavaClassObject::GetJString(Key);
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->EqualToBoolMethod, Value, *JKey);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	if (Key.IsEmpty())
	{
		PlatformData->DbQuery = [Query queryEqualToValue:[NSNumber numberWithBool:Value]];
	}
	else
	{
		PlatformData->DbQuery = [Query queryEqualToValue:[NSNumber numberWithBool:Value] childKey:Key.GetNSString()];
	}
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;
	if (Key.IsEmpty())
	{
		query = query.EqualTo(firebase::Variant::FromBool(Value));
	}
	else
	{
		query = query.EqualTo(firebase::Variant::FromBool(Value), TCHAR_TO_ANSI(*Key));
	}
#endif

	return this;
}

UFGDatabaseRef* UFGDatabaseRef::EqualToString(const FString& Value, const FString& Key)
{
#if PLATFORM_ANDROID
	auto JValue = FJavaClassObject::GetJString(Value);
	auto JKey = FJavaClassObject::GetJString(Key);
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->EqualToStringMethod, *JValue, *JKey);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	if (Key.IsEmpty())
	{
		PlatformData->DbQuery = [Query queryEqualToValue:Value.GetNSString()];
	}
	else
	{
		PlatformData->DbQuery = [Query queryEqualToValue:Value.GetNSString() childKey:Key.GetNSString()];
	}
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;
	if (Key.IsEmpty())
	{
		query = query.EqualTo(firebase::Variant::FromStaticString(TCHAR_TO_ANSI(*Value)));
	}
	else
	{
		query = query.EqualTo(firebase::Variant::FromStaticString(TCHAR_TO_ANSI(*Value)), TCHAR_TO_ANSI(*Key));
	}
#endif

	return this;
}

UFGDatabaseRef* UFGDatabaseRef::LimitToFirst(int Limit)
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->LimitToFirstMethod, Limit);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	PlatformData->DbQuery = [Query queryLimitedToFirst:Limit];
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;
	
	query = query.LimitToFirst(Limit);
#endif

	return this;
}

UFGDatabaseRef* UFGDatabaseRef::LimitToLast(int Limit)
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->LimitToLastMethod, Limit);
#endif

#if PLATFORM_IOS
	FIRDatabaseQuery* Query = PlatformData->DbQuery ? PlatformData->DbQuery : PlatformData->DbRef;
	if (PlatformData->DbQuery) [PlatformData->DbQuery release];
	PlatformData->DbQuery = [Query queryLimitedToLast:Limit];
	[PlatformData->DbQuery retain];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	firebase::database::DatabaseReference::Query query = PlatformData->Query.is_valid() ? PlatformData->Query : PlatformData->DbRef;

	query = query.LimitToLast(Limit);
#endif

	return this;
}

void UFGDatabaseRef::OnDisconnectSetValue(const FFGValueVariant& Value)
{
#if PLATFORM_ANDROID
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	jobject JVal = ValueVariantUtils::VariantToJavaObject(JEnv, Value);

	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->OnDisconnectSetValueMethod, JVal);

	JEnv->DeleteLocalRef(JVal);
#endif

#if PLATFORM_IOS
	id ValueObject = ValueVariantUtils::VariantToId(Value);
	[PlatformData->DbRef onDisconnectSetValue:ValueObject];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PlatformData->DbRef.OnDisconnect()->SetValue(FGVariantUtils::ValueVariantToFirebaseVariant(Value));
#endif
}

void UFGDatabaseRef::OnDisconnectSetTimestamp()
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->OnDisconnectSetTimestampMethod);
#endif

#if PLATFORM_IOS
	[PlatformData->DbRef onDisconnectSetValue:[FIRServerValue timestamp]];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PlatformData->DbRef.OnDisconnect()->SetValue(firebase::database::ServerTimestamp());
#endif
}

void UFGDatabaseRef::OnDisconnectRemoveValue()
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->OnDisconnectRemoveValueMethod);
#endif

#if PLATFORM_IOS
	[PlatformData->DbRef onDisconnectRemoveValue];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PlatformData->DbRef.OnDisconnect()->RemoveValue();
#endif
}

void UFGDatabaseRef::OnDisconnectUpdateChildren(const TMap<FString, FFGValueVariant>& Update)
{
	FFGValueVariant MapWrapper;
	MapWrapper.Type = EValueType::Map;
	MapWrapper.Value = Update;
#if PLATFORM_ANDROID
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	jobject JMap = ValueVariantUtils::VariantToJavaObject(JEnv, MapWrapper);

	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->OnDisconnectUpdateChildrenMethod, JMap);

	JEnv->DeleteLocalRef(JMap);
#endif

#if PLATFORM_IOS
	id UpdateDict = ValueVariantUtils::VariantToId(MapWrapper);
	[PlatformData->DbRef onDisconnectUpdateChildValues:UpdateDict];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PlatformData->DbRef.OnDisconnect()->UpdateChildren(FGVariantUtils::ValueVariantMapToFirebaseVariant(Update));
#endif
}

void UFGDatabaseRef::CancelDisconnectOperations()
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->CancelDisconnectOpsMethod);
#endif

#if PLATFORM_IOS
	[PlatformData->DbRef cancelDisconnectOperations];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PlatformData->DbRef.OnDisconnect()->Cancel();
#endif
}

void UFGDatabaseRef::BindTransactionTask(UFGTransactionTask* Task)
{
	TransactionTask = Task;
}

void UFGDatabaseRef::RunTransaction()
{
#if PLATFORM_ANDROID
	PlatformData->DatabaseRefJObject->CallMethod<void>(PlatformData->RunTransactionMethod);
#endif

#if PLATFORM_IOS
	[PlatformData->DbRef
		runTransactionBlock:^FIRTransactionResult* _Nonnull(FIRMutableData* _Nonnull Data) {
			id Value = Data.value;
			if (!Value || [Value isEqual:[NSNull null]])
				return [FIRTransactionResult successWithValue:Data];

			UFGMutableData* MutableData = NewObject<UFGMutableData>();
			MutableData->InitPlatformData([Data retain]);

			ETransactionResult Result = static_cast<ETransactionResult>(RunTransactionHandler(MutableData));

			return Result == ETransactionResult::Success ? [FIRTransactionResult successWithValue:Data] : [FIRTransactionResult abort];
		}
		andCompletionBlock:^(NSError* _Nullable Error, BOOL Commited, FIRDataSnapshot* _Nullable Snapshot) {
			if (Commited)
			{
				AsyncTask(ENamedThreads::GameThread, [=]() {
					TriggerTransactionComplete();
				});
			}
			else
			{
				const FString ErrorMessage([Error localizedDescription]);
				AsyncTask(ENamedThreads::GameThread, [=]() {
					TriggerTransactionAbort(ErrorMessage);
				});
			}
		}];
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC) && FG_ENABLE_EDITOR_SUPPORT
	PlatformData->DbRef.RunTransaction([=](firebase::database::MutableData* mutableData) {
		UFGMutableData* MutableData = NewObject<UFGMutableData>();
		MutableData->InitPlatformData(mutableData);

		ETransactionResult Result = static_cast<ETransactionResult>(RunTransactionHandler(MutableData));

		return Result == ETransactionResult::Success ? firebase::database::kTransactionResultSuccess : firebase::database::kTransactionResultAbort;
	});
#endif
}

int UFGDatabaseRef::RunTransactionHandler(UFGMutableData* Data)
{
	return TransactionTask->RunHandler(Data);
}

void UFGDatabaseRef::TriggerTransactionComplete()
{
	TransactionTask->Complete.Broadcast(TEXT(""));
}

void UFGDatabaseRef::TriggerTransactionAbort(const FString& ErrorMessage)
{
	TransactionTask->Abort.Broadcast(ErrorMessage);
}

FString UFGDatabaseRef::GetPathToParent() const
{
	if (RefPath.IsEmpty()) return RefPath;

	int SlashPos = RefPath.FindLastCharByPredicate([](TCHAR C) { return C == TEXT('/'); });
	return RefPath.LeftChop(RefPath.Len() - SlashPos);
}

#if PLATFORM_ANDROID
JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGDatabaseRef_onDataChangedCallback(
	JNIEnv* env, jclass clazz, jlong objAddr, jobject dataSnapshot)
{
	UFGDatabaseRef* dbRef = reinterpret_cast<UFGDatabaseRef*>(objAddr);

	UFGDataSnapshot* data = NewObject<UFGDataSnapshot>();
	data->InitPlatformData(dataSnapshot);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		dbRef->OnDataChanged(data);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGDatabaseRef_onCancelledCallback(
	JNIEnv* env, jclass clazz, jlong objAddr, int errorCode, jstring errorMessage)
{
	UFGDatabaseRef* dbRef = reinterpret_cast<UFGDatabaseRef*>(objAddr);
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, errorMessage);

	UE_LOG(LogFirebaseGoodies, Error, TEXT("Database operation failed: %s"), *ErrorMessage);
	AsyncTask(ENamedThreads::GameThread, [=]() {
		dbRef->OnCancelled(errorCode, ErrorMessage);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGDatabaseRef_onChildEventCallback(
	JNIEnv* env, jclass clazz, jlong objAddr, int eventType, jobject dataSnapshot, jstring prevChildName)
{
	UFGDatabaseRef* dbRef = reinterpret_cast<UFGDatabaseRef*>(objAddr);

	UFGDataSnapshot* data = NewObject<UFGDataSnapshot>();
	data->InitPlatformData(dataSnapshot);
	FString PrevChildName = FJavaHelper::FStringFromParam(env, prevChildName);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		dbRef->OnChildEvent((EChileEventType)eventType, data, PrevChildName);
	});
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGDatabaseRef_onChildCancelledCallback(
	JNIEnv* env, jclass clazz, jlong objAddr, int errorCode, jstring errorMessage)
{
	UFGDatabaseRef* dbRef = reinterpret_cast<UFGDatabaseRef*>(objAddr);
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, errorMessage);

	UE_LOG(LogFirebaseGoodies, Error, TEXT("Database operation failed: %s"), *ErrorMessage);
	AsyncTask(ENamedThreads::GameThread, [=]() {
		dbRef->OnChildCancelled(errorCode, ErrorMessage);
	});
}

JNI_METHOD jlong Java_com_ninevastudios_unrealfirebase_FGDatabaseRef_doTransactionCallback(
	JNIEnv* env, jclass clazz, jlong objAddr, jobject mutableData)
{
	UFGDatabaseRef* dbRef = reinterpret_cast<UFGDatabaseRef*>(objAddr);

	UFGMutableData* data = NewObject<UFGMutableData>();
	data->InitPlatformData(mutableData);

	return dbRef->RunTransactionHandler(data);
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGDatabaseRef_onTransactionCompleteCallback(
	JNIEnv* env, jclass clazz, jlong objAddr, jboolean isSuccess, jstring errorMessage)
{
	UFGDatabaseRef* dbRef = reinterpret_cast<UFGDatabaseRef*>(objAddr);

	if (isSuccess)
	{
		AsyncTask(ENamedThreads::GameThread, [=]() {
			dbRef->TriggerTransactionComplete();
		});
	}
	else
	{
		FString ErrorMessage = FJavaHelper::FStringFromParam(env, errorMessage);
		AsyncTask(ENamedThreads::GameThread, [=]() {
			dbRef->TriggerTransactionAbort(ErrorMessage);
		});
	}
}

JNI_METHOD void Java_com_ninevastudios_unrealfirebase_FGDatabaseRef_onQueryErrorCallback(
	JNIEnv* env, jclass clazz, jstring errorMessage)
{
	FString ErrorMessage = FJavaHelper::FStringFromParam(env, errorMessage);
	UE_LOG(LogFirebaseGoodies, Error, TEXT("Query failed: %s"), *ErrorMessage);
}
#endif
