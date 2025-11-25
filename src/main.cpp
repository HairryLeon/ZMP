#include <iostream>
#include <string>
#include <memory>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>

#include "xmlinterp.hh"
#include "Configuration.hh"
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

	xercesc::XMLPlatformUtils::Initialize();
	{
		Configuration cfg;

		std::unique_ptr<xercesc::SAX2XMLReader> parser(
			xercesc::XMLReaderFactory::createXMLReader()
		);
		XMLInterp4Config handler(cfg);
		parser->setContentHandler(&handler);
		parser->setErrorHandler(&handler);

		parser->parse("config/config.xml");

		for(const auto &lib : cfg.GetLibs()){
			registry.LoadAndRegister(std::string("./libs/") + lib);
		}
	}
	xercesc::XMLPlatformUtils::Terminate();

        //registry.LoadAndRegister("./libs/libInterp4Move.so");
        //registry.LoadAndRegister("./libs/libInterp4Rotate.so");
        //registry.LoadAndRegister("./libs/libInterp4Pause.so");
        //registry.LoadAndRegister("./libs/libInterp4Set.so");

        RunProgram(program, registry);
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Błąd: " << e.what() << std::endl;
        return 1;
    }
}
