#include "cbase.h"
#include "gamerules.h"

CGameRules*	g_pGameRules = NULL;

class CMapRulesEntity : public CLogicalEntity
{
public:
	DECLARE_CLASS(CMapRulesEntity, CLogicalEntity);
	void Think(void);
	DECLARE_DATADESC();

	//Constructor
	CMapRulesEntity()
	{
		//Initialize default values

	}
	//Input Functions

private:
	//Declare variables

	//Output Functions
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

//Link our output name from hammer to our output function
//DEFINE_OUTPUT(outputeventname, "hammeroutputstringname"),

END_DATADESC()

