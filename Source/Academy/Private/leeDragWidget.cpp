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

	UleeDragWidget* WidgetVisual = CreateWidget<UleeDragWidget>(GetWorld(), lDragSubVisual);
	WidgetVisual->lSetTexture(ltexture);
	WidgetVisual->lIdname = lIdname;
	//WidgetVisual->lSetButtonSize(iSize);

	UDragDropOperation* DragVisual = NewObject<UDragDropOperation>(GetWorld(), lDragSubOperation);
	DragVisual->Pivot = EDragPivot::CenterCenter;
	DragVisual->Payload = this;// lGetTextureFromPath(lNormalPath);
	DragVisual->DefaultDragVisual = WidgetVisual;
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
			lStatusImage->SetVisibility(ESlateVisibility::Visible);
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
	FVector2D currenRes, sizeRes;
	UTexture2D* tex2D = lGetTextureFromPath(ipath);
	if (tex2D) {
		ltexture = tex2D;
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
			// do mobile specific stuff
			lDragImage->SetBrushSize(v2D);
			sizeRes = v2D;
			lDragImage->SetBrushSize(sizeRes);
			//-----------note scale resolution--------------------------------
			//sizeRes = currenRes.IsZero() ? v2D : currenRes.X <= 1 ? v2D * (currenRes.X * 0.8) : v2D * (currenRes.X);
			//lDragImage->SetBrushSize(v2D);
			//FVector2D statusSize = currenRes.X <= 1 ? lStatusImage->Brush.GetImageSize() * currenRes.X :
			//	lStatusImage->Brush.GetImageSize() * (currenRes.X * 0.7);
			//lStatusImage->SetBrushSize(statusSize);

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
