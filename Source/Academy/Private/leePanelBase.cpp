// Fill out your copyright notice in the Description page of Project Settings.


#include "leePanelBase.h"
#include <Kismet/GameplayStatics.h>
#include <Components/VerticalBoxSlot.h>
#include <Components/ScrollBoxSlot.h>
#include <Components/HorizontalBoxSlot.h>

UleePanelBase::UleePanelBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	if (this != nullptr)
		ins = this;
}

//UleePanelBase* UleePanelBase::operator=(UleePanelBase*& other)
//{
//	if (this == *&other)
//		return this;
//
//	//if (ins) other = *&ins;
//	//other = CreateWidget<UleePanelBase>(this, UleePanelBase::StaticClass());
//	//other->lDirectory = *&lDirectory;
//	//other->lbuttons = *&lbuttons;
//	//other->lCurrentDir = *&lCurrentDir;
//	//other->lMargin = *&lMargin;
//	//other->lRuntimeButton = *&lRuntimeButton;
//	//other->ImageOnly = ImageOnly;
//	//other->lpaneltype = lpaneltype;
//	//other->lQuantityOverride = *&lQuantityOverride;
//	//other->lTexts = *&lTexts;
//	//other->lTexturesOverride = *&lTexturesOverride;
//	//other->iDrag = iDrag;
//	//other->iDrop = iDrop;
//	return this;
//}


void UleePanelBase::lNewPanelImageFromDir(FString dir, bool Hastext)
{
	FString _dir = FPaths::ProjectContentDir() + dir;

	if (!FPaths::DirectoryExists(_dir)) return;
	TArray<FString> folders = lGetAllDirectory(_dir,false);

	if (folders.Num() <= 0) {	return;	}

	for (auto& f : folders) {
		if (f.IsEmpty()) break;
		FString imgpath = "/Game/" + lDirectory + "/" + f;
		lCreateNormalButton(imgpath, ImageOnly,  f);

		//UleeBaseButton* wid = CreateWidget<UleeBaseButton>(GetWorld(), lRuntimeButton);
		//if (wid) {
		//	lPanelWidget->AddChild(wid);
		//	FString imgpath = "/Game/" + lDirectory +"/" + f;
		//	//lDebug(imgpath);
		//	wid->lInitialized(imgpath, f);
		//	wid->lImageOnly = Hastext;
		//	lbuttons.Add(wid);
		//	wid->lButton->OnClicked.AddDynamic(this, &UleePanelBase::iOnClicked);
		//}
	}
	lOverrideTextures(lTexturesOverride, lbuttons, FVector2D{80,80});
	lOverrideTextName(lTexts, lbuttons);
	lCurrentDir = dir;
}

void UleePanelBase::lNewPanelImageFromFiles(FString dir, bool Hastext)
{
	FString _dir = FPaths::ProjectContentDir() + dir;

	if (!FPaths::DirectoryExists(_dir)) return;
	TArray<FString> files = lGetAllDirectory(_dir, true);
	if (files.Num() <= 0) return;

	//override number init button
	int initNum = lQuantityOverride < files.Num() && lQuantityOverride > 0 ? lQuantityOverride : files.Num();
	FString label{};
	for (int i = 0; i < initNum; i++) {
		if (files[i].IsEmpty()) break;
		FString imgpath = "/Game/" + dir + "/" + files[i];

		if (!iDrop && !iDrag) {
			if (!ButtonExists(imgpath))
				lCreateNormalButton(imgpath, ImageOnly, files[i]);

		}
		else {
			lCreateDragButton(imgpath, ImageOnly, iDrop, files[i]);
		}
	}

	if (!iDrop || !iDrag) {
		lOverrideTextures(lTexturesOverride, lbuttons, FVector2D{ 80,80 });
		lOverrideTextName(lTexts, lbuttons);
		lOverridePadding(lMargin, lbuttons);
		lCurrentDir = dir;
	}

}

void UleePanelBase::lInitializePanels(FString dir, TEnumAsByte<PanelType> panel, bool Hastext)
{
	if (dir == lCurrentDir) {
		//lDebug("current load this", FColor::Green, "Current Panels.");
		return;
	}

	if (lPanelWidget->HasAnyChildren()) ClearButtons();
	switch (panel)
	{
	case Files: return lNewPanelImageFromFiles(dir, Hastext);
	case Folders: return lNewPanelImageFromDir(dir, Hastext);
	}
}

void UleePanelBase::lOverrideTextName(TArray<FString> texts, TArray<UleeBaseButton*> btns)
{

	if (btns.Num() <= 0 || texts.Num() <= 0 ) return;
	for (int i = 0; i < texts.Num(); i++) {
		if (btns[i])	btns[i]->lSetText(texts[i]);
	}
}

void UleePanelBase::lOverrideTextName(TArray<FString> texts, TArray<UleeDragWidget*> btns)
{

	if (btns.Num() <= 0 || texts.Num() <= 0) return;
	for (int i = 0; i < texts.Num(); i++) {
		if (btns[i])	btns[i]->lSetText(texts[i]);
	}
}

void UleePanelBase::lOverrideTextName(TArray<FString> texts, bool isDragButtons)
{
	if (texts.Num() < 0) return;

	if (!isDragButtons) {
		return lOverrideTextName(texts, lbuttons);
	}
	return lOverrideTextName(texts, lDragDropButtons);
}

void UleePanelBase::lOverrideTextures(TArray<UTexture2D*> textures, TArray<UleeBaseButton*> btns, FVector2D size)
{
	if (textures.Num() <= 0) return;
	for (int i = 0; i < textures.Num(); i++) {
		if (btns[i]) {
			btns[i]->lSetNormalFromPath(textures[i]->GetPathName(), size);
		}
	}

}

void UleePanelBase::lOverridePadding(TArray<FMargin> margins, TArray<UleeBaseButton*> btns)
{
	if (btns.Num() <= 0 || margins.Num() <= 0) return;
	for (int i = 0; i < margins.Num(); i++) {
		if (btns[i])	btns[i]->lSetPading(margins[i]);
	}

}

void UleePanelBase::NativeConstruct()
{
	
	if (!lExistsDirectory(lDirectory)) return;

	//preview UI
	lInitializePanels(lDirectory, lpaneltype, ImageOnly);

	//FString folder = FPaths::ProjectContentDir() +lDirectory;
	//FString convert = FPaths::ConvertRelativePathToFull("/Game/AcademyAssets/leetdvn/sapxep");
	//lDebug(convert,FColor::Cyan,"Native Panel ");

	//lNewPanelImageFromFiles(folder);
}

void UleePanelBase::lInitializeChoiseAnswer(FString dir, FString ref)
{
	if (dir.IsEmpty() || ref.IsEmpty()) return;
	
}

void UleePanelBase::NativePreConstruct()
{
#if WITH_EDITOR
	if (!lExistsDirectory(lDirectory)) return;
		//preview UI
	lInitializePanels(lDirectory, lpaneltype, ImageOnly);
	//for (auto& i : lPanelWidget->GetAllChildren()) {
	//	UImage* img = Cast<UImage>(i);
	//	if (img) lStaticImage.AddUnique(img);
	//}
#endif
}

void UleePanelBase::NativeDestruct()
{
	if (lbuttons.Num() <= 0 ) return;

	for (auto& btn : lbuttons) {
		if (btn->OnMenuClick.IsBound()) btn->OnMenuClick.Clear();
		if (btn->lButton->OnClicked.IsBound()) btn->lButton->OnClicked.Clear();
	}
}

UleeBaseButton* UleePanelBase::lGetButton(int idx)
{
	if (idx >= lbuttons.Num()) return nullptr;
	return lbuttons[idx];
}

//test delegate
void UleePanelBase::OnDelegate(FString gName)
{
	lDebug(gName, FColor::Blue, "Delegate");
}

void UleePanelBase::ClearButtons()
{
	if (lPanelWidget->HasAnyChildren()) {
		TArray<UWidget*> children = lPanelWidget->GetAllChildren();
		if (children.Num() > 0) {
			for (auto c : children) {
				lPanelWidget->RemoveChild(c);
			}
		}
	}

	if (lDragDropButtons.Num() > 0) lDragDropButtons.Empty();
	if (lbuttons.Num() > 0) lbuttons.Empty();
}

void UleePanelBase::lSetDisable(bool disables)
{
	if (lbuttons.Num() < 0) return;

	ESlateVisibility vis = disables ? ESlateVisibility::HitTestInvisible : ESlateVisibility::SelfHitTestInvisible;

	for (auto& b : lbuttons) {
		b->SetVisibility(vis);
	}
}

void UleePanelBase::lResetChecked()
{
	if (lbuttons.Num() < 0) return;
	for (auto& b : lbuttons) {
		if (b->lGetChecked())
			b->lSetChecked(false);
	}
}

void UleePanelBase::lSetMakeSameAt(FString path, bool DragButton)
{
	if (DragButton && path.IsEmpty() && lDragDropButtons.Num() <= 0) return;
	if (!DragButton && path.IsEmpty() && lbuttons.Num() <= 0) return;


	if (DragButton) {
		for (auto& b : lDragDropButtons)
			b->lSetTexture(path);
		return;
	}

	FVector2D bSize = lGetSizeTexture(path);
	for (auto& b : lbuttons) {
		b->lSetNormalFromPath(path, bSize);
	}

}

UleeBaseButton* UleePanelBase::lCreateNormalButton(FString imgPath, bool ImgOnly, FString text,int32 rID)
{
	UleeBaseButton* wid = CreateWidget<UleeBaseButton>(GetWorld(), lRuntimeButton);
	if (!wid) {
		lDebug("null Base Button");
		return nullptr;
	}
	//------------------------------------
	int32 cCount = lPanelWidget->GetChildrenCount(); 
	lPanelWidget->AddChild(wid);
	lSetUpdateSizeRules(wid->Slot, ESlateSizeRule::Fill);
	wid->lInitialized(imgPath, text, ImgOnly);
	wid->lSetTextVisibility(ImgOnly);
	lbuttons.Add(wid);
	wid->rowID = rID;
	return wid;
}

bool UleePanelBase::ButtonExists(FString& buttonRef)
{
	if (buttonRef.IsEmpty() || !lPanelWidget->GetClass()->GetName().EndsWith("ScrollBox")) return false;
	//FString map = UGameplayStatics::GetCurrentLevelName(GetWorld());// ->GetMapName();
	//if (!map.EndsWith("AMenu")) return false;
	//lDebug(lPanelWidget->GetClass()->GetName());
#pragma omp parallel for
	for (auto& btn : lPanelWidget->GetAllChildren())
	{
		UleeBaseButton* b = Cast< UleeBaseButton>(btn);
		if (b) {
			if (b->lNormalPath == buttonRef)
				return true;
		}
	}
	return false;
}

UleeDragWidget* UleePanelBase::lCreateDragButton(FString imgPath, bool ImgOnly, bool isDrop, FString text, int32 rID)
{

	UleeDragWidget* wid = CreateWidget<UleeDragWidget>(GetWorld(), lRuntimeButton);

	if (!wid) {
		lDebug("null Drag Button");
		return nullptr;
	}

	int32 cCount = lPanelWidget->GetChildrenCount();
	lPanelWidget->AddChild(wid);

	lSetUpdateSizeRules(wid->Slot, ESlateSizeRule::Fill);
	wid->lIsDrop = isDrop;
	wid->lSetTexture(imgPath);
	wid->lSetId(rID);
	lDragDropButtons.Add(wid);

	return wid;
}

void UleePanelBase::lSetPanelId(int32 Id, bool isDragDrop)
{
	if (Id < 0) return;
	if (!isDragDrop) {
#pragma omp parallel for
		for (auto& btn : lbuttons)
			btn->Id = Id;
		return;
	}

#pragma omp parallel for
	for (auto& drag : lDragDropButtons)
		drag->lIdname = Id;

}
