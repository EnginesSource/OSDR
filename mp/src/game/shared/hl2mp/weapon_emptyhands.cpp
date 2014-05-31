//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Empty hands
//
//=============================================================================//

#include "cbase.h"
#include "npcevent.h"
#include "in_buttons.h"

#ifdef CLIENT_DLL
#include "c_hl2mp_player.h"
#else
#include "player_pickup.h"
#include "hl2mp_player.h"
#endif



#include "weapon_hl2mpbasehlmpcombatweapon.h"

#define	PISTOL_FASTEST_REFIRE_TIME		0.1f
#define	PISTOL_FASTEST_DRY_REFIRE_TIME	0.2f

#define	PISTOL_ACCURACY_SHOT_PENALTY_TIME		0.2f	// Applied amount of time each shot adds to the time we must recover from
#define	PISTOL_ACCURACY_MAXIMUM_PENALTY_TIME	1.5f	// Maximum penalty to deal out

#ifdef CLIENT_DLL
#define CWeaponEmptyHands C_WeaponEmptyHands
#endif

//-----------------------------------------------------------------------------
// CWeaponEmptyHands
//-----------------------------------------------------------------------------

class CWeaponEmptyHands : public CBaseHL2MPCombatWeapon
{
public:
	DECLARE_CLASS(CWeaponEmptyHands, CBaseHL2MPCombatWeapon);

	CWeaponEmptyHands(void);

	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	void	Precache(void);
	void	ItemPostFrame(void);
	void	ItemPreFrame(void);
	void	ItemBusyFrame(void);
	void	PrimaryAttack(CBaseEntity *pObject, bool bLimitMassAndSize);
	void	AddViewKick(void);
	void	DryFire(void);
	
	void	UpdatePenaltyTime(void);


	Activity	GetPrimaryAttackActivity(void);

	virtual bool Reload(void);

	//virtual const Vector& GetBulletSpread(void)
	//{
	//	static Vector cone;

	//	float ramp = RemapValClamped(m_flAccuracyPenalty,
	//		0.0f,
	//		PISTOL_ACCURACY_MAXIMUM_PENALTY_TIME,
	//		0.0f,
	//		1.0f);

	//	// We lerp from very accurate to inaccurate over time
	//	VectorLerp(VECTOR_CONE_1DEGREES, VECTOR_CONE_6DEGREES, ramp, cone);

	//	return cone;
	//}

	//virtual int	GetMinBurst()
	//{
	//	return 1;
	//}

	//virtual int	GetMaxBurst()
	//{
	//	return 3;
	//}

	//virtual float GetFireRate(void)
	//{
	//	return 0.5f;
	//}

#ifndef CLIENT_DLL
	DECLARE_ACTTABLE();
#endif

private:
	CNetworkVar(float, m_flSoonestPrimaryAttack);
	CNetworkVar(float, m_flLastAttackTime);
	CNetworkVar(float, m_flAccuracyPenalty);
	CNetworkVar(int, m_nNumShotsFired);

private:
	CWeaponEmptyHands(const CWeaponEmptyHands &);
};

IMPLEMENT_NETWORKCLASS_ALIASED(WeaponEmptyHands, DT_WeaponEmptyHands)

BEGIN_NETWORK_TABLE(CWeaponEmptyHands, DT_WeaponEmptyHands)
END_NETWORK_TABLE()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA(CWeaponEmptyHands)
END_PREDICTION_DATA()
#endif

LINK_ENTITY_TO_CLASS(weapon_emptyhands, CWeaponEmptyHands);
PRECACHE_WEAPON_REGISTER(weapon_emptyhands);

#ifndef CLIENT_DLL
acttable_t CWeaponEmptyHands::m_acttable[] =
{
	{ ACT_HL2MP_IDLE, ACT_HL2MP_IDLE_GRENADE, false },
	{ ACT_HL2MP_RUN, ACT_HL2MP_RUN_GRENADE, false },
	{ ACT_HL2MP_IDLE_CROUCH, ACT_HL2MP_IDLE_CROUCH_GRENADE, false },
	{ ACT_HL2MP_WALK_CROUCH, ACT_HL2MP_WALK_CROUCH_GRENADE, false },
	{ ACT_HL2MP_GESTURE_RANGE_ATTACK, ACT_HL2MP_GESTURE_RANGE_ATTACK_GRENADE, false },
	{ ACT_HL2MP_GESTURE_RELOAD, ACT_HL2MP_GESTURE_RELOAD_GRENADE, false },
	{ ACT_HL2MP_JUMP, ACT_HL2MP_JUMP_GRENADE, false },
	{ ACT_RANGE_ATTACK1, ACT_RANGE_ATTACK_PISTOL, false },
};


IMPLEMENT_ACTTABLE(CWeaponEmptyHands);

#endif

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeaponEmptyHands::CWeaponEmptyHands(void)
{
	m_bFiresUnderwater = true;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponEmptyHands::Precache(void)
{
	BaseClass::Precache();
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CWeaponEmptyHands::DryFire(void)
{

}
//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CWeaponEmptyHands::PrimaryAttack(CBaseEntity *pObject, bool bLimitMassAndSize)
{
	//TODO:
	//Make this fire the use key -Wazanator 4/5/2014
	//

}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponEmptyHands::UpdatePenaltyTime(void)
{
	CBasePlayer *pOwner = ToBasePlayer(GetOwner());

	if (pOwner == NULL)
		return;

	 //Check our penalty time decay
	if (((pOwner->m_nButtons & IN_ATTACK) == false) && (m_flSoonestPrimaryAttack < gpGlobals->curtime))
	{
		m_flAccuracyPenalty -= gpGlobals->frametime;
		m_flAccuracyPenalty = clamp(m_flAccuracyPenalty, 0.0f, PISTOL_ACCURACY_MAXIMUM_PENALTY_TIME);
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponEmptyHands::ItemPreFrame(void)
{
	UpdatePenaltyTime();

	BaseClass::ItemPreFrame();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponEmptyHands::ItemBusyFrame(void)
{
	UpdatePenaltyTime();

	BaseClass::ItemBusyFrame();
}

//-----------------------------------------------------------------------------
// Purpose: Allows firing as fast as button is pressed
//-----------------------------------------------------------------------------
void CWeaponEmptyHands::ItemPostFrame(void)
{
	BaseClass::ItemPostFrame();

	if (m_bInReload)
		return;

	CBasePlayer *pOwner = ToBasePlayer(GetOwner());

	if (pOwner == NULL)
		return;

	if (pOwner->m_nButtons & IN_ATTACK2)
	{
		m_flLastAttackTime = gpGlobals->curtime + PISTOL_FASTEST_REFIRE_TIME;
		m_flSoonestPrimaryAttack = gpGlobals->curtime + PISTOL_FASTEST_REFIRE_TIME;
		m_flNextPrimaryAttack = gpGlobals->curtime + PISTOL_FASTEST_REFIRE_TIME;
	}

	////Allow a refire as fast as the player can click
	if (((pOwner->m_nButtons & IN_ATTACK) == false) && (m_flSoonestPrimaryAttack < gpGlobals->curtime))
	{
		m_flNextPrimaryAttack = gpGlobals->curtime - 0.1f;
	}
	else if ((pOwner->m_nButtons & IN_ATTACK) && (m_flNextPrimaryAttack < gpGlobals->curtime) && (m_iClip1 <= 0))
	{
		DryFire();
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
// Output : int
//-----------------------------------------------------------------------------
Activity CWeaponEmptyHands::GetPrimaryAttackActivity(void)
{
	/*if (m_nNumShotsFired < 1)
		return ACT_VM_PRIMARYATTACK;

	if (m_nNumShotsFired < 2)
		return ACT_VM_RECOIL1;

	if (m_nNumShotsFired < 3)
		return ACT_VM_RECOIL2;
		*/
	return ACT_VM_RECOIL3;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CWeaponEmptyHands::Reload(void)
{
	bool fRet = DefaultReload(GetMaxClip1(), GetMaxClip2(), ACT_VM_RELOAD);
	if (fRet)
	{
		WeaponSound(RELOAD);
		m_flAccuracyPenalty = 0.0f;
	}
	
	return fRet;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponEmptyHands::AddViewKick(void)
{
	//CBasePlayer *pPlayer = ToBasePlayer(GetOwner());

	//if (pPlayer == NULL)
	//	return;

	//QAngle	viewPunch;

	//viewPunch.x = SharedRandomFloat("pistolpax", 0.25f, 0.5f);
	//viewPunch.y = SharedRandomFloat("pistolpay", -.6f, .6f);
	//viewPunch.z = 0.0f;

	////Add it to the view punch
	//pPlayer->ViewPunch(viewPunch);
}
