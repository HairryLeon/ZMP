#include "CommandRegistry.hh"
#include <iostream>

bool CommandRegistry::LoadAndRegister(const std::string &path)
{
    LibInterface lib;
    if (!lib.LoadLibrary(path)) {
        std::cerr << "[ERROR] Nie można załadować biblioteki: " << path << std::endl;
        return false;
    }

    std::string name = lib.GetCmdName();

    _CmdMap.emplace(name, std::move(lib));
    return true;
}

bool CommandRegistry::Exists(const std::string &name) const
{
    return _CmdMap.find(name) != _CmdMap.end();
}

AbstractInterp4Command* CommandRegistry::Create(const std::string &name) const
{

    auto it = _CmdMap.find(name);
    if (it == _CmdMap.end()) {
        return nullptr;
    }

    return it->second.CreateCmdInstance();
}
