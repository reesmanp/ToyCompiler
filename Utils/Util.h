//
// Created by Reesman, Paul on 9/23/16.
//

#ifndef TOYCOMPILER_UTIL_H
#define TOYCOMPILER_UTIL_H

#include <assert.h>

typedef char *string;
typedef char bool;

#define TRUE 1
#define FALSE 0

void *checked_malloc(int);
string String(char *);
string IntString(int);

typedef struct U_boolList_ *U_boolList;
struct U_boolList_ {bool head; U_boolList tail;};
U_boolList U_BoolList(bool head, U_boolList tail);

#endif //TOYCOMPILER_UTIL_H
