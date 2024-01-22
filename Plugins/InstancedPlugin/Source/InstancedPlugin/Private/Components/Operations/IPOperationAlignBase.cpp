// redbox, 2022

#include "Components/Operations/IPOperationAlignBase.h"

UIPOperationAlignBase::UIPOperationAlignBase()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCond = false;
	bAlignToSurface = false;
	OffsetInTraceDirection = 0.f;
	bReverse = false;
	bTraceComplex = false;
	bIgnoreSelf = true;
	DrawTime = 5.f;
#endif
}
