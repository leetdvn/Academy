#include "leeAccoutAuthenication.h"

UleeAccoutAuthenication::UleeAccoutAuthenication(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UleeAccoutAuthenication::OnGoogleClicked()
{
	//UFirebaseAuthenticationSubsystem* fire = NewObject<UFirebaseAuthenticationSubsystem>(UFirebaseAuthenticationSubsystem::StaticClass());
	//fire->GoogleSignIn(OnGoogleSignin);
	//UFirebaseAuthenticationSubsystem::GoogleSignIn(OnGoogleSignin);
	lDebug("On Google");
}

void UleeAccoutAuthenication::OnFaceBoockClicked()
{
	//UFirebaseAuthenticationSubsystem::FacebookSignIn(OnFacebookSignin);
}

void UleeAccoutAuthenication::OnAppleClicked()
{
	//UFirebaseAuthenticationSubsystem::OAuthSignIn(OnAppleSignin, OAuth);
}

void UleeAccoutAuthenication::lToogleVisible()
{
	ESlateVisibility vis = GetVisibility() == ESlateVisibility::SelfHitTestInvisible ?
		ESlateVisibility::Hidden :
		ESlateVisibility::SelfHitTestInvisible;
	SetVisibility(vis);
}

void UleeAccoutAuthenication::NativeConstruct()
{
	//UFirebaseAuthenticationSubsystem::FacebookSignIn(OnFacebookSignin);

#if PLATFORM_ANDROID
	IOSPanel->SetVisibility(ESlateVisibility::Hidden);
	if (AndroidPanel->GetVisibility() == ESlateVisibility::Hidden)
		AndroidPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
#elif PLATFORM_IOS
	AndroidPanel->SetVisibility(ESlateVisibility::Hidden);
	if (IOSPanel->GetVisibility() == ESlateVisibility::Hidden)
		IOSPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
#endif

	black_bgr->OnMouseButtonDownEvent.BindUFunction(this, FName("lToogleVisible"));
	//bind button
	//Facebook_btn->OnClicked.AddDynamic(this, &UleeAccoutAuthenication::OnFaceBoockClicked);
	//Google_btn->OnClicked.AddDynamic(this, &UleeAccoutAuthenication::OnGoogleClicked);
	//AppleID_btn->OnClicked.AddDynamic(this, &UleeAccoutAuthenication::OnAppleClicked);

}

void UleeAccoutAuthenication::NativeDestruct()
{
	if (black_bgr->OnMouseButtonDownEvent.IsBound())
		black_bgr->OnMouseButtonDownEvent.Clear();
}

