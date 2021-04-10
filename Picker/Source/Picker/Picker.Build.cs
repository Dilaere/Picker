// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Picker : ModuleRules
{
	public Picker(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
