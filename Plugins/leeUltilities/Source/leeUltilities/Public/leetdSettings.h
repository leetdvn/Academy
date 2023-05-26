#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "leetdSettings.generated.h"

UCLASS(Config = Engine, DefaultConfig)
class LEEULTILITIES_API UleetdSettings : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, Category = "leeUltilities")
		FString AdsAppId;

	UPROPERTY(Config, EditAnywhere, Category = "leeUltilities")
		TArray<FString> BannerUnitId;

	UPROPERTY(Config, EditAnywhere, Category = "leeUltilities")
		TArray<FString> InterstitialUnitId;

	UPROPERTY(Config, EditAnywhere, Category = "leeUltilities")
		TArray<FString> RewardsUnitId;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override {
		Super::PostEditChangeProperty(PropertyChangedEvent);

		/*Update On Property Changed*/
		if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UleetdSettings, AdsAppId))
		{
			FString StrRef;
			//AdsAppId.Split(".json", &AdsAppId, &StrRef, ESearchCase::IgnoreCase);
			//SettingsFileID.Split("cas_settings", &StrRef, &SettingsFileID, ESearchCase::IgnoreCase);
			UpdateSinglePropertyInConfigFile(GetClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UleetdSettings, AdsAppId)), GetDefaultConfigFilename());
			UpdateSinglePropertyInConfigFile(GetClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UleetdSettings, BannerUnitId)), GetDefaultConfigFilename());
			UpdateSinglePropertyInConfigFile(GetClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UleetdSettings, InterstitialUnitId)), GetDefaultConfigFilename());
			UpdateSinglePropertyInConfigFile(GetClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UleetdSettings, RewardsUnitId)), GetDefaultConfigFilename());

		}


	}
#endif
};
