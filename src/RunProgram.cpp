#include "RunProgram.hh"
#include <sstream>
#include <iostream>

bool RunProgram(const std::string &programText, const CommandRegistry &registry)
{
    std::istringstream input(programText);
    std::string line;
    int lineNo = 0;

    while (std::getline(input, line))
    {
        lineNo++;

        if (line.find_first_not_of(" \t\r\n") == std::string::npos)
            continue;

        std::istringstream ls(line);
        std::string cmdName;
        ls >> cmdName;

        AbstractInterp4Command *cmd = registry.Create(cmdName);
        if (!cmd)
        {
            std::cerr << "Błąd w linii " << lineNo
                      << ": nieznane polecenie \"" << cmdName << "\"\n";
            continue;
        }

        if (!cmd->ReadParams(ls)) {
            std::cerr << "Błąd w linii " << lineNo
                      << ": niepoprawne parametry dla komendy \"" << cmdName << "\"\n";
            delete cmd;
            continue;
        }

        cmd->PrintCmd();
        cmd->PrintParams();

        delete cmd;
    }

    return true;
}
