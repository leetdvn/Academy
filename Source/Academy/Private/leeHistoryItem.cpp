// Fill out your copyright notice in the Description page of Project Settings.


#include "leeHistoryItem.h"

UleeHistoryItem::UleeHistoryItem(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    JsGameObject = MakeShareable(new FJsonObject());
}

UButton* UleeHistoryItem::lTakeItem(bool isLock)
{
    UTexture2D* tex = isLock ? LockPath : UnLockPath;
    ESlateVisibility vis = isLock ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
    if (tex) {

        ItemBgr->SetIsEnabled(!isLock);
        ItemCheck->SetVisibility(vis);
    }
    return ItemBgr;
}

void UleeHistoryItem::OnMouseDown()
{
    isActive = true;
    OnItemClick.Broadcast(this);
    
}

void UleeHistoryItem::NativeConstruct()
{
    ItemBgr->OnClicked.AddDynamic(this, &UleeHistoryItem::OnMouseDown);
}

void UleeHistoryItem::NativeDestruct()
{
    if (OnItemClick.IsBound()) OnItemClick.Clear();
    if (ItemBgr->OnClicked.IsBound()) ItemBgr->OnClicked.Clear();
}

FReply UleeHistoryItem::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent)
{
    FReply iReply = Super::NativeOnTouchStarted(InGeometry, InTouchEvent);
    if (ItemBgr->GetIsEnabled()) return iReply;
    isActive = false;
    OnItemClick.Broadcast(this);
    lDebug("aaaaaaaaaaaaaaaaaaaa");
    return iReply;
}
