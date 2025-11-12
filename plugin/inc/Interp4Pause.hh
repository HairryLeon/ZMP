#ifndef INTERP4PAUSE_HH
#define INTERP4PAUSE_HH

#include <iostream>
#include "../inc/AbstractInterp4Command.hh"

class Interp4Pause : public AbstractInterp4Command
{
    int _time_ms;

public:
    Interp4Pause() : _time_ms(0) {}
    virtual ~Interp4Pause() {}

    virtual const char* GetCmdName() const override { return "Pause"; }

    virtual void PrintSyntax() const override {
        std::cout << "   Pause  Czas[ms]" << std::endl;
    }

    virtual void PrintCmd() const override {
        std::cout << "Pause " << _time_ms << std::endl;
    }

    virtual void PrintParams() const override {
        std::cout << "Params: " << _time_ms << std::endl;
    }

    virtual bool ReadParams(std::istream &in) override {
        in >> _time_ms;
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
