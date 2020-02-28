// Dmitriy Barannik aka redbox, 2020

#include "Components/Operations/IPOperationAlignBase.h"

UIPOperationAlignBase::UIPOperationAlignBase()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	bAlignToSurface = false;
	bReverse = false;
	bTraceComplex = false;
	bIgnoreSelf = true;
	DrawTime = 5.f;
#endif
}