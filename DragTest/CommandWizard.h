#pragma once
class CommandWizard
{
private:
	CString CmdName;
	int Para_1;
	int Para_2;
	BOOL isLoop;
	int loopCount;
public:
	CommandWizard(void);
	CommandWizard::CommandWizard(CString str,int pri1,int pri2);
	~CommandWizard(void);
	CString getCmdName();
	int getPara_1();
	int getPara_2();
	BOOL getLoop();
	int getCount();
	virtual BOOL save();
	virtual BOOL open();
};

