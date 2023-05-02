// Fill out your copyright notice in the Description page of Project Settings.


#include "leeTutorials.h"

void UleeTutorials::NativeConstruct()
{
	UWidgetAnimation* anim = !isDragTutorials ? Touch : Tutorial;

	PlayAnimation(anim, 0, 0);
}

void UleeTutorials::NativeDestruct()
{
}
