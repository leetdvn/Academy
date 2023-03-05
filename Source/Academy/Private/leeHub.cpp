// Fill out your copyright notice in the Description page of Project Settings.

#include "leeHub.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include <leePanelBase.h>

class UKidWidget;

AleeHub::AleeHub()
{
	lOnGStart.AddDynamic(this, &AleeHub::OnGameStart);
}

void AleeHub::BeginPlay()
{
	Super::BeginPlay();
	
	if (!lMenuWidget) return;

	FString map = UGameplayStatics::GetCurrentLevelName(GetWorld());// ->GetMapName();
	TSubclassOf<UUserWidget> panel;// = map.EndsWith("AMenu") ? lMenuWidget : lThreeLine;

	if (map.EndsWith("AMenu"))
		panel = lMenuWidget;
	else if (map.EndsWith("ThreeLines"))
		panel = lThreeLine;
	//else if (map.EndsWith("AlphaBet"))
	//	panel = lFourBox;
	else if (map.EndsWith("FourBox"))
		panel = lFourBox;

	//Create Menu
	if (!panel) return;
	lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), panel);
	//add to view port

	if (lCurrentWidget) {
		lCurrentWidget->AddToViewport();
		UPanelWidget* parent= lCurrentWidget->GetRootWidget()->GetParent();
		//lget
		//GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		//FVector2D resolution = lScreenResolution();
	}
	//active Event start game

}

void AleeHub::Tick(float DeltaTime)
{
	//double x{}, y{};
}

void AleeHub::lSetGameWidgets(int index)
{
	//if (index >= lGameWidgets.Num()) return;
	//lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), lGameWidgets[index]);
	//if (lCurrentWidget != nullptr) {
	//	lCurrentWidget->AddToViewport();
	//}


}

int AleeHub::lGetlGameWidgets()
{
	return 0;
}

void AleeHub::OnGameStart()
{
	lOnGStart.Broadcast();
}

void AleeHub::OnChangeClick()
{
	//leeTdDebug("Event Dispatcher");
}

void AleeHub::Onlevelchanged()
{
	onlevelChanged.Broadcast();
}
