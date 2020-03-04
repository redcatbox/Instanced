// Dmitriy Barannik aka redbox, 2020

#include "InstancedPlugin.h"

#define LOCTEXT_NAMESPACE "FInstancedPluginModule"

DEFINE_LOG_CATEGORY(IPLog);

void FInstancedPluginModule::StartupModule()
{

}

void FInstancedPluginModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FInstancedPluginModule, InstancedPlugin)