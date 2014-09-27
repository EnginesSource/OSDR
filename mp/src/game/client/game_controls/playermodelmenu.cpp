#include "cbase.h"
#include "c_basehlplayer.h"
#include "tier3/tier3.h"
#include <tier1/strtools.h>
#include <vgui_controls/Frame.h>
#include <vgui_controls/Label.h>
#include <vgui/ISurface.h>
#include <vgui_controls/RichText.h>
#include <vgui_controls/ImagePanel.h>
#include <vgui_controls\Button.h>
#include <vgui/IInput.h>
#include <vgui/ILocalize.h>

#include "playermodel.h"
#include "Iplayermodelpanel.h"

extern IFileSystem *g_pFullFileSystem;

using namespace vgui;

int CURRENTMODEL = 1;
int MAXMODELS = 75;

ConVar cl_showplayermodelpanel("cl_showplayermodelpanel", "0", FCVAR_CLIENTDLL, "Sets the state of player model selection panel <state>");

CPlayerModelPanel::CPlayerModelPanel(vgui::VPANEL parent) : BaseClass(NULL, "PlayerModelPanel") {
	SetParent(parent);

	SetKeyBoardInputEnabled(true);
	SetMouseInputEnabled(true);

	SetProportional(false);
	SetTitleBarVisible(true);
	SetMinimizeButtonVisible(false);
	SetMaximizeButtonVisible(false);
	SetCloseButtonVisible(false);
	SetSizeable(false);
	SetMoveable(false);
	SetVisible(true);

	SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/SourceScheme.res", "SourceScheme"));

	LoadControlSettings("resource/ui/playermodelpanel.res");

	playerImage = FindControl<vgui::ImagePanel>("playerImage", true);
	updateImage();
	nextModel_BTN = FindControl<vgui::Button>("nextModel_BTN", true);
	previousModel_BTN = FindControl<vgui::Button>("previousModel_BTN", true);
	modelSelect_BTN = FindControl<vgui::Button>("modelSelect_BTN", true);
	close_BTN = FindControl<vgui::Button>("close_BTN", true);
}


CPlayerModelPanel::~CPlayerModelPanel() {
}

void CPlayerModelPanel::OnCommand(const char *command) {
	//BaseClass::OnCommand(command);
	if (!Q_stricmp(command, "next_Model"))
		PlayerModelPanel->nextModel();
	if (!Q_stricmp(command, "previous_Model"))
		PlayerModelPanel->previousModel();
	if (!Q_stricmp(command, "model_select"))
		PlayerModelPanel->selectModel();
	if (!Q_stricmp(command, "turnoff"))
		SetVisible(0);
}

void CPlayerModelPanel::updateImage(void) {
	vgui::IImage *img;
	switch (CURRENTMODEL)
	{
	case 1:
		img = scheme()->GetImage("models/random_model.vmt", false);
		playerImage->SetImage(img);
		break;
	case 2:
		img = scheme()->GetImage("models/humans/group03/male_01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 3:
		img = scheme()->GetImage("models/humans/group03/male_02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 4:
		img = scheme()->GetImage("models/humans/group03/male_03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 5:
		img = scheme()->GetImage("models/humans/group03/male_04.vmt", false);
		playerImage->SetImage(img);
		break;
	case 6:
		img = scheme()->GetImage("models/humans/group03/male_05.vmt", false);
		playerImage->SetImage(img);
		break;
	case 7:
		img = scheme()->GetImage("models/humans/group03/male_06.vmt", false);
		playerImage->SetImage(img);
		break;
	case 8:
		img = scheme()->GetImage("models/humans/group03/male_07.vmt", false);
		playerImage->SetImage(img);
		break;
	case 9:
		img = scheme()->GetImage("models/humans/group03/male_08.vmt", false);
		playerImage->SetImage(img);
		break;
	case 10:
		img = scheme()->GetImage("models/humans/group03/male_09.vmt", false);
		playerImage->SetImage(img);
		break;
	case 11:
		img = scheme()->GetImage("models/humans/group03/female_01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 12:
		img = scheme()->GetImage("models/humans/group03/female_02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 13:
		img = scheme()->GetImage("models/humans/group03/female_03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 14:
		img = scheme()->GetImage("models/humans/group03/female_04.vmt", false);
		playerImage->SetImage(img);
		break;
	case 15:
		img = scheme()->GetImage("models/humans/group03/female_06.vmt", false);
		playerImage->SetImage(img);
		break;
	case 16:
		img = scheme()->GetImage("models/humans/group03/female_07.vmt", false);
		playerImage->SetImage(img);
		break;
	case 17:
		img = scheme()->GetImage("models/combine_soldier.vmt", false);
		playerImage->SetImage(img);
		break;
	case 18:
		img = scheme()->GetImage("models/combine_soldier_prisonguard.vmt", false);
		playerImage->SetImage(img);
		break;
	case 19:
		img = scheme()->GetImage("models/combine_super_soldier.vmt", false);
		playerImage->SetImage(img);
		break;
	case 20:
		img = scheme()->GetImage("models/police.vmt", false);
		playerImage->SetImage(img);
		break;
	case 21:
		img = scheme()->GetImage("models/hl2arcade/combine_engineer_female_01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 22:
		img = scheme()->GetImage("models/hl2arcade/combine_engineer_female_02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 23:
		img = scheme()->GetImage("models/hl2arcade/combine_engineer_female_03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 24:
		img = scheme()->GetImage("models/hl2arcade/combine_engineer_male_01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 25:
		img = scheme()->GetImage("models/hl2arcade/combine_engineer_male_02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 26:
		img = scheme()->GetImage("models/hl2arcade/combine_engineer_male_03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 27:
		img = scheme()->GetImage("models/hl2arcade/combine_medic_female_01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 28:
		img = scheme()->GetImage("models/hl2arcade/combine_medic_female_02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 29:
		img = scheme()->GetImage("models/hl2arcade/combine_medic_female_03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 30:
		img = scheme()->GetImage("models/hl2arcade/combine_medic_male_01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 31:
		img = scheme()->GetImage("models/hl2arcade/combine_medic_male_02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 32:
		
		break;
	case 33:

		break;
	case 34:
		img = scheme()->GetImage("models/hl2arcade/combine_normal_female_02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 35:
		img = scheme()->GetImage("models/hl2arcade/combine_normal_female_03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 36:

		break;
	case 37:
		img = scheme()->GetImage("models/hl2arcade/combine_normal_male_02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 38:
		img = scheme()->GetImage("models/hl2arcade/combine_normal_male_03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 39:
		img = scheme()->GetImage("models/hl2arcade/combine_sniper_male_01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 40:
		img = scheme()->GetImage("models/hl2arcade/combine_sniper_male_02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 41:

		break;
	case 42:

		break;
	case 43:

		break;
	case 44:

		break;
	case 45:
		img = scheme()->GetImage("models/hl2arcade/gordon.vmt", false);
		playerImage->SetImage(img);
		break;
	case 46:
		img = scheme()->GetImage("models/hl2arcade/resis_engineer_female01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 47:
		img = scheme()->GetImage("models/hl2arcade/resis_engineer_female02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 48:
		img = scheme()->GetImage("models/hl2arcade/resis_engineer_female03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 49:
		img = scheme()->GetImage("models/hl2arcade/resis_engineer_male01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 50:
		img = scheme()->GetImage("models/hl2arcade/resis_engineer_male02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 51:

		break;
	case 52:
		img = scheme()->GetImage("models/hl2arcade/resis_medic_female01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 53:
		img = scheme()->GetImage("models/hl2arcade/resis_medic_female02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 54:
		img = scheme()->GetImage("models/hl2arcade/resis_medic_female03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 55:
		img = scheme()->GetImage("models/hl2arcade/resis_medic_male01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 56:
		img = scheme()->GetImage("models/hl2arcade/resis_medic_male02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 57:
		img = scheme()->GetImage("models/hl2arcade/resis_medic_male03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 58:
		img = scheme()->GetImage("models/hl2arcade/resis_normal_female01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 59:
		img = scheme()->GetImage("models/hl2arcade/resis_normal_female02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 60:
		img = scheme()->GetImage("models/hl2arcade/resis_normal_female03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 61:
		img = scheme()->GetImage("models/hl2arcade/resis_normal_male01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 62:
		img = scheme()->GetImage("models/hl2arcade/resis_normal_male02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 63:
		img = scheme()->GetImage("models/hl2arcade/resis_normal_male03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 64:
		img = scheme()->GetImage("models/hl2arcade/resis_sniper_female01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 65:
		img = scheme()->GetImage("models/hl2arcade/resis_sniper_female02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 66:
		img = scheme()->GetImage("models/hl2arcade/resis_sniper_female03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 67:
		img = scheme()->GetImage("models/hl2arcade/resis_sniper_male01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 68:
		img = scheme()->GetImage("models/hl2arcade/resis_sniper_male02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 69:
		img = scheme()->GetImage("models/hl2arcade/resis_sniper_male03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 70:
		img = scheme()->GetImage("models/hl2arcade/resis_soldier_female01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 71:
		img = scheme()->GetImage("models/hl2arcade/resis_soldier_female02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 72:
		img = scheme()->GetImage("models/hl2arcade/resis_soldier_female03.vmt", false);
		playerImage->SetImage(img);
		break;
	case 73:
		img = scheme()->GetImage("models/hl2arcade/resis_soldier_male01.vmt", false);
		playerImage->SetImage(img);
		break;
	case 74:
		img = scheme()->GetImage("models/hl2arcade/resis_soldier_male02.vmt", false);
		playerImage->SetImage(img);
		break;
	case 75:
		img = scheme()->GetImage("models/hl2arcade/resis_soldier_male03.vmt", false);
		playerImage->SetImage(img);
		break;
	default:
		break;
	}
}

void CPlayerModelPanel::nextImage(void) {
	if (CURRENTMODEL == MAXMODELS)
	{
		CURRENTMODEL = 1;
		updateImage();
	}
	else
	{
		CURRENTMODEL++;
		//sadly we had some broken models
		if (CURRENTMODEL == 32 || CURRENTMODEL == 33 || CURRENTMODEL == 36 || CURRENTMODEL == 51 || CURRENTMODEL == 41 || CURRENTMODEL == 42 || CURRENTMODEL == 43 || CURRENTMODEL == 44)
		{
			CURRENTMODEL++;
			PlayerModelPanel->nextModel();
			return;
		}
		updateImage();
	}
}

void CPlayerModelPanel::previousImage(void) {
	if (CURRENTMODEL == 1)
	{
		CURRENTMODEL = MAXMODELS;
		updateImage();
	}
	else
	{
		if (CURRENTMODEL == 32 || CURRENTMODEL == 33 || CURRENTMODEL == 36 || CURRENTMODEL == 51 || CURRENTMODEL == 41 || CURRENTMODEL == 42 || CURRENTMODEL == 43 || CURRENTMODEL == 44)
		{
			CURRENTMODEL--;
			PlayerModelPanel->previousModel();
			return;
		}
		CURRENTMODEL--;
		updateImage();
	}
}

void CPlayerModelPanel::setModel(void) {
	switch (CURRENTMODEL)
	{
	case 1:
		DoOver:
		CURRENTMODEL = RandomInt(2, MAXMODELS);
		if (CURRENTMODEL == 32 || CURRENTMODEL == 33 || CURRENTMODEL == 36 || CURRENTMODEL == 51 || CURRENTMODEL == 41 || CURRENTMODEL == 42 || CURRENTMODEL == 43 || CURRENTMODEL == 44)
		{
			goto DoOver;
			break;
		}
		setModel();
		updateImage();
		break;
	case 2:
		engine->ClientCmd("cl_playermodel models/humans/group03/male_01.mdl");
		break;
	case 3:
		engine->ClientCmd("cl_playermodel models/humans/group03/male_02.mdl");
		break;
	case 4:
		engine->ClientCmd("cl_playermodel models/humans/group03/male_03.mdl");
		break;
	case 5:
		engine->ClientCmd("cl_playermodel models/humans/group03/male_04.mdl");
		break;
	case 6:
		engine->ClientCmd("cl_playermodel models/humans/group03/male_05.mdl");
		break;
	case 7:
		engine->ClientCmd("cl_playermodel models/humans/group03/male_06.mdl"); 
		break;
	case 8:
		engine->ClientCmd("cl_playermodel models/humans/group03/male_07.mdl");
		break;
	case 9:
		engine->ClientCmd("cl_playermodel models/humans/group03/male_08.mdl");
		break;
	case 10:
		engine->ClientCmd("cl_playermodel models/humans/group03/male_09.mdl");
		break;
	case 11:
		engine->ClientCmd("cl_playermodel models/humans/group03/female_01.mdl");
		break;
	case 12:
		engine->ClientCmd("cl_playermodel models/humans/group03/female_02.mdl");
		break;
	case 13:
		engine->ClientCmd("cl_playermodel models/humans/group03/female_03.mdl");
		break;
	case 14:
		engine->ClientCmd("cl_playermodel models/humans/group03/female_04.mdl");
		break;
	case 15:
		engine->ClientCmd("cl_playermodel models/humans/group03/female_06.mdl");
		break;
	case 16:
		engine->ClientCmd("cl_playermodel models/humans/group03/female_07.mdl");
		break;
	case 17:
		engine->ClientCmd("cl_playermodel models/combine_soldier.mdl");
		break;
	case 18:
		engine->ClientCmd("cl_playermodel models/combine_soldier_prisonguard.mdl");
		break;
	case 19:
		engine->ClientCmd("cl_playermodel models/combine_super_soldier.mdl");
		break;
	case 20:
		engine->ClientCmd("cl_playermodel models/police.mdl");
		break;
	case 21:
		engine->ClientCmd("cl_playermodel models/c_eng_f/combine_engineer_female.mdl");
		break;
	case 22:
		engine->ClientCmd("cl_playermodel models/c_eng_fxss1/c_eng_fxss1.mdl");
		break;
	case 23:
		engine->ClientCmd("cl_playermodel models/c_eng_fxss2/c_eng_fxss2.mdl");
		break;
	case 24:
		engine->ClientCmd("cl_playermodel models/c_eng_m/combine_engineer_male.mdl");
		break;
	case 25:
		engine->ClientCmd("cl_playermodel models/c_eng_mxss1/c_eng_mxss1.mdl");
		break;
	case 26:
		engine->ClientCmd("cl_playermodel models/c_eng_mxss2/c_eng_mxss2.mdl");
		break;
	case 27:
		engine->ClientCmd("cl_playermodel models/c_med_f/combine_medic_female.mdl");
		break;
	case 28:
		engine->ClientCmd("cl_playermodel models/c_med_fxss1/c_med_fxss1.mdl");
		break;
	case 29:
		engine->ClientCmd("cl_playermodel models/c_med_fxss2/c_med_fxss2.mdl");
		break;
	case 30:
		engine->ClientCmd("cl_playermodel models/c_med_m/combine_medic_male.mdl");
		break;
	case 31:
		engine->ClientCmd("cl_playermodel models/c_med_mxss1/c_med_mxss1.mdl");
		break;
	case 32:
		
		break;
	case 33:
		
		break;
	case 34:
		engine->ClientCmd("cl_playermodel models/c_nor_fxss1/c_nor_fxss1.mdl");
		break;
	case 35:
		engine->ClientCmd("cl_playermodel models/c_nor_fxss2/c_nor_fxss2.mdl");
		break;
	case 36:
		
		break;
	case 37:
		engine->ClientCmd("cl_playermodel models/c_nor_mxss1/c_nor_mxss1.mdl");
		break;
	case 38:
		engine->ClientCmd("cl_playermodel models/c_nor_mxss2/c_nor_mxss2.mdl");
		break;
	case 39:
		engine->ClientCmd("cl_playermodel models/c_sni_m/combine_sniper_male.mdl");
		break;
	case 40:
		engine->ClientCmd("cl_playermodel models/c_sni_mxss1/c_sni_mxss1.mdl");
		break;
	case 41:
		
		break;
	case 42:
		
		break;
	case 43:
		
		break;
	case 44:
		
		break;
	case 45:
		engine->ClientCmd("cl_playermodel models/gordon/gordon.mdl");
		break;
	case 46:
		engine->ClientCmd("cl_playermodel models/r_eng_f/resis_engineer_female.mdl");
		break;
	case 47:
		engine->ClientCmd("cl_playermodel models/r_eng_fxss1/r_eng_fxss1.mdl");
		break;
	case 48:
		engine->ClientCmd("cl_playermodel models/r_eng_fxss2/r_eng_fxss2.mdl");
		break;
	case 49:
		engine->ClientCmd("cl_playermodel models/r_eng_m/resis_engineer_male.mdl");
		break;
	case 50:
		engine->ClientCmd("cl_playermodel models/r_eng_mxss1/r_eng_mxss1.mdl");
		break;
	case 51:
		
		break;
	case 52:
		engine->ClientCmd("cl_playermodel models/r_med_f/resis_medic_female.mdl");
		break;
	case 53:
		engine->ClientCmd("cl_playermodel models/r_med_fxss1/r_med_fxss1.mdl");
		break;
	case 54:
		engine->ClientCmd("cl_playermodel models/r_med_fxss2/r_med_fxss2.mdl");
		break;
	case 55:
		engine->ClientCmd("cl_playermodel models/r_med_m/resis_medic_male.mdl");
		break;
	case 56:
		engine->ClientCmd("cl_playermodel models/r_med_mxss1/r_med_mxss1.mdl");
		break;
	case 57:
		engine->ClientCmd("cl_playermodel models/r_med_mxss2/r_med_mxss2.mdl");
		break;
	case 58:
		engine->ClientCmd("cl_playermodel models/r_nor_f/resis_normal_female.mdl");
		break;
	case 59:
		engine->ClientCmd("cl_playermodel models/r_nor_fxss1/r_nor_fxss1.mdl");
		break;
	case 60:
		engine->ClientCmd("cl_playermodel models/r_nor_fxss2/r_nor_fxss2.mdl");
		break;
	case 61:
		engine->ClientCmd("cl_playermodel models/r_nor_m/resis_normal_male.mdl");
		break;
	case 62:
		engine->ClientCmd("cl_playermodel models/r_nor_mxss1/r_nor_mxss1.mdl");
		break;
	case 63:
		engine->ClientCmd("cl_playermodel models/r_nor_mxss2/r_nor_mxss2.mdl");
		break;
	case 64:
		engine->ClientCmd("cl_playermodel models/r_sni_f/resis_sniper_female.mdl");
		break;
	case 65:
		engine->ClientCmd("cl_playermodel models/r_sni_fxss1/r_sni_fxss1.mdl");
		break;
	case 66:
		engine->ClientCmd("cl_playermodel models/r_sni_fxss2/r_sni_fxss2.mdl");
		break;
	case 67:
		engine->ClientCmd("cl_playermodel models/r_sni_m/resis_sniper_male.mdl");
		break;
	case 68:
		engine->ClientCmd("cl_playermodel models/r_sni_mxss1/r_sni_mxss1.mdl");
		break;
	case 69:
		engine->ClientCmd("cl_playermodel models/r_sni_mxss2/r_sni_mxss2.mdl");
		break;
	case 70:
		engine->ClientCmd("cl_playermodel models/r_sol_f/resis_soldier_female.mdl");
		break;
	case 71:
		engine->ClientCmd("cl_playermodel models/r_sol_fxss1/r_sol_fxss1.mdl");
		break;
	case 72:
		engine->ClientCmd("cl_playermodel models/r_sol_fxss2/r_sol_fxss2.mdl");
		break;
	case 73:
		engine->ClientCmd("cl_playermodel models/r_sol_m/resis_soldier_male.mdl");
		break;
	case 74:
		engine->ClientCmd("cl_playermodel models/r_sol_mxss1/r_sol_mxss1.mdl");
		break;
	case 75:
		engine->ClientCmd("cl_playermodel models/r_sol_mxss2/r_sol_mxss2.mdl");
		break;
	default:
		break;
	}
}


class CPlayerModelPanelFactory : public IPlayerModelPanel {
private:
	CPlayerModelPanel *PlayerModelPanel;

public:
	CPlayerModelPanelFactory(void) {
		PlayerModelPanel = NULL;
	}

	void Create(vgui::VPANEL parent) {
		PlayerModelPanel = new CPlayerModelPanel(parent);
	}

	void Destroy(void) {
		if (PlayerModelPanel) {
			PlayerModelPanel->SetParent((vgui::Panel *)NULL);
			delete PlayerModelPanel;
		}
	}
	void Activate(void)
	{
		if (PlayerModelPanel)
		{
			PlayerModelPanel->Activate();
		}
	}
	void nextModel(void) {
		PlayerModelPanel->nextImage();
	}

	void previousModel(void) {
		PlayerModelPanel->previousImage();
	}
	void selectModel(void) {
		PlayerModelPanel->setModel();
	}
};

static CPlayerModelPanelFactory g_PlayerModelPanel;
IPlayerModelPanel *PlayerModelPanel = (IPlayerModelPanel *)&g_PlayerModelPanel;

CON_COMMAND(TogglePlayerModelPanel, "Toggles playermodelpanel on or off")
{
	cl_showplayermodelpanel.SetValue(!cl_showplayermodelpanel.GetBool());
	PlayerModelPanel->Activate();
};

CON_COMMAND(next_Model, "progress to the next model") {
	g_PlayerModelPanel.nextModel();
}

CON_COMMAND(previous_Model, "regress to the previous model") {
	PlayerModelPanel->previousModel();
}

CON_COMMAND(model_select, "choose currently selected model") {
	PlayerModelPanel->selectModel();
}