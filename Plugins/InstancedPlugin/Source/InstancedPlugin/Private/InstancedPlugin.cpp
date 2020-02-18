// Dmitriy Barannik aka redbox, 2020

#include "InstancedPlugin.h"
#include "InstancedPluginCommands.h"
#include "LevelEditor.h"
#include "Objects/IPFunctionLibrary.h"

#define LOCTEXT_NAMESPACE "FInstancedPluginModule"

void FInstancedPluginModule::StartupModule()
{
	FInstancedPluginCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FInstancedPluginCommands::Get().PluginCommand0,
		FExecuteAction::CreateRaw(this, &FInstancedPluginModule::PluginAction0),
		FCanExecuteAction()
	);

	PluginCommands->MapAction(
		FInstancedPluginCommands::Get().PluginCommand1,
		FExecuteAction::CreateRaw(this, &FInstancedPluginModule::PluginAction1),
		FCanExecuteAction()
	);

	PluginCommands->MapAction(
		FInstancedPluginCommands::Get().PluginCommand2,
		FExecuteAction::CreateRaw(this, &FInstancedPluginModule::PluginAction2),
		FCanExecuteAction()
	);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{
		//TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		//MenuExtender->AddMenuExtension("FileProject",
		//	EExtensionHook::After,
		//	PluginCommands,
		//	FMenuExtensionDelegate::CreateRaw(this, &FInstancedPluginModule::AddMenuExtension));
		//LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Content",
			EExtensionHook::Before,
			PluginCommands,
			FToolBarExtensionDelegate::CreateRaw(this, &FInstancedPluginModule::AddToolbarExtension));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FInstancedPluginModule::ShutdownModule()
{
	FInstancedPluginCommands::Unregister();
}

//void FInstancedPluginModule::AddMenuExtension(FMenuBuilder& Builder)
//{
//	Builder.AddMenuEntry(FInstancedPluginCommands::Get().PluginCommand0);
//	Builder.AddMenuEntry(FInstancedPluginCommands::Get().PluginCommand1);
//	Builder.AddMenuEntry(FInstancedPluginCommands::Get().PluginCommand2);
//}

void FInstancedPluginModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FInstancedPluginCommands::Get().PluginCommand0);
	Builder.AddToolBarButton(FInstancedPluginCommands::Get().PluginCommand1);
	Builder.AddToolBarButton(FInstancedPluginCommands::Get().PluginCommand2);
}

void FInstancedPluginModule::PluginAction0()
{
	UIPFunctionLibrary::ConvertStaticMeshesToInstances();
}

void FInstancedPluginModule::PluginAction1()
{
	UIPFunctionLibrary::ConvertInstancesToStaticMeshes();
}

void FInstancedPluginModule::PluginAction2()
{
	UIPFunctionLibrary::CheckNegativeScaleValues();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FInstancedPluginModule, InstancedPlugin)