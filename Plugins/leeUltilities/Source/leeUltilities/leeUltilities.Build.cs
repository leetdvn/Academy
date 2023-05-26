// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class leeUltilities : ModuleRules
{
	public leeUltilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UMG",
				"Json",
                "InputCore",
                "JsonUtilities",
                "UMG",
				"Networking",
				"Sockets",

				// ... add other public dependencies that you statically link with here ...
			}
            );
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        PrivateIncludePathModuleNames.Add("Settings");
        //PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        //PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Interfaces"));

        /*Android Platform*/
        if (Target.Platform == UnrealTargetPlatform.Android)
		{
            PrivateDependencyModuleNames.AddRange(new string[] { "Core", "Engine", "Slate", "SlateCore", "Launch" });
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "leeUltilities_APL.xml"));

        }
    }
}
