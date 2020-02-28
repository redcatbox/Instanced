// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Framework/Commands/UIAction.h"

class FToolBarBuilder;
class FMenuBuilder;
class FReply;
class SWidget;

class FInstancedPluginEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void PluginAction0();
	void PluginAction1();
	void PluginAction2();

private:
	TSharedPtr<FUICommandList> PluginCommands;
	TSharedRef<SWidget> FillComboButton(TSharedPtr<class FUICommandList> Commands);

	void AddToolbarButton(FToolBarBuilder& ToolBarBuilder);
};