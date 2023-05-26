#pragma once

#include "leeEnvironment.h"
#include "leeBaseLessions.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "leelineEnvironment.generated.h"


UCLASS(BlueprintType, Blueprintable)
class ACADEMY_API UleelineEnvironment : public UleeBaseLessions
{
	GENERATED_BODY()

public:


	virtual void OnIDrop(bool isCorrect) override;

	virtual void NewGameThreelineInit() override;

protected:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "lee's Ultils")
		UleeEnvironment* lineEnvi;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
};