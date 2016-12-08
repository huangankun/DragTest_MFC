#include "StdAfx.h"
#include "CommandWizard.h"

CommandWizard::CommandWizard()
{

}

CommandWizard::CommandWizard(CString str,int pri1,int pri2)
{
	this->CmdName = str;
	this->Para_1 = pri1;
	this->Para_2 = pri2;
	isLoop = FALSE;
	loopCount = 0;
}


CommandWizard::~CommandWizard(void)
{
}

BOOL CommandWizard::open()
{
	return FALSE;
}

BOOL CommandWizard::save()
{
	return TRUE;
}

CString CommandWizard::getCmdName()
{
	return this->CmdName;
}

int CommandWizard::getPara_1()
{
	return this->Para_1;
}

int CommandWizard::getPara_2()
{
	return this->Para_2;
}

BOOL CommandWizard::getLoop()
{
	return this->getLoop();
}

int CommandWizard::getCount()
{
	return this->loopCount;
}
