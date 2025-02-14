﻿
#pragma once

// #include "../xrEngine/stdafx.h"

#include "../xrEngine/stdafx.h"

#include "../xrServerEntities/smart_cast.h"
// #include "../xrEngine/pure.h"
// #include "../xrEngine/engineapi.h"
// #include "../xrEngine/eventapi.h"

#include "../xrcdb/xrcdb.h"
#include "../xrsound/sound.h"
// #include "../xrengine/IGame_Level.h"

#include "xrPhysics.h"

#include "../xrapi/xrapi.h"
#ifdef DEBUG
#include "d3d9types.h"
#endif
// IC IGame_Level &GLevel()
//{
//	VERIFY( g_pGameLevel );
//	return *g_pGameLevel;
// }
class xrGameMaterialLibraryInterface;
IC xrGameMaterialLibraryInterface& GMLibrary()
{
    VERIFY(GameMaterialLibrary);
    return *GameMaterialLibrary;
}
