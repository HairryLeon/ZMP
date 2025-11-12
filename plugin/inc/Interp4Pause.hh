#ifndef INTERP4PAUSE_HH
#define INTERP4PAUSE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

class Interp4Pause : public AbstractInterp4Command
{
	double _Time_ms;

public:
	Interp4Pause();

	virtual const char* GetCmdName() const override;
	virtual void PrintSyntax() const override;
	virtual void PrintCmd() const override;
	virtual void PrintParams() const override;
	virtual bool ReadParams(std::istream &in) override;
	virtual bool ExecCmd(AbstractScene &rScn, const char * sMobObjName, AbstractComChannel &rComChann) override;
	static AbstractInterp4Command * CreateCmd();
};

#endif
