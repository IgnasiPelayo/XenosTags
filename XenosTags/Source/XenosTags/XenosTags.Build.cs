// Copyright (c) Ignasi Pelayo, 2023. All Rights Reserved.

using UnrealBuildTool;

public class XenosTags : ModuleRules
{
	public XenosTags(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
		});
	}
}
