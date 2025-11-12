#ifndef INTERP4SET_HH
#define INTERP4SET_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

class Interp4Set: public AbstractInterp4Command {

	std::string _ObjName;
	double _x, _y, _z;
	double _ox, _oy, _oz;
public:
	Interp4Set();

	virtual const char* GetCmdName() const override;
	virtual void PrintSyntax() const override;
	virtual void PrintCmd() const override;
	virtual void PrintParams() const override;
	virtual bool ReadParams(std::istream &in) override;
	virtual bool ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann) override;
	static AbstractInterp4Command * CreateCmd();
};

#endif
