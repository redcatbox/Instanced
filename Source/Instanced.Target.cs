// redbox, 2022

using UnrealBuildTool;
using System.Collections.Generic;

public class InstancedTarget : TargetRules
{
	public InstancedTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
        ExtraModuleNames.Add("Instanced");
	}
}
