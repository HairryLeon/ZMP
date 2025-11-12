#include <iostream>
#include "Interp4Set.hh"

using std::cout;
using std::endl;

extern "C" {
	AbstractInterp4Command *CreateCmd(void);
	const char* GetCmdName() {return "Set"; }
}

AbstractInterp4Command *CreateCmd(void)
{
	return Interp4Set::CreateCmd();
}

Interp4Set::Interp4Set(): _x(0), _y(0), _z(0), _ox(0), _oy(0), _oz(0)
{}

void Interp4Set::PrintCmd() const
{
	cout << GetCmdName() << " " << _x << " " << _y << " " << _z << " " << _ox << " " << _oy << " " << _oz << endl;
}

const char *Interp4Set::GetCmdName() const
{
	return ::GetCmdName();
}

bool Interp4Set::ExecCmd( AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann)
{
	return true;
}

bool Interp4Set::ReadParams(std::istream &in)
{
	return true;
}

AbstractInterp4Command *Interp4Set::CreateCmd()
{
	return new Interp4Set();
}

void Interp4Set::PrintSyntax() const
{
	cout << "  Set  NazwaObiektu  X  Y  Z  OX[st]  OY[st]  OZ[st]" << endl;
}

