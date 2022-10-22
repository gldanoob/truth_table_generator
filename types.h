#ifndef TYPES_H
#define TYPES_H

typedef enum {
    NO_PROP,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z
} Prop;

typedef enum {
    NO_OP,
    NOT,
    AND,
    OR,
    IMPLIES,
    IFF
} Op;

typedef struct _wff {
    struct _wff *o1;
    Op op;
    struct _wff *o2;

    int atomic;
    Prop prop;
} Wff;

#endif