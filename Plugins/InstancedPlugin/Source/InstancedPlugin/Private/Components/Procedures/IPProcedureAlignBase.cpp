// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureAlignBase.h"

UIPProcedureAlignBase::UIPProcedureAlignBase()
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