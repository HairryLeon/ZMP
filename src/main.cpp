#include <iostream>
#include "RunPreprocessor.hh"
#include "CommandRegistry.hh"
#include "RunProgram.hh"

int main()
{
    try
    {
        std::string program = RunPreprocessor("src/scenariusz.txt");

        std::cout << "\n=== Po preprocesorze ===\n";
        std::cout << program << std::endl;

        CommandRegistry registry;
        registry.LoadAndRegister("./libs/libInterp4Move.so");
        registry.LoadAndRegister("./libs/libInterp4Rotate.so");
        registry.LoadAndRegister("./libs/libInterp4Pause.so");
        registry.LoadAndRegister("./libs/libInterp4Set.so");

        RunProgram(program, registry);
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Błąd: " << e.what() << std::endl;
        return 1;
    }
}
