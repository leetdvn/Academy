// Fill out your copyright notice in the Description page of Project Settings.


#include "lee4BoxData.h"

Ulee4BoxData::Ulee4BoxData(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

FFourBoxData Ulee4BoxData::GetLinesAt(int32 index)
{
	return FFourBoxData();
}

TSharedPtr<FJsonValue> Ulee4BoxData::GetGameAsJSonAt(int32 index)
{
	return TSharedPtr<FJsonValue>();
}
