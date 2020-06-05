// redbox, 2020

#include "Components/Operations/IPOperationAlignBase.h"

UIPOperationAlignBase::UIPOperationAlignBase()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	bAlignToSurface = false;
	OffsetInTraceDirection = 0.f;
	bReverse = false;
	bTraceComplex = false;
	bIgnoreSelf = true;
	DrawTime = 5.f;
#endif
}