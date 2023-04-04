// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Academy : ModuleRules
{
	public Academy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","UMG" ,"JSon", "JsonUtilities", "Paper2D" ,
            "OnlineSubsystem", "OnlineSubsystemUtils", "Networking", "Sockets",
            "FirebaseAuthentication",
            "OnlineSubsystemFacebook",
            "FirebaseGoodies",
            "leeUltilities",
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemGooglePlay");

        PublicIncludePaths.Add("F:/Epic Games/UE_4.27/Engine/Plugins/Online/OnlineSubsystemFacebook/Source/Public");
        //Add IOS if you're using it
        if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        {
            //Facebook API
            PublicDependencyModuleNames.AddRange(new string[] { "Facebook" });
            //Facebook Subsystem
            PrivateDependencyModuleNames.Add("OnlineSubsystemFacebook");

            //Include
            //PublicIncludePaths.Add("Runtime/Online/OnlineSubsystemFacebook/Public");
            //PublicIncludePaths.Add("Runtime/Online/OnlineSubsystemFacebook/Private/Windows");
        }    // Uncomment if you are using online features
             // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
