#pragma once
class CommandWizard
{
private:
	CString CmdName;
	int Para_1;
	int Para_2;
public:
	CommandWizard(void);
	CommandWizard::CommandWizard(CString str,int pri1,int pri2);
	~CommandWizard(void);
	CString getCmdName();
	int getPara_1();
	int getPara_2();
	virtual BOOL save();
	virtual BOOL open();
};

