#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <string>
#include "AbstractInterp4Command.hh"

class LibInterface
{
    void *_LibHandler = nullptr;
    AbstractInterp4Command* (*_pCreateCmd)(void) = nullptr;
    std::string _CmdName;

public:
    LibInterface() = default;
    ~LibInterface();

    // Kopiowanie ZABRONIONE (jeden właściciel jednego dlopen handle)
    LibInterface(const LibInterface&) = delete;
    LibInterface& operator=(const LibInterface&) = delete;

    // WŁASNE przenoszenie: przejmij wskaźniki i WYZERUJ źródło
    LibInterface(LibInterface&& other) noexcept
    : _LibHandler(other._LibHandler),
      _pCreateCmd(other._pCreateCmd),
      _CmdName(std::move(other._CmdName))
    {
        other._LibHandler = nullptr;
        other._pCreateCmd = nullptr;
    }

    LibInterface& operator=(LibInterface&& other) noexcept
    {
        if (this != &other) {
            // zwolnij aktualny zasób (jeśli jakiś jest)
            if (_LibHandler) {
                // zamknie to destruktor, ale możemy wyzerować tu, aby zachować prostotę
                // zostawiamy zwolnienie w destruktorze – wystarczy
            }
            _LibHandler = other._LibHandler;
            _pCreateCmd = other._pCreateCmd;
            _CmdName    = std::move(other._CmdName);

            other._LibHandler = nullptr;
            other._pCreateCmd = nullptr;
        }
        return *this;
    }

    bool LoadLibrary(const std::string &libPath);
    AbstractInterp4Command* CreateCmdInstance() const;
    std::string GetCmdName() const;
};

#endif
