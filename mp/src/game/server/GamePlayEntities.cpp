#include "cbase.h"
#include "hl2mp_gamerules.h"
#include "game.h" //We want access to the game convars
#include "GamePlayEntities.h"
#include "hl2mp_player.h"

//GameRules*	g_pGameRules = NULL;
bool roundsOver = false;

////////////////////////////////////////////////////////////////////////////////
//MAP_RULES
//-----------------------------------------------------------------------------
// Purpose: The entity that is setup for controlling all gameplay related functions such as lives, respawn time, end of round, etc
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
class CMapRulesEntity : public CLogicalEntity
{
public:
	DECLARE_CLASS(CMapRulesEntity, CLogicalEntity);
	//void Think(void);
	DECLARE_DATADESC();

	//Constructor
	CMapRulesEntity()
	{
		//Initialize default values
	}
	//Input Functions
	void InputEndRound(inputdata_t &inputdata);
private:
	//Declare variables

	//Output Functions
	COutputEvent OutPutOnEndRound;
};

//This is what we use to tell the engine how to link hammer entity to internal entity
LINK_ENTITY_TO_CLASS(map_rules, CMapRulesEntity);

//Start of our data description for CMapRulesEntity
BEGIN_DATADESC(CMapRulesEntity)

//For save/load
//List each variable and it's type EX:
//DEFINE_FIELD(variablename, type),

//Link our class variables to hammer keyvalues
//DEFINE_KEYFIELD(variablename, variabletype, "hammerkeyvaluestringname"),

//Link our input name from hammer to our input function
//DEFINE_INPUTFUNC(type, "hammerinputname", inputfunction),
	DEFINE_INPUTFUNC(FIELD_VOID, "EndRound", InputEndRound),

//Link our output name from hammer to our output function
//DEFINE_OUTPUT(outputeventname, "hammeroutputstringname"),
	DEFINE_OUTPUT(OutPutOnEndRound, "OnEndRound"),

END_DATADESC()

void CMapRulesEntity::InputEndRound(inputdata_t &inputdata)
{
	OutPutOnEndRound.FireOutput(inputdata.pActivator, this);
	roundsOver = true;
}


////////////////////////////////////////////////////////////////////////////////
//INFO_PLAYER_DEATHRUN
//-----------------------------------------------------------------------------
// Purpose: The main spawn point for this mod
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
class CPlayerDeathrunEntity : public CPointEntity
{
public:
	DECLARE_CLASS(CPlayerDeathrunEntity, CPointEntity);
	DECLARE_DATADESC();

	//Constructor
	CPlayerDeathrunEntity()
	{
	}
	
private:
	
};

//This is what we use to tell the engine how to link hammer entity to internal entity
LINK_ENTITY_TO_CLASS(info_player_deathrun, CPointEntity);


////////////////////////////////////////////////////////////////////////////////
//game_setspawn
//-----------------------------------------------------------------------------
// Purpose: Entity used to set a players spawnpoints
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
class CSetSpawn : public CLogicalEntity
{
public:
	DECLARE_CLASS(CSetSpawn, CLogicalEntity);
	//void Think(void);
	DECLARE_DATADESC();

	//Constructor
	CSetSpawn()
	{
		//Initialize default values
	}
	//Input Functions
	void SetSpawn(inputdata_t &inputdata);
private:
	//Declare variables
	
	//Output Functions
	COutputEvent OnSetSpawn;
};

//This is what we use to tell the engine how to link hammer entity to internal entity
LINK_ENTITY_TO_CLASS(game_setspawn, CSetSpawn);

//Start of our data description for CMapRulesEntity
BEGIN_DATADESC(CSetSpawn)

//Link our input name from hammer to our input function
//DEFINE_INPUTFUNC(type, "hammerinputname", inputfunction),
DEFINE_INPUTFUNC(FIELD_STRING, "SetSpawn", SetSpawn),

//Link our output name from hammer to our output function
//DEFINE_OUTPUT(outputeventname, "hammeroutputstringname"),
DEFINE_OUTPUT(OnSetSpawn, "OnSetSpawn"),

END_DATADESC()

void CSetSpawn::SetSpawn(inputdata_t &inputdata)
{
	
	//Make sure they put something in there
	if (!inputdata.value.String()[0])
		return;
	//We need to convert the inputdata to a c string valves string isnt what we want
	string_t tempString = inputdata.value.StringID();
	char *spawnPointName = (char*)STRING(tempString);

	DevMsg(spawnPointName);
	CHL2MP_Player *player = dynamic_cast< CHL2MP_Player * >(inputdata.pActivator);
		if (player)
		{
			player->SetSpawnPointName(spawnPointName);
			return;
		}
	return;
	
	
	
		

}