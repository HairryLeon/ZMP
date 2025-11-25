#include "LibInterface.hh"
#include <dlfcn.h>
#include <iostream>

using namespace std;

bool LibInterface::LoadLibrary(const std::string &libPath)
{
    dlerror();

    _LibHandler = dlopen(libPath.c_str(), RTLD_LAZY);
    if (!_LibHandler) {
        std::cerr << "Nie mozna otworzyc biblioteki: " << libPath << std::endl;
        std::cerr << dlerror() << std::endl;
        return false;
    }

    dlerror();
    void *pFun = dlsym(_LibHandler, "CreateCmd");
    const char *error = dlerror();
    if (error != nullptr) {
        std::cerr << "Nie znaleziono CreateCmd() w: " << libPath << std::endl;
        std::cerr << error << std::endl;
        dlclose(_LibHandler);
        _LibHandler = nullptr;
        return false;
    }

    _pCreateCmd = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

     AbstractInterp4Command *cmd = _pCreateCmd();
    _CmdName = cmd->GetCmdName();
    delete cmd;

    return true;
}

AbstractInterp4Command* LibInterface::CreateCmdInstance() const
{
    if (!_pCreateCmd) return nullptr;
    return _pCreateCmd();
}

std::string LibInterface::GetCmdName() const
{
    return _CmdName;
}

LibInterface::~LibInterface()
{
    if (_LibHandler != nullptr) {
        dlclose(_LibHandler);
        _LibHandler = nullptr;
    }
}
