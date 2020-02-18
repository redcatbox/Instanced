// Dmitriy Barannik aka redbox, 2020

#include "InstancedPluginCommands.h"
#include "InstancedPlugin.h"

#define LOCTEXT_NAMESPACE "FInstancedPluginEditorModule"

void FInstancedPluginCommands::RegisterCommands()
{
	UI_COMMAND(PluginCommand0,
		"ConvertStaticMeshesToInstances",
		"Convert selected StaticMeshActors or actors with StaticMeshComponents to instances",
		EUserInterfaceActionType::Button,
		FInputGesture());

	UI_COMMAND(PluginCommand1,
		"ConvertInstancesToStaticMeshes",
		"Convert selected instances to static meshes",
		EUserInterfaceActionType::Button,
		FInputGesture());

	UI_COMMAND(PluginCommand2,
		"CheckNegativeScaleValues",
		"Check selected actors and instances contain negative scale values",
		EUserInterfaceActionType::Button,
		FInputGesture());
}

#undef LOCTEXT_NAMESPACE