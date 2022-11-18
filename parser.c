#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

char *s;

int props[12] = {0};
int props_no = 0;

int *get_props() {
    int *_props = (int*) malloc(sizeof props);
    memcpy(_props, props, sizeof props);
    return _props;
}

int get_props_no() {
    return props_no;
}

void skipSpace() {
    while (*s == ' ') s++;
}

Wff *makeWff() {
    return (Wff *)calloc(1, sizeof(Wff));
}

Wff *parseParen();

Wff *parseProp() {
    if (*s >= 'P' && *s <= 'Z') {
        Wff *wff = makeWff();
        Prop prop = (Prop)(*(s++) - 'P' + 1);
        wff->atomic = 1;
        if (!props[prop]) {
            props[prop] = 1;
            props_no++;
        }
        wff->prop = prop;
        return wff;
    } else if (*s == '(') {
        return parseParen();
    } else {
        printf("EXPECTED PROP VAR, GOT %c", *s);
        exit(1);
    }
}

Wff *parseNot() {
    if (*s == 'n' && *(s + 1) == 'o' && *(s + 2) == 't') {
        Wff *wff = makeWff();
        s += 3;
        skipSpace();
        wff->op = NOT;
        wff->o2 = parseProp();
        return wff;

    } else {
        return parseProp();
    }
}

Wff *parseAnd() {
    Wff *o1 = parseNot();
    skipSpace();
    while (*s == 'a' && s[1] == 'n' && s[2] == 'd') {
        Wff *wff = makeWff(), *o2;
        s += 3;
        wff->op = AND;
        wff->o1 = o1;

        skipSpace();

        o2 = parseNot();
        wff->o2 = o2;

        o1 = wff;

        skipSpace();
    }
    return o1;
}

Wff *parseOr() {
    Wff *o1 = parseAnd();
    skipSpace();
    while (*s == 'o' && s[1] == 'r') {
        Wff *wff = makeWff(), *o2;
        s += 2;
        wff->op = OR;
        wff->o1 = o1;

        skipSpace();

        o2 = parseAnd();
        wff->o2 = o2;

        o1 = wff;

        skipSpace();
    }
    return o1;
}

Wff *parseImp() {
    Wff *o1 = parseOr();
    skipSpace();
    if (*s == 't' && s[1] == 'h' && s[2] == 'e' && s[3] == 'n') {
        Wff *wff = makeWff(), *o2;
        s += 4;
        wff->op = IMPLIES;
        wff->o1 = o1;

        skipSpace();

        o2 = parseImp();
        wff->o2 = o2;

        o1 = wff;
    }
    return o1;
}

Wff *parseIff() {
    Wff *o1 = parseImp();
    skipSpace();
    while (*s == 'i' && s[1] == 'f' && s[2] == 'f') {
        Wff *wff = makeWff(), *o2;
        s += 3;
        wff->op = IFF;
        wff->o1 = o1;

        skipSpace();

        o2 = parseImp();
        wff->o2 = o2;

        o1 = wff;

        skipSpace();
    }
    return o1;
}

Wff *parseParen() {
    Wff *wff;
    s++;
    skipSpace();
    wff = parseIff();
    skipSpace();
    if (*s++ != ')') {
        printf("EXPECTED )");
        exit(1);
    }
    return wff;
}

Wff *parse(char *_s) {
    Wff *wff;
    s = _s;
    skipSpace();
    wff = parseIff();
    skipSpace();
    if (*s != '\0' && *s != '\n') {
        printf("UNEXPECTED TOKEN: %c", *s);
        exit(1);
    }
    return wff;
}