#include "Interp4Set.hh"

extern "C" {
    AbstractInterp4Command* CreateCmd() {
        return new Interp4Set;
    }
}
