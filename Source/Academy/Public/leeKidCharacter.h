// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "leePublicInterface.h"
#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "leeBaseLessions.h"
#include <Components/TextRenderComponent.h>
#include "leeKidCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ACADEMY_API AleeKidCharacter : public APaperCharacter , public IleePublicInterface
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UTextRenderComponent* TextComponent;
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
protected:
	// The animation to play while running around
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	//	class UPaperFlipbook* RunningAnimation;

	//// The animation to play while idle (standing still)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	//	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		TSubclassOf<UUserWidget> lMenuWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "lee's Ultils")
		TSubclassOf<UUserWidget> lLession;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called for side to side input */
	void MoveRight(float Value);

	void UpdateCharacter();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	AleeKidCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UUserWidget* lCurrentWidget;

};
