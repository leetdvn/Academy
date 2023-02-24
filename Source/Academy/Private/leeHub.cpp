// Fill out your copyright notice in the Description page of Project Settings.

#include "leeHub.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

class UKidWidget;

AleeHub::AleeHub()
{
	lOnGStart.AddDynamic(this, &AleeHub::OnGameStart);
}

void AleeHub::BeginPlay()
{
	Super::BeginPlay();
	
	if (!lMenuWidget) return;

	FString map = GetWorld()->GetMapName();
	TSubclassOf<UUserWidget> panel = map.EndsWith("AMenu") ? lMenuWidget : lMove;
	//Create Menu
	lCurrentWidget = CreateWidget<UUserWidget>(GetWorld(), panel);
	//add to view port

	if (lCurrentWidget) {
		lCurrentWidget->AddToViewport();
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
	//active Event start game

	//if (lMove) {
	//	lMoveButton = CreateWidget<UUserWidget>(GetWorld(), lMove);

	//	lDebug(lCurrentWidget->GetRootWidget()->GetName());
	//	//lMoveButton->AddToViewport();
	//}
	//UleeBaseWidget* wdget = Cast<UleeBaseWidget>(lCurrentWidget);
	//if (wdget) {
	//	//wdget->execOnBtnClicked.AddDyanmic(this,&ALeetdHUD::OnChangeClick);
	//	wdget->lOnClicked.AddDynamic(this, &ALeetdHUD::OnChangeClick);
	//	leeTdDebug("begin play 1");

	//}

	//static ConstructorHelpers::FObjectFinder<UBlueprint> explosionBlueprint(TEXT("Blueprint'/Game/Blueprint/BP_leeButton'"));

	//if (explosionBlueprint.Object != NULL)
	//{
	//	UClass* uclass = explosionBlueprint.Object->GeneratedClass;
	//}
}

void AleeHub::Tick(float DeltaTime)
{
	double x{}, y{};
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
