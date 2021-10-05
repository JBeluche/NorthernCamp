// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NorthernCamp : ModuleRules
{
	public NorthernCamp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		//Stuff I added:
		//	Landscape: needed in the Loose Pawn Camera to cast to landscape 
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "Landscape", "AIModule" });
        

        
        
    }
}
