//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Special handling for hl2 usable ladders
//
//=============================================================================//
#include "cbase.h"

//-----------------------------------------------------------------------------
// Purpose: Fixing func_ladder
//Original code from SecobMod
//Ported over by Wazanator
//Date 4/3/14
//-----------------------------------------------------------------------------
#include "gamemovement.h"
// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Expose our interface.
static CGameMovement g_GameMovement;
IGameMovement *g_pGameMovement = (IGameMovement *)&g_GameMovement;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CGameMovement, IGameMovement, INTERFACENAME_GAMEMOVEMENT, g_GameMovement);