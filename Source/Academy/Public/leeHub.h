// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Components/Image.h>
#include "leePublicInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "leeHub.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGamePause);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEnd);

/**
 * 
 */
UCLASS()
class ACADEMY_API AleeHub : public AHUD, public IleePublicInterface
{
	GENERATED_BODY()
public:
	AleeHub();
	//override game begien
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

#pragma region UFUNCTION / PROPERTY UE
	/// <summary>
	/// Menu Widgets
	/// </summary>
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
	TSubclassOf<UUserWidget> lMenuWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		TSubclassOf<UUserWidget> lMove;

	/// <summary>
	/// Widget ingame list
	/// </summary>
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
	TArray<TSubclassOf<class UUserWidget>> lGameWidgets;

	/// <summary>
	/// switch widget 
	/// </summary>
	/// <param name="index"></param>
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
	void lSetGameWidgets(int index);
	/// <summary>
	/// get index 
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
	int lGetlGameWidgets();

	///
	DECLARE_EVENT(ALeetdHUD,LevelChanged)
		LevelChanged& OnLevelChanged() { return onlevelChanged; }

	UFUNCTION()
		void OnGameStart();

	UPROPERTY(BlueprintAssignable, Category = "Test")
		FOnGameStart lOnGStart;
	UUserWidget* lCurrentWidget;


#pragma endregion

protected:
	UWorld* leeWorld;
	class UUserWidget* MenuWidget;
	UFUNCTION()
	void OnChangeClick();
	void Onlevelchanged();
	FOnGamePause lOnGPause;
	FOnGameEnd lOnGEnd;
	LevelChanged onlevelChanged;

	UUserWidget* lMoveButton;

};
