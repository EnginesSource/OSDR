class IPlayerModelPanel
{
public:
	virtual void            Create(vgui::VPANEL parent) = 0;
	virtual void            Destroy(void) = 0;
	virtual void            Activate(void) = 0;
	virtual void			nextModel(void) = 0;
	virtual void			previousModel(void) = 0;
	virtual void            selectModel(void) = 0;
};


extern IPlayerModelPanel* PlayerModelPanel;