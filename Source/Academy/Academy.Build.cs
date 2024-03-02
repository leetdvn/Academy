// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Academy : ModuleRules
{
	public Academy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add("C:/Program Files/Epic Games/UE_4.27/Engine/Plugins/Online/OnlineSubsystemFacebook/Source/Public");

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","UMG" ,"JSon", "JsonUtilities", "Paper2D" ,
            "OnlineSubsystemUtils",
            "FirebaseAuthentication",
            "OnlineSubsystemFacebook",
            "FirebaseGoodies",
            "leeUltilities",
            "Niagara",
            "OnlineSubsystem",
        });


		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore",  });

        //Add IOS if you're using it
        if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        {
            //Facebook API
            PublicDependencyModuleNames.AddRange(new string[] { "Facebook" });
            //Facebook Subsystem
            PrivateDependencyModuleNames.Add("OnlineSubsystemFacebook");

        }    // Uncomment if you are using online features
        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicDependencyModuleNames.AddRange(new string[] {"Launch"});
            PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "OnlineSubsystem" , });
            PrivateDependencyModuleNames.Add("AndroidAdvertising");
            DynamicallyLoadedModuleNames.Add("OnlineSubsystemGooglePlay");
            //string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            //AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "Academy_APL.xml"));

        }
    }
}
