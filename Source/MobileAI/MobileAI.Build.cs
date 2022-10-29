// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MobileAI : ModuleRules
{
	public MobileAI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
        
        // PublicIncludePaths.AddRange(new string[] { "Characters" });
    }
}
