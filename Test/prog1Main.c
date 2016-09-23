//
// Created by Reesman, Paul on 9/23/16.
//

#include <stdio.h>

#include "prog1Main.h"
#include "prog1.h"
#include "../Lex/A_.h"
#include "../Utils/Util.h"

int mainProg1()
{
    // Part 1

    // Part 2
    interp(prog());

    return 1;
}

void interp(A_stm stm)
{
    Table_ t = checked_malloc(sizeof(*t));
    interpStm(stm, t);
    while(t)
    {
        printf("ID: %s\t\t\tValue: %d\n", t->id, t->value);
        t = t->tail;
    }
}

Table_ interpStm(A_stm s, Table_ t)
{
    switch(s->kind) {
        case A_compoundStm:
            return interpStm(s->u.compound.stm2, interpStm(s->u.compound.stm1, t));
        case A_assignStm: {
            IntAndTable_ iat = interpExp(s->u.assign.exp, t);
            return Table(s->u.assign.id, iat->i, iat->t);
        }
        case A_printStm:
            //TODO
            break;
    }
}

IntAndTable_ interpExp(A_exp e, Table_ t)
{
    switch(e->kind) {
        case A_idExp:
            //TODO
            //return IAT()
        case A_numExp:
            return IAT(e->u.num, t);
        case A_opExp:
            switch(e->u.op.oper) {
                case A_plus: {
                    IntAndTable_ iat1 = interpExp(e->u.op.left, t);
                    IntAndTable_ iat2 = interpExp(e->u.op.right, iat1->t);
                    return IAT(iat1->i + iat2->i, iat2->t);
                }
                case A_minus: {
                    IntAndTable_ iat1 = interpExp(e->u.op.left, t);
                    IntAndTable_ iat2 = interpExp(e->u.op.right, iat1->t);
                    return IAT(iat1->i - iat2->i, iat2->t);
                }
                case A_times: {
                    IntAndTable_ iat1 = interpExp(e->u.op.left, t);
                    IntAndTable_ iat2 = interpExp(e->u.op.right, iat1->t);
                    return IAT(iat1->i * iat2->i, iat2->t);
                }
                case A_div: {
                    IntAndTable_ iat1 = interpExp(e->u.op.left, t);
                    IntAndTable_ iat2 = interpExp(e->u.op.right, iat1->t);
                    return IAT(iat1->i / iat2->i, iat2->t);
                }
            }
        case A_eseqExp: {
            Table_ t2 = interpStm(e->u.eseq.stm, t);
            return interpExp(e->u.eseq.exp, t);
        }
    }
}

Table_ Table(string id, int value, struct table *tail)
{
    Table_ t = checked_malloc(sizeof(*t));
    t->id = id;
    t->value = value;
    t->tail = tail;
    return t;
}

IntAndTable_ IAT(int i, Table_ t)
{
    IntAndTable_ iat = checked_malloc(sizeof(*iat));
    iat->i = i;
    iat->t = t;
    return iat;
}

int lookup(Table_ t, string key)
{
    if(!t)
        return 0;
    return t->id == key ? t->value : lookup(t->tail, key);
}