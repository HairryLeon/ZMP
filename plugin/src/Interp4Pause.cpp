#include <iostream>
#include "Interp4Pause.hh"

using std::cout;
using std::endl;

extern "C" {
	AbstractInterp4Command* CreateCmd(void);
	const char* GetCmdName() {return "Pause"; }
}

AbstractInterp4Command* CreateCmd(void)
{
	return Interp4Pause::CreateCmd();
}

Interp4Pause::Interp4Pause(): _Time_ms(0)
{}

void Interp4Pause::PrintCmd() const
{
	cout << GetCmdName() << " " << _Time_ms << " 10 2" << endl;
}

const char* Interp4Pause::GetCmdName() const
{
	return ::GetCmdName();
}

bool Interp4Pause::ExecCmd( AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann)
{
	return true;
}

bool Interp4Pause::ReadParams(std::istream &in)
{
	return true;
}

AbstractInterp4Command *Interp4Pause::CreateCmd()
{
	return new Interp4Pause();
}

void Interp4Pause::PrintSyntax() const
{
	cout << "  Pause  NazwaObiektu  Czas[ms]" << endl;
}
