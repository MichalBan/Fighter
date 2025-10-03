// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Fighter : ModuleRules
{
	public Fighter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Fighter",
			"Fighter/Variant_Platforming",
			"Fighter/Variant_Platforming/Animation",
			"Fighter/Variant_Combat",
			"Fighter/Variant_Combat/AI",
			"Fighter/Variant_Combat/Animation",
			"Fighter/Variant_Combat/Gameplay",
			"Fighter/Variant_Combat/Interfaces",
			"Fighter/Variant_Combat/UI",
			"Fighter/Variant_SideScrolling",
			"Fighter/Variant_SideScrolling/AI",
			"Fighter/Variant_SideScrolling/Gameplay",
			"Fighter/Variant_SideScrolling/Interfaces",
			"Fighter/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
