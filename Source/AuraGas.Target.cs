// Copyright LCC Personal

using UnrealBuildTool;
using System.Collections.Generic;

public class AuraGasTarget : TargetRules
{
	public AuraGasTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "AuraGas" } );
	}
}
