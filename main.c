#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "eval.h"
#include "parser.h"
#include "printwff.h"
#include "types.h"

void table_gen(Wff *wff, int *props, int props_no) {
    int i = 0, n = 0, r = 0;
    while (n < props_no) {
        if (props[i]) {
            printf(" %c |", (char)(i + 'P' - 1));
            n++;
        }
        i++;
    }
    printf(" %s\n", wff_to_string(wff));
    for (r = 0; r < pow(2, props_no); r++) {
        int interp[12], res;
        i = n = 0;
        while (n < props_no) {
            if (props[i]) {
                interp[i] = (r >> (props_no - n - 1)) % 2;
                printf(" %c |", (interp[i]) ? 'T' : 'F');
                n++;
            }
            i++;
        }
        res = eval(wff, interp);
        printf(" %c\n", res ? 'T' : 'F');
    }
}

int main(int argc, char const *argv[]) {
    Wff *wff;
    char *s = malloc(100);
    printf("Input your formula: ");
    fgets(s, 100, stdin);

    wff = parse(s);

    table_gen(wff, get_props(), get_props_no());

    return 0;
}