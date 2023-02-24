// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "leeActor.generated.h"



//
//UENUM(BlueprintType)
//enum ECollisionChannel
//{
//	/**
//	* @NOTE!!!! This DisplayName [DISPLAYNAME] SHOULD MATCH suffix of ECC_DISPLAYNAME
//	* Otherwise it will mess up collision profile loading
//	* If you change this, please also change FCollisionResponseContainers
//	*
//	* If you add any more TraceQuery="1", you also should change UCollsionProfile::LoadProfileConfig
//	* Metadata doesn't work outside of editor, so you'll need to add manually
//	*/
//	ECC_WorldStatic UMETA(DisplayName = "WorldStatic"),
//	ECC_WorldDynamic UMETA(DisplayName = "WorldDynamic"),
//	ECC_Pawn UMETA(DisplayName = "Pawn"),
//	ECC_Visibility UMETA(DisplayName = "Visibility", TraceQuery = "1"),
//	ECC_Camera UMETA(DisplayName = "Camera", TraceQuery = "1"),
//	ECC_PhysicsBody UMETA(DisplayName = "PhysicsBody"),
//	ECC_Vehicle UMETA(DisplayName = "Vehicle"),
//	ECC_Destructible UMETA(DisplayName = "Destructible"),
//	// @NOTE : when you add more here for predefined engine channel
//	// please change the max in the CollisionProfile
//	// search ECC_Destructible
//
//	// Unspecified Engine Trace Channels
//	ECC_EngineTraceChannel1 UMETA(Hidden),
//	ECC_EngineTraceChannel2 UMETA(Hidden),
//	ECC_EngineTraceChannel3 UMETA(Hidden),
//	ECC_EngineTraceChannel4 UMETA(Hidden),
//	ECC_EngineTraceChannel5 UMETA(Hidden),
//	ECC_EngineTraceChannel6 UMETA(Hidden),
//
//	// in order to use this custom channels
//	// we recommend to define in your local file
//	// - i.e. #define COLLISION_WEAPON		ECC_GameTraceChannel1
//	// and make sure you customize these it in INI file by
//	// 
//	// in DefaultEngine.ini
//	//
//	// [/Script/Engine.CollisionProfile]
//	// GameTraceChannel1="Weapon"
//	// 
//	// also in the INI file, you can override collision profiles that are defined by simply redefining
//	// note that Weapon isn't defined in the BaseEngine.ini file, but "Trigger" is defined in Engine
//	// +Profiles=(Name="Trigger",CollisionEnabled=QueryOnly,ObjectTypeName=WorldDynamic, DefaultResponse=ECR_Overlap, CustomResponses=((Channel=Visibility, Response=ECR_Ignore), (Channel=Weapon, Response=ECR_Ignore)))
//	ECC_GameTraceChannel1 UMETA(Hidden),
//	ECC_GameTraceChannel2 UMETA(Hidden),
//	ECC_GameTraceChannel3 UMETA(Hidden),
//	ECC_GameTraceChannel4 UMETA(Hidden),
//	ECC_GameTraceChannel5 UMETA(Hidden),
//	ECC_GameTraceChannel6 UMETA(Hidden),
//	ECC_GameTraceChannel7 UMETA(Hidden),
//	ECC_GameTraceChannel8 UMETA(Hidden),
//	ECC_GameTraceChannel9 UMETA(Hidden),
//	ECC_GameTraceChannel10 UMETA(Hidden),
//	ECC_GameTraceChannel11 UMETA(Hidden),
//	ECC_GameTraceChannel12 UMETA(Hidden),
//	ECC_GameTraceChannel13 UMETA(Hidden),
//	ECC_GameTraceChannel14 UMETA(Hidden),
//	ECC_GameTraceChannel15 UMETA(Hidden),
//	ECC_GameTraceChannel16 UMETA(Hidden),
//	ECC_GameTraceChannel17 UMETA(Hidden),
//	ECC_GameTraceChannel18 UMETA(Hidden),
//
//	/** Add new serializeable channels above here (i.e. entries that exist in FCollisionResponseContainer) */
//	/** Add only nonserialized/transient flags below */
//
//	// NOTE!!!! THESE ARE BEING DEPRECATED BUT STILL THERE FOR BLUEPRINT. PLEASE DO NOT USE THEM IN CODE
//	/**
//	 * This can be used to get all overlap event. If you trace with this channel,
//	 * It will return everything except its own. Do not use this often as this is expensive operation
//	 */
//	 /**
//	  * can't add displaynames because then it will show up in the collision channel option
//	  */
//	  ECC_OverlapAll_Deprecated UMETA(Hidden),
//	  ECC_MAX,
//};


UCLASS()
class ACADEMY_API AleeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AleeActor();

	UPROPERTY(EditAnywhere, Category = "lee's Ultils")
		TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;
	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* leeMeshInstance;
	
	UPROPERTY(VisibleAnywhere)
		TSubclassOf<AActor> lActor;
	
	UPROPERTY(EditAnyWhere,BlueprintReadWrite, Category = "lee's Ultils")
		FVector2D lRowColumnOffset;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		int32 lRows;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		float lSpawnNums;

	UFUNCTION()
		void lMultiSpawns(int spawnNumber);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		bool lparallel;

	FVector lTraceLine(FVector TraceStart);

	FVector lTrace;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;

};
