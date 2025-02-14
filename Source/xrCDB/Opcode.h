﻿///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *	OPCODE - Optimized Collision Detection
 *	Copyright (C) 2001 Pierre Terdiman
 *	Homepage: http://www.codercorner.com/Opcode.htm
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Main file for Opcode.dll.
 *	\file		Opcode.h
 *	\author		Pierre Terdiman
 *	\date		March, 20, 2001
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __OPCODE_H__
#define __OPCODE_H__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Preprocessor
#define OPCODE_API
#ifndef __ICECORE_H__
#ifdef WIN32
#include <windows.h>
#include <windowsx.h>
#endif   // WIN32

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>

#ifndef ASSERT
#define ASSERT assert
#endif

#define Log
#define SetIceError    false
#define EC_OUTOFMEMORY "Out of memory"
#define Alignment

#include "OPC_Preprocessor.h"
#define ICECORE_API OPCODE_API

#include "OPC_Types.h"
#include "OPC_FPU.h"
#include "OPC_MemoryMacros.h"
namespace IceCore
{
#include "OPC_Container.h"
}
using namespace IceCore;
#endif

#ifndef __ICEMATHS_H__
#include <Math.h>
#define ICEMATHS_API OPCODE_API
namespace IceMaths
{
#include "OPC_Point.h"
#include "OPC_Matrix3x3.h"
#include "OPC_Matrix4x4.h"
#include "OPC_Plane.h"
#include "OPC_Ray.h"
}   // namespace IceMaths
using namespace IceMaths;
#endif

#ifndef __MESHMERIZER_H__
#define MESHMERIZER_API OPCODE_API
namespace Meshmerizer
{
#include "OPC_Triangle.h"
#include "OPC_AABB.h"
#include "OPC_OBB.h"
#include "OPC_BoundingSphere.h"
}   // namespace Meshmerizer
using namespace Meshmerizer;
#endif

namespace Opcode
{
// Bulk-of-the-work
#include "OPC_Settings.h"
#include "OPC_Common.h"
    //		#include "OPC_TreeBuilders.h"
#include "OPC_AABBTree.h"
#include "OPC_OptimizedTree.h"
#include "OPC_Model.h"
#include "OPC_BVTCache.h"
#include "OPC_Collider.h"
#include "OPC_VolumeCollider.h"
#include "OPC_TreeCollider.h"
#include "OPC_RayCollider.h"
#include "OPC_SphereCollider.h"
#include "OPC_OBBCollider.h"
#include "OPC_AABBCollider.h"
#include "OPC_PlanesCollider.h"
}   // namespace Opcode

#endif   // __OPCODE_H__
