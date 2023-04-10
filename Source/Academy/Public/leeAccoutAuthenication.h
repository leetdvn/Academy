#pragma once
#include <FirebaseAuthenticationSubsystem.h>
#include <Components/Image.h>
#include "leePublicInterface.h"
#include "Components/Button.h"
#include <Components/PanelWidget.h>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "leeAccoutAuthenication.generated.h"

UCLASS(BlueprintType)
class ACADEMY_API UleeAccoutAuthenication : public UUserWidget, public IleePublicInterface
{
	GENERATED_BODY()
public:
	UleeAccoutAuthenication(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Bgr", meta = (BindWidget));
		UImage* black_bgr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Facebook Sign in", meta = (BindWidget));
		UButton* Facebook_btn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "AppleID  Sign in", meta = (BindWidget));
		UButton* AppleID_btn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Google Sign in", meta = (BindWidget));
		UButton* Google_btn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Android panel", meta = (BindWidget));
		UPanelWidget* AndroidPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "lee's Ultils", DisplayName = "Android panel", meta = (BindWidget));
		UPanelWidget* IOSPanel;

	UPROPERTY()
		FOnGoogleAuthenticationCompleted OnGoogleSignin;

	//UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	//	FOnFirebaseAuthenticationCompleted OnFacebookSignin;

	//UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	//	FOnFirebaseAuthenticationCompleted OnAppleSignin;


	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void OnGoogleClicked();
	
	UFUNCTION()
		void OnFaceBoockClicked();

	UFUNCTION()
		void OnAppleClicked();

	UFUNCTION(BlueprintCallable, Category = "lee's Ultils")
		void lToogleVisible();

protected:

	virtual void NativeConstruct() override;
};
