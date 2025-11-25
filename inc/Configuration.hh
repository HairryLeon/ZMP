#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <string>
#include <vector>

class Configuration {
public:
	struct Cube {
		std:: string Name;
		double Shift[3]		{0.0, 0.0, 0.0};
		double Scale[3]		{1.0, 1.0, 1.0};
		double RotXYZ_deg[3]	{0.0, 0.0, 0.0};
		double Trans_m[3]	{0.0, 0.0, 0.0};
		int RGB[3]		{128, 128, 128};
	};

	void AddLib(const std::string &name) { _Libs.push_back(name); }
	const std::vector<std::string>& GetLibs() { return _Libs; }

	void AddCube(const Cube &c) { _Cubes.push_back(c); }
	const std::vector<Cube>& GetCubes() const { return _Cubes; }
private:
	std::vector<Cube> _Cubes;
	std::vector<std::string> _Libs;

};


#endif
