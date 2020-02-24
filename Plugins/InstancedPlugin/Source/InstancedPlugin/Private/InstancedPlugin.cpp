// Dmitriy Barannik aka redbox, 2020

#include "InstancedPlugin.h"
#include "InstancedPluginCommands.h"
#include "LevelEditor.h"
//#include "ToolMenus/Public/ToolMenus.h"
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

	//UToolMenu* ToolbarBuilder = UToolMenus::Get()->RegisterMenu("LevelEditor.LevelEditorToolBar", NAME_None, EMultiBoxType::ToolBar);

	//FToolMenuSection& SettingsSection = ToolbarBuilder->AddSection("Instanced");
	//{
	//	SettingsSection.AddEntry(FToolMenuEntry::InitComboButton(
	//		"LevelToolbarQuickSettings",
	//		FUIAction(),
	//		FOnGetContent::CreateStatic(&FLevelEditorToolBar::GenerateQuickSettingsMenu, InCommandList),
	//		LOCTEXT("QuickSettingsCombo", "Settings"),
	//		LOCTEXT("QuickSettingsCombo_ToolTip", "Project and Editor settings"),
	//		FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.GameSettings"),
	//		false,
	//		"LevelToolbarQuickSettings"
	//	));
	//}

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{
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

void FInstancedPluginModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.BeginSection(TEXT("Instanced"));
	Builder.AddToolBarButton(FInstancedPluginCommands::Get().PluginCommand0);
	Builder.AddToolBarButton(FInstancedPluginCommands::Get().PluginCommand1);
	Builder.AddToolBarButton(FInstancedPluginCommands::Get().PluginCommand2);
	Builder.EndSection();
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
	UIPFunctionLibrary::CheckNegativeScale();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FInstancedPluginModule, InstancedPlugin)