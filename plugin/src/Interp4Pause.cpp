#include "Interp4Pause.hh"

extern "C" {
    AbstractInterp4Command* CreateCmd() {
        return new Interp4Pause;
    }
}
