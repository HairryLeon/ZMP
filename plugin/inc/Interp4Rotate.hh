#ifndef INTERP4ROTATE_HH
#define INTERP4ROTATE_HH

#include "AbstractInterp4Command.hh"

class Interp4Rotate : public AbstractInterp4Command
{
	std::string _ObjName;
	double _AngSpeed;
	double _Angle;
	char _Axis;

public:
	Interp4Rotate();
	virtual ~Interp4Rotate() {}

	virtual const char* GetCmdName() const { return "Rotate"; }
	virtual void PrintSyntax() const;
	virtual void PrintParams() const;
	virtual void PrintCmd() const;
	virtual bool ReadParams(std::istream &);
	virtual bool ExecCmd(AbstractScene&, const char*, AbstractComChannel&);
};

extern "C" {
	AbstractInterp4Command* CreateCmd();
}

#endif
