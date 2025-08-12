


using UnrealBuildTool;

public class ProjectAGEditor : ModuleRules
{
    public ProjectAGEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Core", 
            "CoreUObject",
            "Engine",
            "Slate", 
            "SlateCore",
            "AnimationEditor",
            "UnrealEd",
            "ProjectAG",
        });
    }
}