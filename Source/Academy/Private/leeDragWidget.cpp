// Fill out your copyright notice in the Description page of Project Settings.


#include "leeDragWidget.h"
#include <Blueprint/DragDropOperation.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

UleeDragWidget::UleeDragWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	lImageDefault = "/Game/AcademyAssets/Assets/Textures/UI/btn_check";
}

void UleeDragWidget::NativePreConstruct()
{
	if (!lFilesExists(lImagePath)) lInitializeDefault(lImageDefault);

	lInitializeDefault(lImagePath);

}

void UleeDragWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (lIsDrop) return;

	//lDebug("Touching Detected");
	if (!lDragSubVisual || !lDragSubOperation) return;

	UleeDragWidget* WidgetVisual = CreateWidget<UleeDragWidget>(this, lDragSubVisual);
	WidgetVisual->lSetTexture(ltexture);
	WidgetVisual->lIdname = lIdname;
	//WidgetVisual->lSetButtonSize(iSize);

	UDragDropOperation* DragVisual = NewObject<UDragDropOperation>(this, lDragSubOperation);
	DragVisual->Payload = this;// lGetTextureFromPath(lNormalPath);
	DragVisual->DefaultDragVisual = WidgetVisual;
	DragVisual->Pivot = EDragPivot::CenterCenter;
	OutOperation = DragVisual;
	SetVisibility(ESlateVisibility::Hidden);
}

FReply UleeDragWidget::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent)
{
	FEventReply iReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InTouchEvent, this, EKeys::LeftMouseButton);
	if (lIsDrop) return iReply.NativeReply;

	if (InTouchEvent.IsTouchEvent()) {
		iReply.NativeReply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
		//lDebug("Touching Drag Widget");
		return iReply.NativeReply;
	}
	return iReply.NativeReply;
}

bool UleeDragWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (!lIsDrop) return false;

	UleeDragWidget* DragVisual = Cast<UleeDragWidget>(InOperation->DefaultDragVisual);
	if (DragVisual) {
		UleeDragWidget* DragObj = Cast<UleeDragWidget>(InOperation->Payload);
		FString DropName = DragVisual->ltexture->GetName();
		OnDropTimes.Broadcast();
		if (ltexture->GetName().EndsWith(DropName) && DragVisual->lIdname == lIdname) {
			lSetTexture(DragVisual->ltexture);
			OnDropCorrect.Broadcast();
			return false;
		}
		if (DragObj)
			DragObj->lSetVisibility(false);
	}
	OnDropFail.Broadcast();


	return false;
}

void UleeDragWidget::lInitializeDefault(FString ipath)
{
	UTexture2D* tex2D = lGetTextureFromPath(ipath);
	if (tex2D) {
		lDragImage->SetBrushResourceObject(tex2D);
		lPanelSlot = Cast<UCanvasPanelSlot>(lDragImage->Slot);
		if (lPanelSlot) {
			lPanelSlot->SetAlignment(FVector2D{ 0.5,0.5 });
			FAnchors anchor = lPanelSlot->GetAnchors();
			anchor.Minimum = FVector2D(0.5, 0.5);
			anchor.Maximum = FVector2D(0.5, 0.5);
			lPanelSlot->SetAnchors(anchor);
			lPanelSlot->SetPosition(FVector2D{ 0,0 });
			FVector2D v2D = lGetSizeTexture(ipath);
			lDragImage->SetBrushSize(v2D);
			ltexture = tex2D;
		}
	}

}

void UleeDragWidget::lSetTexture(FString path)
{
	lImagePath = path;
	lInitializeDefault(path);
}

void UleeDragWidget::lSetVisibility(bool visible)
{
	ESlateVisibility state = visible ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	if (GetVisibility() != state)
		SetVisibility(state);

}
