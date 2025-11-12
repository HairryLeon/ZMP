#ifndef COMMANDREGISTRY_HH
#define COMMANDREGISTRY_HH

#include <map>
#include <string>
#include "LibInterface.hh"

class CommandRegistry
{
    std::map<std::string, LibInterface> _CmdMap;

public:
    bool LoadAndRegister(const std::string &path);
    bool Exists(const std::string &name) const;
    AbstractInterp4Command* Create(const std::string &name) const;
};

#endif
