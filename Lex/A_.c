//
// Created by Reesman, Paul on 9/23/16.
//

#include "../Utils/Util.h"
#include "A_.h"

// Statement Constructors
A_stm A_CompoundStm(A_stm stm1, A_stm stm2)
{
    A_stm s = checked_malloc(sizeof(*s));
    s->kind = A_stm_::A_compoundStm;
    s->u.compound.stm1 = stm1;
    s->u.compound.stm2 = stm2;
    return s;
}
A_stm A_AssignStm(string id, A_exp exp)
{
    A_stm s = checked_malloc(sizeof(*s));
    s->kind = A_stm_::A_assignStm;
    s->u.assign.id = id;
    s->u.assign.exp = exp;
    return s;
}
A_stm A_PrintStm(A_expList exps)
{
    A_stm s = checked_malloc(sizeof(*s));
    s->kind = A_stm_::A_printStm;
    s->u.print.exps = exps;
    return s;
}

// Expression Constructors
A_exp A_IdExp(string id)
{
    A_exp s = checked_malloc(sizeof(*s));
    s->kind = A_exp_::A_idExp;
    s->u.id = id;
    return s;
}
A_exp A_NumExp(int num)
{
    A_exp s = checked_malloc(sizeof(*s));
    s->kind = A_exp_::A_numExp;
    s->u.num = num;
    return s;
}
A_exp A_OpExp(A_exp left, A_binop oper, A_exp right)
{
    A_exp s = checked_malloc(sizeof(*s));
    s->kind = A_exp_::A_opExp;
    s->u.op.left = left;
    s->u.op.oper = oper;
    s->u.op.right = right;
    return s;
}
A_exp A_EseqExp(A_stm stm, A_exp exp)
{
    A_exp s = checked_malloc(sizeof(*s));
    s->kind = A_exp_::A_eseqExp;
    s->u.eseq.stm = stm;
    s->u.eseq.exp = exp;
    return s;
}

// Expression List Constructors
A_expList A_PairExpList(A_exp head, A_expList tail)
{
    A_expList s = checked_malloc(sizeof(*s));
    s->kind = A_expList_::A_pairExpList;
    s->u.pair.head = head;
    s->u.pair.tail = tail;
    return s;
}
A_expList A_LastExpList(A_exp last)
{
    A_expList s = checked_malloc(sizeof(*s));
    s->kind = A_expList_::A_lastExpList;
    s->u.last = last;
    return s;
}
