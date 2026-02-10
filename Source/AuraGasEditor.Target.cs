// Copyright LCC Personal

using UnrealBuildTool;
using System.Collections.Generic;

public class AuraGasEditorTarget : TargetRules
{
	public AuraGasEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "AuraGas" } );
	}
}
