#include "LibInterface.hh"
#include <iostream>
#include <dlfcn.h>

bool LibInterface::LoadLibrary(const std::string &libPath){
	_LibHandler = dlopen(libPath.c_str(), RTLD_LAZY);
	if(!_LibHandler){
		std::cerr << "Nie mozna otworzyc biblioteki: " << libPath << std::endl;
		return false;
	}

	void *pFun = dlsym(_LibHandler, "CreateCmd");
	if(!pFun){
		std::cerr << "Nie znaleziono CreateCmd() w " << libPath << std::endl;
		return false;
	}

	_pCreateCmd = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);
	_LibName = libPath;
	return true;
}

AbstractInterp4Command* LibInterface::CreateCmdInstance() const{
	if(!_pCreateCmd) return nullptr;
	return _pCreateCmd();
}

std::string LibInterface::GetCmdName() const {
	AbstractInterp4Command* cmd = CreateCmdInstance();
	std::string result = cmd->GetCmdName();
	delete cmd;
	return result;
}

LibInterface::~LibInterface()
{
	if(_LibHandler != nullptr){
		dlclose(_LibHandler);
	}
}
