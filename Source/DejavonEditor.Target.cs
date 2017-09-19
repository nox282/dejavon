// MIT License Copyright(c) 2017 Nicolas Hamard
using UnrealBuildTool;
using System.Collections.Generic;

public class DejavonEditorTarget : TargetRules
{
	public DejavonEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Dejavon" } );
	}
}
