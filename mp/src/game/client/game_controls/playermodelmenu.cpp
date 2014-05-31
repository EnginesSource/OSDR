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
int MAXMODELS = 20;

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
		CURRENTMODEL--;
		updateImage();
	}
}

void CPlayerModelPanel::setModel(void) {
	switch (CURRENTMODEL)
	{
	case 1:
		CURRENTMODEL = RandomInt(2, MAXMODELS);
		setModel();
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