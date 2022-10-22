#include <stdio.h>
#include <stdlib.h>

#include "types.h"

char *wff_to_string(Wff *wff) {
    if (wff->atomic) {
        char *s = malloc(1);
        *s = wff->prop + 'P' - 1;
        return s;
    } else {
        char *o1_str = "", *o2_str, *op, *s = malloc(100);
        if (wff->op != NOT) o1_str = wff_to_string(wff->o1);
        o2_str = wff_to_string(wff->o2);
        switch (wff->op) {
            case NOT:
                op = "not";
                break;
            case AND:
                op = "and";
                break;
            case OR:
                op = "or";
                break;
            case IMPLIES:
                op = "then";
                break;
            case IFF:
                op = "iff";
                break;
            case NO_OP:
            default:
                op = "";
                break;
        }
        sprintf(s, "(%s %s %s)", o1_str, op, o2_str);
        return s;
    }
}