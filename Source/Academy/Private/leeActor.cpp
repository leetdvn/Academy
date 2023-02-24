// Fill out your copyright notice in the Description page of Project Settings.


#include "leeActor.h"
#include <Engine/StaticMeshActor.h>
#include <Components/SphereComponent.h>
#include <DrawDebugHelpers.h>
// Sets default values
AleeActor::AleeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	leeMeshInstance= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leeInstance"));
	leeMeshInstance->SetMobility(EComponentMobility::Static);
}


void AleeActor::lMultiSpawns(int spawnNumber)
{
	FActorSpawnParameters params;
	FVector sLocation = GetActorLocation();
	float row{};
	int column=lRows;
	if (lparallel) {
#pragma omp parallel for
	}
	for (int i = 0; i < spawnNumber; i++, row += lRowColumnOffset.X) {
		if (i == column) {
			sLocation.Y += lRowColumnOffset.Y;
			row = GetActorLocation().X ;
			column += lRows;
		}
		float RowX = GetActorLocation().X + row;

		sLocation.X = RowX;
		FVector impactPoint = lTraceLine(sLocation);

		sLocation.Z = impactPoint.Z;

		AActor* spawn = GetWorld()->SpawnActor< AActor>(lActor, sLocation, FRotator{0,0,0}, params);
		spawn->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		//spawn->SetActorLocation(sLocation, true, nullptr, ETeleportType::None);
		//spawn->SetActorLocationAndRotation(sLocation,);
	}

}


FVector AleeActor::lTraceLine(FVector TraceStart)
{
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;
	TArray<FHitResult> Hits;
	FCollisionShape sphere = FCollisionShape::MakeSphere(2.0f);
	// We set up a line trace from our current location to a point 1000cm ahead of us
	FVector TraceEnd = GetActorLocation() + (-GetActorUpVector()) * 100000.0f;

	// You can use FCollisionQueryParams to further configure the query
	// Here we add ourselves to the ignored list so we won't block the trace
	FCollisionQueryParams QueryParams= FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);;

	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = false;
	//QueryParams.bDebugQuery = true;
	QueryParams.AddIgnoredActor(this);
	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	//GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);
	bool isHit = GetWorld()->SweepMultiByChannel(Hits, TraceStart, TraceEnd, FQuat::Identity, TraceChannelProperty,sphere,QueryParams);
	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	DrawDebugSphere(GetWorld(), TraceStart, sphere.GetSphereRadius(), 10, FColor::Purple, true);
	UE_LOG(LogTemp, Warning, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());

	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (isHit)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
		//UE_LOG(LogTemp, Warning, TEXT("Trace hit actor: %s"), *Hit.Location.ToString());
		for (auto h : Hits) {

			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, h.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 20.0f);
			//ULeetdFunctionLibrary::leeDebugStr(h.Location.ToString());
			//ULeetdFunctionLibrary::leeDebugStr(FString::FromInt(Hits.Num()));
			return h.Location;
		}
		

		FVector location = Hit.Location;
		//lMultiSpawns(location, FRotator(), 40);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Actors were hit"));
	}

	return FVector();
}

// Called when the game starts or when spawned
void AleeActor::BeginPlay()
{
	Super::BeginPlay();
	
	lMultiSpawns(50);
}

// Called every frame
//void AleeActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

