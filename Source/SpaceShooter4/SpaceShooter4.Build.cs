// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SpaceShooter4 : ModuleRules
{
	public SpaceShooter4(ReadOnlyTargetRules Target) : base(Target)
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
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"SpaceShooter4",
			"SpaceShooter4/Variant_Platforming",
			"SpaceShooter4/Variant_Combat",
			"SpaceShooter4/Variant_Combat/AI",
			"SpaceShooter4/Variant_SideScrolling",
			"SpaceShooter4/Variant_SideScrolling/Gameplay",
			"SpaceShooter4/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
