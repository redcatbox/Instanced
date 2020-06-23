// redbox, 2020

using UnrealBuildTool;
using System.Collections.Generic;

public class InstancedEditorTarget : TargetRules
{
	public InstancedEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Instanced");
	}
}
