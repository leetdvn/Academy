// Fill out your copyright notice in the Description page of Project Settings.


#include "leeLessionData.h"

UleeLessionData* UleeLessionData::ins;

UleeLessionData::UleeLessionData()
{
	if (this != nullptr)
		ins = this;
}
