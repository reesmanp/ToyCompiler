//
// Created by Reesman, Paul on 9/26/16.
//

#ifndef TOYCOMPILER_ERRORMSG_H
#define TOYCOMPILER_ERRORMSG_H

extern bool EM_anyErrors;

void EM_newline(void);

extern int EM_tokPos;

void EM_error(int, string,...);
void EM_impossible(string,...);
void EM_reset(string filename);

#endif //TOYCOMPILER_ERRORMSG_H
