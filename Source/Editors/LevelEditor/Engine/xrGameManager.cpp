﻿#include "stdafx.h"
#include "xrGameManager.h"
#include "../../xrAPI/xrGameManager.h"
#include "../../xrServerEntities/xrServer_Objects_Abstract.h"
#include "../xrEngine/xrGameEditorInterface.h"
xrGameManagerLE* g_xrGameManager = nullptr;
extern "C"
{
    typedef void xrGameInitialize();
};
xrGameManagerLE::xrGameManagerLE()
{
    LPCSTR g_name = "xrGame.dll";
    switch (xrGameManager::GetGame())
    {
        case EGame::CS:
            g_name = "xrGameCS.dll";
            break;
        case EGame::SHOC:
            g_name = "xrGameSOC.dll";
            break;
    }

    Log("Loading DLL:", g_name);
    m_hGame = LoadLibrary(g_name);
    if (0 == m_hGame)
        R_CHK(GetLastError());
    R_ASSERT2(m_hGame, "Game DLL raised exception during loading or there is no game DLL at all");
    m_pCreate = (Factory_Create*)GetProcAddress(m_hGame, "xrFactory_Create");
    R_ASSERT(m_pCreate);
    m_pCreateFromSection = (ISE_Abstract * (__cdecl*)(LPCSTR)) GetProcAddress(m_hGame, "xrFactory_Create_From_Section");
    R_ASSERT(m_pCreate);
    m_pDestroy = (Factory_Destroy*)GetProcAddress(m_hGame, "xrFactory_Destroy");
    R_ASSERT(m_pCreate);
    Engine.External.pCreate             = m_pCreate;
    Engine.External.pDestroy            = m_pDestroy;

    xrGameInitialize* pxrGameInitialize = (xrGameInitialize*)GetProcAddress(m_hGame, "xrGameInitialize");
    R_ASSERT(pxrGameInitialize);
    pxrGameInitialize();
}

xrGameManagerLE::~xrGameManagerLE()
{
    FreeLibrary(m_hGame);
}

DLL_Pure* xrGameManagerLE::Create(CLASS_ID clsid)
{
    return m_pCreate(clsid);
}

ISE_Abstract* xrGameManagerLE::CreateFromSection(LPCSTR Name)
{
    return m_pCreateFromSection(Name);
}

void xrGameManagerLE::Destroy(ISE_Abstract* p)
{
    // m_pDestroy(static_cast<DLL_Pure*>(p));
}
