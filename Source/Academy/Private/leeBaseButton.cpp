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

UleeBaseButton::UleeBaseButton(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	if (this != nullptr)
		ins = this;
}

void UleeBaseButton::NativeConstruct()
{
	Super::NativeConstruct();
	//lDebug("Construction debug.. ", FColor::Purple, "Native :");
	//FString text = "", img = "";
	//lInitialized(img,text,lImageOnly);
	FOnInputAction abc;
	ListenForInputAction("Touching", EInputEvent::IE_Pressed, true,abc);
	if (lButton)
		lButton->OnClicked.AddDynamic(this, &UleeBaseButton::lClickCallBack);

}

void UleeBaseButton::NativeDestruct()
{
	Super::NativeDestruct();
	//debug ondestroying
	//lDebug("native destroy...");
	//if (lButton->OnClicked.IsBound())
	lButton->OnClicked.Clear();
	Premium->OnMouseButtonDownEvent.Clear();
	OnCorrect.Clear();
	OnMenuClick.Clear();
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
		lButton->WidgetStyle.Disabled.SetImageSize(vector2D);

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

void UleeBaseButton::lSetTexture2D(UTexture2D* tex)
{
	if (!tex) return;
	lButton->WidgetStyle.Normal.SetResourceObject(tex);
	lButton->WidgetStyle.Hovered.SetResourceObject(tex);
	lButton->WidgetStyle.Pressed.SetResourceObject(tex);
	lButton->WidgetStyle.Disabled.SetResourceObject(tex);
	ltexture2D = tex;
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

void UleeBaseButton::lInitialized(FString ImagePath,FString &text, bool ImageOnly, TEnumAsByte<lGameType> gametype)
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

void UleeBaseButton::lClickCallBack()
{
	//lDebug("call back Touch..");

	FString log = GetParent()->GetClass()->GetName();
	//UE_LOG(LogTemp,Warning, TEXT("Log : %s"),*log)
	if(ltexture2D && log == "ScrollBox")
		OnMenuClick.Broadcast(ltexture2D->GetName());
	OnCorrect.Broadcast(this);
}

void UleeBaseButton::lReplyFourBox()
{
	FString answer = " answer : " + lGetText();
	lDebug(answer);
}

void UleeBaseButton::lClearCorrectBound()
{
	OnCorrect.Clear();
	OnMenuClick.Clear();
}

void UleeBaseButton::lClearOnClick()
{
	if (lButton)
		lButton->OnClicked.Clear();
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
	lSetDisableFromPath(imgPath);
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

void UleeBaseButton::lSetDisableFromPath(FString imgPath)
{
	UTexture2D* tex = lGetTextureFromPath(imgPath);
	if (!tex) return;
	//lButton->WidgetStyle.Disabled.TintColor = FLinearColor{ 1,1,1,1 };
	lButton->WidgetStyle.Disabled.SetResourceObject(tex);

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
	FText::FromStringTable("", "");
	return ltextblock->SetText(FText::FromString(newtext));
}

FString UleeBaseButton::lGetTextureName()
{
	if(ltexture2D)
		return ltexture2D->GetName();
	return lButton->WidgetStyle.Normal.GetResourceObject()->GetFName().ToString();
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
