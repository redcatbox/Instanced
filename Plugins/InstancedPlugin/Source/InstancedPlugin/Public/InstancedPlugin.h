// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;

class FInstancedPluginModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void PluginAction0();
	void PluginAction1();
	void PluginAction2();

private:
	void AddToolbarExtension(FToolBarBuilder& Builder);
	TSharedPtr<FUICommandList> PluginCommands;
};