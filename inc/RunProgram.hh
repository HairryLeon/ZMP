#ifndef RUNPROGRAM_HH
#define RUNPROGRAM_HH

#include <string>
#include "CommandRegistry.hh"

bool RunProgram(const std::string &programText, const CommandRegistry &registry);

#endif
