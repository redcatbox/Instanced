// redbox, 2022

using UnrealBuildTool;
using System.Collections.Generic;

public class InstancedEditorTarget : TargetRules
{
	public InstancedEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("Instanced");
	}
}
