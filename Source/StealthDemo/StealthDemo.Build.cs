// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class StealthDemo : ModuleRules
{
	public StealthDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject",
			"Engine", 
			"InputCore", 
			"AIModule", 
			"GameplayTasks",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] {
			"StealthDemo/Public",
			"StealthDemo/Public/AI",
			"StealthDemo/Public/Components",
			"StealthDemo/Public/AI/Senses",
			"StealthDemo/Public/AI/Services",
			"StealthDemo/Public/InteractiveObjects"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
