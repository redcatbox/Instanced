// redbox, 2021

#pragma once

#include "SlateBasics.h"
#include "EditorStyleSet.h"

class FInstancedPluginEditorCommands : public TCommands<FInstancedPluginEditorCommands>
{
public:
	FInstancedPluginEditorCommands()
		: TCommands<FInstancedPluginEditorCommands>
		(
			TEXT("InstancedPluginEditor"),
			NSLOCTEXT("Contexts", "InstancedPluginEditor", "InstancedPluginEditor Plugin"),
			NAME_None,
			FEditorStyle::GetStyleSetName()
		) {}

	virtual void RegisterCommands() override;
	TSharedPtr<FUICommandInfo> PluginCommand0;
	TSharedPtr<FUICommandInfo> PluginCommand1;
	TSharedPtr<FUICommandInfo> PluginCommand2;
};
