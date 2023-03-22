// Fill out your copyright notice in the Description page of Project Settings.


#include "leeHistoryItem.h"

UleeHistoryItem::UleeHistoryItem(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    JsGameObject = MakeShareable(new FJsonObject());
}

UImage* UleeHistoryItem::lTakeItem(bool isLock)
{
    UTexture2D* tex = isLock ? LockPath : UnLockPath;
    ESlateVisibility vis = isLock ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
    if (tex) {
        ItemBgr->Brush.SetResourceObject(tex);
        ItemCheck->SetVisibility(vis);
    }
    return ItemBgr;
}

void UleeHistoryItem::OnMouseDown()
{
    OnItemClick.Broadcast(this);
}

void UleeHistoryItem::NativeConstruct()
{
    ItemBgr->OnMouseButtonDownEvent.BindUFunction(this, FName("OnMouseDown"));
}
