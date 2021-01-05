// redbox, 2021

#include "InstancedPluginEditor.h"
#include "InstancedPluginEditorCommands.h"
#include "LevelEditor.h"
#include "Objects/IPEFunctionLibrary.h"

#define LOCTEXT_NAMESPACE "FInstancedPluginEditorModule"

DEFINE_LOG_CATEGORY(IPELog);

void FInstancedPluginEditorModule::StartupModule()
{
	FInstancedPluginEditorCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FInstancedPluginEditorCommands::Get().PluginCommand0,
		FExecuteAction::CreateRaw(this, &FInstancedPluginEditorModule::PluginAction0),
		FCanExecuteAction()
	);

	PluginCommands->MapAction(
		FInstancedPluginEditorCommands::Get().PluginCommand1,
		FExecuteAction::CreateRaw(this, &FInstancedPluginEditorModule::PluginAction1),
		FCanExecuteAction()
	);

	PluginCommands->MapAction(
		FInstancedPluginEditorCommands::Get().PluginCommand2,
		FExecuteAction::CreateRaw(this, &FInstancedPluginEditorModule::PluginAction2),
		FCanExecuteAction()
	);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Content",
			EExtensionHook::Before,
			PluginCommands,
			FToolBarExtensionDelegate::CreateRaw(this, &FInstancedPluginEditorModule::AddToolbarButton));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FInstancedPluginEditorModule::ShutdownModule()
{
	FInstancedPluginEditorCommands::Unregister();
}

void FInstancedPluginEditorModule::PluginAction0()
{
	UIPEFunctionLibrary::ConvertStaticMeshesToInstances();
}

void FInstancedPluginEditorModule::PluginAction1()
{
	UIPEFunctionLibrary::ConvertInstancesToStaticMeshes();
}

void FInstancedPluginEditorModule::PluginAction2()
{
	UIPEFunctionLibrary::CheckNegativeScale();
}

void FInstancedPluginEditorModule::AddToolbarButton(FToolBarBuilder& ToolbarBuilder)
{
	ToolbarBuilder.AddToolBarButton(FInstancedPluginEditorCommands::Get().PluginCommand0);

	FUIAction TempCompileOptionsCommand;

	ToolbarBuilder.AddComboButton(
		TempCompileOptionsCommand,
		FOnGetContent::CreateRaw(this, &FInstancedPluginEditorModule::FillComboButton, PluginCommands),
		LOCTEXT("InstancedPlugin", "Instanced Plugin"),
		LOCTEXT("InstancedPluginCommands", "Instanced Plugin Commands"),
		TAttribute<FSlateIcon>(),
		true
	);
}

TSharedRef<SWidget> FInstancedPluginEditorModule::FillComboButton(TSharedPtr<class FUICommandList> Commands)
{
	FMenuBuilder MenuBuilder(true, Commands);
	MenuBuilder.AddMenuEntry(FInstancedPluginEditorCommands::Get().PluginCommand1);
	MenuBuilder.AddMenuEntry(FInstancedPluginEditorCommands::Get().PluginCommand2);
	return MenuBuilder.MakeWidget();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FInstancedPluginEditorModule, InstancedPluginEditor)
