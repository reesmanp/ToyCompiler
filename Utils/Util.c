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

void *checked_malloc(int len)
{
    void *p = malloc(len);
    assert(p);
    return p;
}