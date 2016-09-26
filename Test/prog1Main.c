//
// Created by Reesman, Paul on 9/23/16.
//

#include <stdio.h>
#include <string.h>

#include "prog1Main.h"
#include "prog1.h"
#include "../Intro/A_.h"
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
    Table_ t2 = interpStm(stm, t);
    while(t2)
    {
        printf("ID: %s\t\t\tValue: %d\n", t2->id, t2->value);
        t2 = t2->tail;
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
        case A_printStm: {
            IntAndTable_ iat = interpExpList(s->u.print.exps, t);
            printf("%s\n", iat->s);
            return iat->t;
        }
    }
    return t;
}

IntAndTable_ interpExp(A_exp e, Table_ t)
{
    switch(e->kind) {
        case A_idExp: {
            int i = lookup(t, e->u.id);
            return IAT(i, t);
        }
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
            return interpExp(e->u.eseq.exp, t2);
        }
    }
}

IntAndTable_ interpExpList(A_expList e, Table_ t)
{
    switch(e->kind) {
        case A_pairExpList: {
            IntAndTable_ iat1 = interpExp(e->u.pair.head, t);
            IntAndTable_ iat2 = interpExpList(e->u.pair.tail, iat1->t);
            iat1->s = IntString(iat1->i);
            char str[22];
            strcpy(str, iat1->s);
            strcat(str, " ");
            strcat(str, iat2->s);
            iat2->s = String(str);
            return iat2;
        }
        case A_lastExpList: {
            IntAndTable_ iat = interpExp(e->u.last, t);
            iat->s = IntString(iat->i);
            return iat;
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