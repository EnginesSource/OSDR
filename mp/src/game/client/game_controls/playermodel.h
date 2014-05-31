#ifndef _PLAYERMODEL_PANEL_H_
#define _PLAYERMODEL_PANEL_H_

#include "cbase.h"

#include <vgui/IVGui.h>
#include <vgui_controls/Frame.h>
#include <vgui_controls/RichText.h>
#include <vgui_controls/ImagePanel.h>

class CPlayerModelPanel : public vgui::Frame {
	DECLARE_CLASS_SIMPLE(CPlayerModelPanel, vgui::Frame);

	CPlayerModelPanel(vgui::VPANEL parent);
	~CPlayerModelPanel();

	void updateImage(void);
	void nextImage(void);
	void previousImage(void);
	void setModel(void);
	

protected:
	virtual void OnCommand(const char *command);
	//virtual void OnTick();

	vgui::ImagePanel *playerImage;
	vgui::Button *nextModel_BTN;
	vgui::Button *previousModel_BTN;
	vgui::Button *modelSelect_BTN;
	vgui::Button *close_BTN;

};

#endif