// MIT License Copyright(c) 2017 Nicolas Hamard
using UnrealBuildTool;
using System.Collections.Generic;

public class DejavonTarget : TargetRules
{
	public DejavonTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Dejavon" } );
	}
}
