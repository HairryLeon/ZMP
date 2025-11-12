#ifndef INTERP4SET_HH
#define INTERP4SET_HH

#include <string>
#include <iostream>
#include "../inc/AbstractInterp4Command.hh"   // ścieżka względna względem katalogu plugin/inc

class Interp4Set : public AbstractInterp4Command
{
    std::string _ObjName;
    double _x, _y, _z;
    double _roll, _pitch, _yaw;

public:
    Interp4Set()
        : _ObjName(), _x(0), _y(0), _z(0), _roll(0), _pitch(0), _yaw(0)
    {}

    virtual ~Interp4Set() {}

    virtual const char* GetCmdName() const override { return "Set"; }

    virtual void PrintSyntax() const override {
        std::cout << "   Set  NazwaObiektu  x y z  roll pitch yaw" << std::endl;
    }

    virtual void PrintCmd() const override {
        std::cout << "Set " << _ObjName << " "
                  << _x << " " << _y << " " << _z << " "
                  << _roll << " " << _pitch << " " << _yaw << std::endl;
    }

    virtual void PrintParams() const override {
        std::cout << "Params: " << _ObjName << " "
                  << _x << " " << _y << " " << _z << " "
                  << _roll << " " << _pitch << " " << _yaw << std::endl;
    }

    virtual bool ReadParams(std::istream &in) override {
        in >> _ObjName >> _x >> _y >> _z >> _roll >> _pitch >> _yaw;
        return !in.fail();
    }

    virtual bool ExecCmd(AbstractScene&, const char*, AbstractComChannel&) override {
        // Etap 1: brak realnej egzekucji
        return true;
    }
};

extern "C" {
    AbstractInterp4Command* CreateCmd();
}

#endif
