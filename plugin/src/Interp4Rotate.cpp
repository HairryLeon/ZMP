#include <iostream>
#include "Interp4Rotate.hh"

using namespace std;

Interp4Rotate::Interp4Rotate()
{
	_ObjName = "";
	_AngSpeed = 0;
	_Angle = 0;
	_Axis = 'Z';
}

void Interp4Rotate::PrintCmd() const {
	cout << GetCmdName() << " " << _ObjName << " " << _Axis << " " << _AngSpeed << " " << _Angle << endl;
}

void Interp4Rotate::PrintParams() const {
	cout << "Params: " << _ObjName << " " << _Axis << " " << _AngSpeed << " " << _Angle << endl;
}

void Interp4Rotate::PrintSyntax() const {
	cout << "       Rotate NazwaObiektu Axis(X/Y/Z) Szybkosc[st/s] Kat[st]" << endl;
}

bool Interp4Rotate::ReadParams(istream &in){
	in >> _ObjName >> _Axis >> _AngSpeed >> _Angle;
	return !in.fail();
}

bool Interp4Rotate::ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChannel) {
	cout << "Nic tu jeszcze nie ma..." << endl;
	PrintCmd();
	return true;
}

extern "C" {
AbstractInterp4Command* CreateCmd()
{
	return new Interp4Rotate;
}
}
