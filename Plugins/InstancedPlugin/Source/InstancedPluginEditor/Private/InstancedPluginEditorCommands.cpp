// redbox, 2021

#include "InstancedPluginEditorCommands.h"

#define LOCTEXT_NAMESPACE "FInstancedPluginEditorModule"

void FInstancedPluginEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginCommand0,
		"Convert static meshes to instances",
		"Replace selected StaticMeshActors or actors containing StaticMeshComponents with instances",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(PluginCommand1,
		"Convert instances to static meshes",
		"Replace selected instances with static meshes",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(PluginCommand2,
		"Check negative scale",
		"Check selected actors and instances for containing negative scale values",
		EUserInterfaceActionType::Button,
		FInputChord());
}

#undef LOCTEXT_NAMESPACE
