// Fill out your copyright notice in the Description page of Project Settings.


#include "leeDecorPanel.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"

void UleeDecorPanel::DecorInit(FString pathdecor)
{
	if (pathdecor.IsEmpty()) return;
	float distX{};
	float minX = (-768 / 2);
	float maxX = FMath::Abs(minX);
	float Avr = 768 / Number +1;
	if (DecorImgs.Num() > 0)
		DecorPanel->ClearChildren();

	/*paht imgae decoration*/

	for (int i = 0; i < Number; i++) {
		FString objName = "Decor_" + FString::FromInt(i);
		UImage* img = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(),FName(*objName));// NewObject<UImage>(UImage::StaticClass());
		UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(DecorPanel->AddChild(img));
		if (slot) {
			//UE_LOG(LogTemp, Warning, TEXT("info : %s"), *texPath);
			UTexture2D* tex = lGetTextureFromPath(pathdecor);
			if (tex) {
				float halfTex = tex->GetSizeY() / 1.5f;
				float RandMulti = FMath::RandRange(0.4f, 1.2f);
				img->SetBrushFromTexture(tex, true);
				FVector2D sizeRand = FVector2D(tex->GetSizeX()*RandMulti,tex->GetSizeY()*RandMulti);
				img->SetBrushSize(sizeRand);
				slot->SetAlignment(FVector2D{ .5,.5 });
				slot->SetAnchors(FAnchors{ 0.5,0.5 });
				float RandY = lRand(-45 , 45);
				//slot->bAutoSize = true;
				/*float max = FMath::Abs(min);*/
				float plusRand = lRand(halfTex, 100.0);
				UE_LOG(LogTemp, Warning, TEXT("abc : %f"), Avr);

				distX += i == 0 ? minX +halfTex: Avr;
				//if (distX > FMath::Abs(hX))
				//	distX = FMath::Abs(hX) - tex->GetSizeX()/2;
				slot->SetAutoSize(true);


				slot->SetPosition(FVector2D{ distX,RandY});
				//if(distX < FMath::Abs())
				//distX += lRand(tex->GetSizeX(), 200);
			}
		}
		DecorImgs.Add(img);
	}
}

FString UleeDecorPanel::PathInit()
{
	FString path = FPaths::ProjectContentDir() + PathDecor;
	FString result = lGetRandFileFromDirectory(path);
	return  decorPath= "/Game/" + PathDecor + result;
}

//void UleeDecorPanel::NativePreConstruct()
//{
//
//	//UE_LOG(LogTemp,Warning,TEXT("test Decor  : %s"), *result);
//}
//
void UleeDecorPanel::NativeConstruct()
{
	PathInit();
}
