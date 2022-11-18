#include <math.h>
#include <stdio.h>

#include "types.h"

int eval(Wff *wff, int *interp) {
    if (wff->atomic) return interp[wff->prop];

    switch (wff->op) {
        case NOT:
            return !eval(wff->o2, interp);
        case AND:
            return eval(wff->o1, interp) && eval(wff->o2, interp);
        case OR:
            return eval(wff->o1, interp) || eval(wff->o2, interp);
        case IMPLIES:
            return !eval(wff->o1, interp) || eval(wff->o2, interp);
        case IFF:
            return eval(wff->o1, interp) == eval(wff->o2, interp);
        default:
            return 0;
            break;
    }
}
