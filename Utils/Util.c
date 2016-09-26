//
// Created by Reesman, Paul on 9/23/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Util.h"

string String(char *s)
{
    string p = checked_malloc(strlen(s)+1);
    strcpy(p,s);
    return p;
}

string IntString(int i)
{
    char s[10];
    sprintf(s, "%d", i);
    return String(s);
}

void *checked_malloc(int len)
{
    void *p = malloc(len);
    assert(p);
    return p;
}

U_boolList U_BoolList(bool head, U_boolList tail)
{ U_boolList list = checked_malloc(sizeof(*list));
    list->head = head;
    list->tail = tail;
    return list;
}