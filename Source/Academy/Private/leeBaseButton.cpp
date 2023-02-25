// Fill out your copyright notice in the Description page of Project Settings.


#include "leeBaseButton.h"
#include <Kismet/GameplayStatics.h>
#include <Components/VerticalBoxSlot.h>
#include <Components/ScrollBoxSlot.h>
#include <Components/HorizontalBoxSlot.h>
#include <leePublicEnum.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

class UWidgetTree;

UleeBaseButton* UleeBaseButton::ins;

UleeBaseButton* UleeBaseButton::operator=(UleeBaseButton*& other)
{
	if(!other)
		other = CreateWidget<UleeBaseButton>(GetWorld(), UleeBaseButton::StaticClass());
	other->lSetTextFont(ltextsize);
	//set size
	other->lSetButtonSize(lSizeOverride);
	other->lUpdateBaseSize(lSizeOverride);
	other->lSetTextVisibility(lImageOnly);
	//set text
	other->ltextblock->SetText(FText::FromString(ltext));

	//set Normal Image
	other->lSetNormalFromPath(lNormalPath, lSizeOverride);
	other->rowID = rowID;
	other->lSetTextVisibility(ltextHiden);
	other->lSetContentSize();
	//lDebug(ltextsize);
	return other;
}

UleeBaseButton::UleeBaseButton(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	if (this != nullptr)
		ins = this;
	//bCanChildrenBeAccessible = true;
	//bCreatedByConstructionScript = true;
	//UTextBlock* t = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
}

void UleeBaseButton::NativeConstruct()
{

	//lDebug("Construction debug.. ", FColor::Purple, "Native :");
	//FString text = "", img = "";
	//lInitialized(img,text,lImageOnly);
	FOnInputAction abc;
	ListenForInputAction("Touching", EInputEvent::IE_Pressed, true,abc);
}

//void UleeBaseButton::ListenForInputAction(FName ActionName, TEnumAsByte<EInputEvent> EventType, bool bConsume, FOnInputAction Callback)
//{
//	lDebug("Listening");
//}

void UleeBaseButton::NativeDestruct()
{
	//debug ondestroying
	//lDebug("native destroy...");
}

void UleeBaseButton::NativeOnInitialized()
{
	//if (lDrop)
	//	lDrag = !lDrop;
	//else if (lDrag)
	//	lDrop = !lDrag;
	//lDebug("OnInitialized debug.. ", FColor::Purple, "Native :");

}

void UleeBaseButton::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (!lDrag) return;

	//lDebug("Mouse On Drag.... ", FColor::Blue, "Native :");
	if (lWidgetVisual && lDragVisual) {
		UleeBaseButton* WidgetVisual = CreateWidget<UleeBaseButton>(this, lWidgetVisual);
		WidgetVisual=lCopyRef(ins);
	
		WidgetVisual->lButton=this->lButton;// = *&this->lButton;
		WidgetVisual->ltextblock->SetText(FText::FromString(""));
		//WidgetVisual->rowID = rowID;
		//WidgetVisual->lSetButtonSize(iSize);

		UDragDropOperation* DragVisual = NewObject<UDragDropOperation>(this, lDragVisual);
		DragVisual->Payload = this;// lGetTextureFromPath(lNormalPath);
		DragVisual->DefaultDragVisual = WidgetVisual;
		DragVisual->Pivot = EDragPivot::CenterCenter;
		OutOperation = DragVisual;
		lSetVisibility(true);
	}

}

FReply UleeBaseButton::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//FEventReply iReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this,EKeys::MiddleMouseButton);
	////Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	//if (InMouseEvent.IsTouchEvent())
	//{
	//	iReply.NativeReply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	//	lDebug("mouse touching.");
	//}

	//if (InMouseEvent.GetEffectingButton() == EKeys::MiddleMouseButton || InMouseEvent.GetEffectingButton() == EKeys::MiddleMouseButton) {
	//	iReply.NativeReply.DetectDrag(TakeWidget(), EKeys::MiddleMouseButton);
	//	return iReply.NativeReply;
	//}
	//return iReply.NativeReply;//Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

bool UleeBaseButton::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (!lDrop) return false;
	UIleeDelegate::OnCorrectDrop.Broadcast(InOperation);
	UleeBaseButton* DragVisual = Cast<UleeBaseButton>(InOperation->DefaultDragVisual);
	if (DragVisual) {
		DragVisual->lSetContentSize();
		UleeBaseButton* DragObj = Cast<UleeBaseButton>(InOperation->Payload);
		FString DropName= DragVisual->lGetTextureButton()->GetName();
		if (DragVisual->rowID != rowID  || DropName == lGetTextureButton()->GetName()) {
			if (DragObj)
				DragObj->lSetVisibility(false);
			return false;

		}
		//OnDropTimes.Broadcast(Droptimes);

		if (ltexture2D->GetName().EndsWith(DropName)) {
			lSetNormalFromPath(DragVisual->lNormalPath, DragVisual->lSize);
			//OnDropCorrect.Broadcast(DropCorrecttimes);
			if (lCheckStatus) lSetChecked(true);
			return false;
		}

		//on Drop Fail
		//OnDropFail.Broadcast(DropFailtimes);
		if (DragObj)
			DragObj->lSetVisibility(false);
	}

	return false;

}

void UleeBaseButton::NativePreConstruct()
{
	lSetTextFont(ltextsize);
	lSetButtonSize(lSizeOverride);
	lSetTextVisibility(lImageOnly);
	lSetNormalFromPath(lNormalPath, lSizeOverride);
	if(Slot)
		lSetUpdateSizeRules(Slot,ESlateSizeRule::Fill);

}

FReply UleeBaseButton::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent)
{
	FReply iReply = Super::NativeOnTouchStarted(InGeometry, InTouchEvent);
	if (InTouchEvent.IsTouchEvent()) {
		iReply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
		lDebug("Touch....2");

	}

	if (InTouchEvent.IsTouchEvent()) {
		iReply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
		lDebug("Touch....3");

	}
	return iReply;
}

FEventReply UleeBaseButton::OnTouchMoved(FGeometry MyGeometry, const FPointerEvent& InTouchEvent)
{
	FEventReply iReply = Super::OnTouchMoved(MyGeometry, InTouchEvent);
	lDebug("toouch...");

	return iReply;
}

void UleeBaseButton::lSetDrag(UUserWidget* DragVisual, bool isDrag)
{
	//lDragVisual
	/*{ lDrag = isDrag; lDragVisual = DragVisual; };*/
}

void UleeBaseButton::lSetPading(FMargin newMargin)
{
	if (Slot) {
		FString slotName = Slot->GetClass()->GetName();
		if (slotName.StartsWith("Vertical")){
			UVerticalBoxSlot* panel = Cast<UVerticalBoxSlot>(Slot);
			if (panel) panel->SetPadding(newMargin);
		}
		else if (slotName.StartsWith("Horizontal"))
		{
			UHorizontalBoxSlot* panel = Cast<UHorizontalBoxSlot>(Slot);
			if (panel) { panel->SetPadding(newMargin); }

		}
		else if (slotName.StartsWith("Scroll"))	{
			UScrollBoxSlot* panel = Cast<UScrollBoxSlot>(Slot);
			if (panel) panel->SetPadding(newMargin);
		}
	}
}

void UleeBaseButton::lSetContentSize()
{
    
	if (ltexture2D) {
		ltexture2D = lGetTextureFromPath(lNormalPath); 
		lButton->WidgetStyle.Normal.SetResourceObject(ltexture2D);
		FVector2D vector2D{ float(ltexture2D->GetSizeX()) , float(ltexture2D->GetSizeY()) };
		lButton->WidgetStyle.Normal.SetImageSize(vector2D);
		lButton->WidgetStyle.Hovered.SetImageSize(vector2D*1.05);
		lButton->WidgetStyle.Pressed.SetImageSize(vector2D);
		lSize = vector2D;
		lSetButtonSize(vector2D);
		//lSetButtonSize(vector2D);
		//lButton->WidgetStyle.Normal.SetImageSize(vector2D);
		//lButton->WidgetStyle.Hovered.SetImageSize(vector2D);
		//lButton->WidgetStyle.Pressed.SetImageSize(vector2D);

	}
}

void UleeBaseButton::lSetChecked(bool ischecked)
{
	if (!lCheckStatus) return;
	ESlateVisibility state = ischecked ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	if (lCheckStatus->GetVisibility() != state)
		lCheckStatus->SetVisibility(state);

}

bool UleeBaseButton::lGetChecked()
{
	if (!lCheckStatus) return false;

	bool results = lCheckStatus->GetVisibility() == ESlateVisibility::SelfHitTestInvisible ||
		lCheckStatus->GetVisibility() == ESlateVisibility::Visible
		? true : false;

	return results;
}

TEnumAsByte<lSlotType> UleeBaseButton::lGetSlotType()
{
	TEnumAsByte<lSlotType> mSlot{};

	if (Slot) {
		FString slotName = Slot->GetClass()->GetName();
		mSlot = slotName.StartsWith("Vertical") ? VerticalBox :
			slotName.StartsWith("Horizontal") ? HorizontalBox :	ScrollBox;
		return mSlot;
	}
	return mSlot;
}

template<class T>
void UleeBaseButton::lSetRules(ESlateSizeRule::Type nRules)
{
	if (Slot->GetClass()->GetName().StartsWith("Scroll")) return;
	T* panelSlot = Cast<T>(Slot);
	if (panelSlot) {
		FSlateChildSize cSize = panelSlot->Size;
		cSize.SizeRule = nRules;
		panelSlot->SetSize(cSize);
	}
}

void UleeBaseButton::lInitialized(FString ImagePath,FString &text, bool ImageOnly)
{
	//init text size may be not need
	lSetTextFont(ltextsize);
	//set size
	lSetButtonSize(lSizeOverride);
	lUpdateBaseSize(lSizeOverride);
	lSetTextVisibility(ImageOnly);
	//set text
	lSetText(text);

	if (ImagePath.IsEmpty()) return;
	//set Normal Image
	lSetNormalFromPath(ImagePath,lSizeOverride);
	lNormalPath = ImagePath;

	//lDebug(ltextsize);
	lButton->OnClicked.AddDynamic(this, &UleeBaseButton::OpenMap);
}

void UleeBaseButton::OnCorrectClicked()
{
	lDebug("Correct Clicked.");
	OnCorrectClick.Broadcast(GetName());
}
//change map level
void UleeBaseButton::OpenMap()
{
	//
	FString CurrentMap = GetWorld()->GetMapName();
	FString newMap = "ThreeLines";
	if (CurrentMap.EndsWith(newMap) || !lMapExists(newMap)) return;
	//lDebug(CurrentMap);
	//TArray<FString> maps= lGetAllMapNames();
	//for (auto m : maps)
	//	if(!m.StartsWith("UEDPIE_0"))lDebug(m);
	UGameplayStatics::OpenLevel(GetWorld(),TEXT("ThreeLines"));
}

UleeBaseButton* UleeBaseButton::lCopyRef(UleeBaseButton*& other)
{
	other->lSetTextFont(ltextsize);
	//set size
	other->lSetTextVisibility(lImageOnly);
	//set text
	other->ltextblock->SetText(FText::FromString(ltext));

	//set Normal Image
	other->lSetNormalFromPath(lNormalPath, lSizeOverride);
	other->rowID = rowID;
	//other->lSetTextVisibility(ltextHiden);
	lSize = lGetSizeTexture(lNormalPath);
	other->lButton->WidgetStyle.Normal.SetImageSize(lSize);
	other->lButton->WidgetStyle.Hovered.SetImageSize(lSize*1.05);
	other->lSetButtonSize(lSize*1.1);

	return other;
}

void UleeBaseButton::lOnListenCallback()
{
	lDebug("call back Touch..");
}

void UleeBaseButton::lSetNormalFromPath(FString imgPath, FVector2D normalSize)
{
	//if (normalSize.X > 0 || normalSize.Y > 0) WidgetStyle.Normal.ImageSize = normalSize;
	lUpdateBaseSize(normalSize);
	if (imgPath.IsEmpty() || imgPath == "") return;
	UTexture2D* Texture = lGetTextureFromPath(imgPath);
	if (Texture) {
		lButton->WidgetStyle.Normal.SetResourceObject(Texture);
		ltexture2D = Texture;
		lSize = FVector2D(Texture->GetSizeX(), Texture->GetSizeY());
	}
	lButton->WidgetStyle.Normal.TintColor = FLinearColor{ 1,1,1,1 };
	Texture->GetPathName();
	lSetHorverFromPath(imgPath);
	lSetPressFromPath(imgPath);
	//lButton->OnClicked.AddDynamic(this, &UleeBaseButton::OnCorrectClicked);
}

void UleeBaseButton::lSetHorverFromPath(FString imgPath)
{
	UTexture2D* tex = lGetTextureFromPath(imgPath);
	if (!tex) return;
	lButton->WidgetStyle.Hovered.TintColor = FLinearColor{ 1,1,1,1 };
	lButton->WidgetStyle.Hovered.SetResourceObject(tex);
}

void UleeBaseButton::lSetPressFromPath(FString imgPath)
{
	UTexture2D* tex = lGetTextureFromPath(imgPath);
	if (!tex) return;
	lButton->WidgetStyle.Pressed.TintColor = FLinearColor{ 1,1,1,1 };
	lButton->WidgetStyle.Pressed.SetResourceObject(tex);
}

void UleeBaseButton::lSetTextFont(int32 fontsize)
{
	FSlateFontInfo font = ltextblock->Font;
	font.Size = fontsize;
	return ltextblock->SetFont(font);
}

void UleeBaseButton::lSetButtonSize(FVector2D sizeOverride)
{
	FVector2D newsize = lButton->WidgetStyle.Normal.ImageSize == sizeOverride ?
		lButton->WidgetStyle.Normal.ImageSize : sizeOverride;
	//lButton->WidgetStyle.Normal.SetImageSize(newsize);
	//lButton->WidgetStyle.Hovered.SetImageSize(newsize * 1.2);
	//lButton->WidgetStyle.Pressed.SetImageSize(newsize);
	lSizeBox->SetWidthOverride(newsize.X + ltextsize);
	lSizeBox->SetHeightOverride(newsize.Y + ltextsize);
}

void UleeBaseButton::lUpdateBaseSize(FVector2D newsize)
{
	lButton->WidgetStyle.Normal.SetImageSize(newsize);
	lButton->WidgetStyle.Hovered.SetImageSize(newsize*1.1);
	lButton->WidgetStyle.Pressed.SetImageSize(newsize);
}

void UleeBaseButton::lSetText(FString newtext)
{
	ltext = newtext;
	return ltextblock->SetText(FText::FromString(newtext));
}

void UleeBaseButton::lSetTextVisibility(bool visible)
{
	ESlateVisibility state = visible ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	if (ltextblock->GetVisibility() != state)
		ltextblock->SetVisibility(state);
	ltextHiden = visible;
}

void UleeBaseButton::lSetVisibility(bool visible)
{
	ESlateVisibility state = visible ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	if (GetVisibility() != state)
		SetVisibility(state);

}
