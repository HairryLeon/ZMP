#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <memory>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "xmlinterp.hh"
#include "Configuration.hh"
#include "RunPreprocessor.hh"
#include "CommandRegistry.hh"
#include "RunProgram.hh"
#include "Port.hh"
#include "AccessControl.hh"

int Send(int Sk2Server, const char *sMesg)
{
	ssize_t IlWyslanych;
	ssize_t IlDoWyslania = (ssize_t)strlen(sMesg);
	while((IlWyslanych = write(Sk2Server, sMesg, IlDoWyslania)) > 0 ){
		IlDoWyslania -=IlWyslanych;
		sMesg += IlWyslanych;
	}
	if(IlWyslanych < 0) {
		std::cerr << "*** Blad przeslania napisu." << std::endl;
	}
	return 0;
}

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

		int sock = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in sa{};
		sa.sin_family = AF_INET;
		sa.sin_port = htons(PORT);
		inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr);

		if (connect(sock, (sockaddr*)&sa, sizeof(sa)) != 0) {
    			perror("connect");
    			return 1;
		}


		Send(sock, "Clear\n");


		auto cubes = cfg.GetCubes();
		std::vector<Configuration::Cube> sorted = cubes;   // kopia, żeby móc sortować
		std::sort(sorted.begin(), sorted.end(),
          	[](const auto& a, const auto& b){ return a.Name.size() < b.Name.size(); });


		for (const auto &c : sorted) {
    			std::ostringstream cmd;
    			cmd << "AddObj Name=" << c.Name
        		<< " Shift=("     << c.Shift[0]     << "," << c.Shift[1]     << "," << c.Shift[2]     << ")"
        		<< " Scale=("     << c.Scale[0]     << "," << c.Scale[1]     << "," << c.Scale[2]     << ")"
        		<< " RotXYZ_deg=("<< c.RotXYZ_deg[0]<< "," << c.RotXYZ_deg[1]<< "," << c.RotXYZ_deg[2]<< ")"
        		<< " Trans_m=("   << c.Trans_m[0]   << "," << c.Trans_m[1]   << "," << c.Trans_m[2]   << ")"
        		<< " RGB=("       << c.RGB[0]       << "," << c.RGB[1]       << "," << c.RGB[2]       << ")"
        		<< "\n";
    			Send(sock, cmd.str().c_str());
		}

		Send(sock, "Close\n");
		close(sock);
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
