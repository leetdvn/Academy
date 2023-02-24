#pragma once

//#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"

class UleeBaseButton;
class UDragDropOperation;
/// <summary>
/// static delegate
/// </summary>
namespace UIleeDelegate {

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCorrectDrop, UDragDropOperation*);
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		extern FOnCorrectDrop OnCorrectDrop;

};