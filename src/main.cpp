#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "RunPreprocessor.hh"
#include "LibInterface.hh"

using namespace std;

int main()
{
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: libInterp4Move.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);


  AbstractInterp4Command *pCmd = pCreateCmd_Move();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
// preprocesor
	std::cout << "streszczenie.txt: " << std::endl;
	std::string content = RunPreprocessor("src/scenariusz.txt");
	std::cout << content << std::endl;

// libinterface

	LibInterface lib;
	lib.LoadLibrary("./libs/libInterp4Move.so");

	AbstractInterp4Command *cmd = lib.CreateCmdInstance();
	std::cout << cmd->GetCmdName() << std::endl;
	cmd->PrintSyntax();

	delete cmd;

// wtyczka 2
	LibInterface libRotate;
	libRotate.LoadLibrary("./libs/libInterp4Rotate.so");

	AbstractInterp4Command *cmd2 = libRotate.CreateCmdInstance();
	cmd2->PrintSyntax();
	delete cmd2;

  delete pCmd;

  dlclose(pLibHnd_Move);
}
