// Copyright LCC Personal

using UnrealBuildTool;
using System.Collections.Generic;

public class AuraGasEditorTarget : TargetRules
{
	public AuraGasEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V7;
		bOverrideBuildEnvironment = true;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;

		ExtraModuleNames.AddRange( new string[] { "AuraGas" } );
	}
}
