// Fill out your copyright notice in the Description page of Project Settings.


#include "leeComfirmWidget.h"

void UleeComfirmWidget::lSetConfirmTittle(FString Message)
{
	if (!Message.IsEmpty())
		lMessage->SetText(FText::FromString(Message));
}

void UleeComfirmWidget::lSetTitleFromTable(FString field)
{
	if (field.IsEmpty()) return;

	FText text = FText::FromStringTable(SETTINGTABLE, field);
}

void UleeComfirmWidget::lSetVisible(bool isShow)
{
	ESlateVisibility vis = isShow ? ESlateVisibility::SelfHitTestInvisible :
		ESlateVisibility::Hidden;
	return this->SetVisibility(vis);
}
