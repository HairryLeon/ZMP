#include "RunPreprocessor.hh"
#include <iostream>
#include <sstream>
#include <memory>
#include <stdexcept>

std::string RunPreprocessor(const std::string &filename){
	std::ostringstream output;
	std::string command = "cpp -P " + filename;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
	if(!pipe){
		throw std::runtime_error("Nie udalo sie uruchomic preprocesora dla pliku" + filename);
	}

	char buffer[512];
	while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
		output << buffer;
	}
	return output.str();
}
