// redbox, 2022

#include "IPDetailsCustomization.h"
#include "DetailLayoutBuilder.h"

#define LOCTEXT_NAMESPACE "FInstancedPluginEditorModule"

TSharedRef<IDetailCustomization> FIPDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FIPDetailsCustomization);
}

void FIPDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{

}

#undef LOCTEXT_NAMESPACE
