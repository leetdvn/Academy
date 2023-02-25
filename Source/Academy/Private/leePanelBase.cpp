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

UleePanelBase* UleePanelBase::operator=(UleePanelBase*& other)
{
	if (ins) other = *&ins;
	//other = CreateWidget<UleePanelBase>(this, UleePanelBase::StaticClass());
	//other->lDirectory = *&lDirectory;
	//other->lbuttons = *&lbuttons;
	//other->lCurrentDir = *&lCurrentDir;
	//other->lMargin = *&lMargin;
	//other->lRuntimeButton = *&lRuntimeButton;
	//other->ImageOnly = ImageOnly;
	//other->lpaneltype = lpaneltype;
	//other->lQuantityOverride = *&lQuantityOverride;
	//other->lTexts = *&lTexts;
	//other->lTexturesOverride = *&lTexturesOverride;
	//other->iDrag = iDrag;
	//other->iDrop = iDrop;
	return other;
}


void UleePanelBase::lNewPanelImageFromDir(FString dir, bool Hastext)
{
	FString _dir = FPaths::ProjectContentDir() + dir;

	if (!FPaths::DirectoryExists(_dir)) return;
	TArray<FString> folders = lGetAllDirectory(_dir,false);

	if (folders.Num() <= 0) {	return;	}

	for (auto& f : folders) {
		if (f.IsEmpty()) break;
		FString imgpath = "/Game/" + lDirectory + "/" + f;
		lCreateButton(imgpath, ImageOnly, iDrop, f, iDrag);

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
			lCreateButton(imgpath, ImageOnly, iDrop, files[i], iDrag);
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
		lDebug("current load this", FColor::Green, "Current Panels.");
		return;
	}
	if (lPanelWidget->HasAnyChildren()) ClearButtons();
	switch (panel)
	{
	case Files: return lNewPanelImageFromFiles(dir, Hastext);
	case Folders: return lNewPanelImageFromDir(dir, Hastext);
	}
}

void UleePanelBase::iOnClicked()
{
	//lDebug("Clicked from lee CanvasPanel", FColor::Purple);

}

void UleePanelBase::lOverrideTextName(TArray<FString> texts, TArray<UleeBaseButton*> btns)
{

	if (btns.Num() <= 0 || texts.Num() <= 0 ) return;
	for (int i = 0; i < texts.Num(); i++) {
		if (btns[i])	btns[i]->lSetText(texts[i]);
	}
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

void UleePanelBase::lSetAutoFill(UleeDragWidget*& btn, bool isAuto)
{
	//UCanvasPanelSlot* vSlot = Cast<UCanvasPanelSlot>(btn->Slot);
	//if (vSlot) {
	//	vSlot->SetR;
	//	vSlot->SetHorizontalAlignment(HAlign_Fill);
	//}
}

template<class T>
T* UleePanelBase::lExistsWidget(UPanelWidget* Parent, FString& name, bool status)
{
	//check file exits
	bool Success{};
	TArray<UWidget*> widgets = Parent->GetAllChildren();
	if (widgets.Num() <= 0) return nullptr;

	//loop find
#pragma omp parallel for
	for (auto wd : widgets) {
		FString wName = wd->GetFName().ToString();
		if (wName == name) { return Cast<T>(wd); }
		UPanelWidget* box = Cast<UPanelWidget>(wd);

		if (box) {
			Success = lExistsWidget<T>(box, name, status);
			if (Success) { return nullptr; }

		}
	}
	return nullptr;
}

void UleePanelBase::NativeConstruct()
{
	
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
	if (!lExistsDirectory(lDirectory)) return;

	//preview UI
	lInitializePanels(lDirectory,lpaneltype , ImageOnly);
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
}

UleeBaseButton* UleePanelBase::lCreateButton(FString imgPath, bool ImgOnly, bool isDrop, FString text,bool isDrag,int32 rID)
{
	UleeBaseButton* wid = CreateWidget<UleeBaseButton>(GetWorld(), lRuntimeButton);
	if (!wid) return nullptr;
	//------------------------------------
	int32 cCount = lPanelWidget->GetChildrenCount(); 
	lPanelWidget->AddChild(wid);

	wid->lInitialized(imgPath, text, ImgOnly);
	wid->lSetTextVisibility(ImgOnly);
	lbuttons.Add(wid);
	wid->lDrop = isDrop;
	wid->lDrag = isDrag;
	wid->rowID = rID;
	return wid;
}

UleeDragWidget* UleePanelBase::lCreateDragButton(FString imgPath, bool ImgOnly, bool isDrop, FString text, int32 rID)
{

	UleeDragWidget* wid = CreateWidget<UleeDragWidget>(GetWorld(), lRuntimeButton);

	if (!wid) return nullptr;
	int32 cCount = lPanelWidget->GetChildrenCount();
	lPanelWidget->AddChild(wid);

	lSetUpdateSizeRules(wid->Slot, ESlateSizeRule::Fill);
	wid->lIsDrop = isDrop;
	wid->lSetTexture(imgPath);
	wid->lSetId(rID);

	return wid;
}
