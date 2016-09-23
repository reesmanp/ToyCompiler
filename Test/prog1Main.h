//
// Created by Reesman, Paul on 9/23/16.
//

#ifndef PROJECT_PROG1MAIN_H
#define PROJECT_PROG1MAIN_H

typedef struct table *Table_;
typedef struct intAndtable *IntAndTable_;
typedef char *string;
typedef struct A_stm_ *A_stm;
typedef struct A_exp_ *A_exp;

struct table
{
    string id;
    int value;
    Table_ tail;
};

struct intAndtable
{
    int i;
    Table_ t;
};

int mainProg1();
void interp(A_stm);
Table_ interpStm(A_stm, struct table *);
IntAndTable_ interpExp(A_exp, struct table *);
Table_ Table(string, int, struct table *);
IntAndTable_ IAT(int, struct table *);
int lookup(struct table *, string);

#endif //PROJECT_PROG1MAIN_H
