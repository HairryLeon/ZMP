#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <string>
#include "AbstractInterp4Command.hh"

class LibInterface
{
	void *_LibHandler = nullptr;
	AbstractInterp4Command* (*_pCreateCmd)(void) = nullptr;
	std::string _LibName;

public:
	LibInterface() = default;
	~LibInterface();

	bool LoadLibrary(const std::string &libPath);
	AbstractInterp4Command* CreateCmdInstance() const;
	std::string GetCmdName() const;
};

#endif
