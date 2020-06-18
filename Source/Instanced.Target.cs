// redbox, 2020

using UnrealBuildTool;
using System.Collections.Generic;

public class InstancedTarget : TargetRules
{
	public InstancedTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Instanced");
	}
}