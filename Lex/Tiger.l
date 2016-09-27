%{
#include <string.h>
#include "util.h"
#include "tokens.h"
#include "errormsg.h"

static int comment_level = 0;
int charPos=1;

#define INIT_LEN 32
static string str_buf;
static int str_len;
static int str_cap;

int yywrap(void)
{
 charPos=1;
 return 1;
}


void adjust(void)
{
 EM_tokPos=charPos;
 charPos+=yyleng;
}

static void init_buf(void)
{
    str_buf = checked_malloc(INIT_LEN);
    str_buf[0] = 0;
    str_len = 0;
    str_cap = INIT_LEN;
}

static void append_char(char ch)
{
    if (++str_len == str_cap)
    {
        char *p;

        str_cap *= 2;
        p = checked_malloc(str_cap);
        memcpy(p, str_buf, str_len);
        free(str_buf);
        str_buf = p;
    }
    str_buf[str_len - 1] = ch;
    str_buf[str_len] = 0;
}

%}

%x COMMENT STRING

%%
    /* Comments */
"/*"                    {adjust(); comment_level=1; BEGIN(COMMENT);}
<COMMENT>[^*/\n]*       {adjust();}
<COMMENT>"*"+[^*/\n]*   {adjust();}
<COMMENT>"/"+[^*/\n]*   {adjust();}
<COMMENT>\n             {adjust(); EM_newline();}
<COMMENT>"/"+"*"        {adjust(); comment_level++;}
<COMMENT>"*"+"/"        {adjust(); comment_level--; if(comment_level<=0) BEGIN(INITIAL);}

    /* Reserved Words */
while                   {adjust(); return WHILE;}
for  	                {adjust(); return FOR;}
to                      {adjust(); return TO;}
break                   {adjust(); return BREAK;}
let                     {adjust(); return LET;}
in                      {adjust(); return IN;}
end                     {adjust(); return END;}
function                {adjust(); return FUNCTION;}
var                     {adjust(); return VAR;}
type                    {adjust(); return TYPE;}
array                   {adjust(); return ARRAY;}
if                      {adjust(); return IF;}
then                    {adjust(); return THEN;}
else                    {adjust(); return ELSE;}
do                      {adjust(); return DO;}
of                      {adjust(); return OF;}
nil                     {adjust(); return NIL;}

    /* Punctuation Symbols */
","	                    {adjust(); return COMMA;}
":"                     {adjust(); return COLON;}
";"                     {adjust(); return SEMICOLON;}
"("                     {adjust(); return LPAREN;}
")"                     {adjust(); return RPAREN;}
"["                     {adjust(); return LBRACK;}
"]"                     {adjust(); return RBRACK;}
"{"                     {adjust(); return LBRACE;}
"}"                     {adjust(); return RBRACE;}
"."                     {adjust(); return DOT;}
"+"                     {adjust(); return PLUS;}
"-"                     {adjust(); return MINUS;}
"*"                     {adjust(); return TIMES;}
"/"                     {adjust(); return DIVIDE;}
"="                     {adjust(); return EQ;}
"<>"                    {adjust(); return NEQ;}
"<"                     {adjust(); return LT;}
"<="                    {adjust(); return LE;}
">"                     {adjust(); return GT;}
">="                    {adjust(); return GE;}
"&"                     {adjust(); return AND;}
"|"                     {adjust(); return OR;}
":="                    {adjust(); return ASSIGN;}


[ \t\f\v\r]             {adjust();}
\n	                    {adjust(); EM_newline();}
[0-9]+	                {adjust(); yylval.ival=atoi(yytext); return INT;}
[a-zA-Z][a-zA-Z_0-9]*   {adjust(); yylval.sval=String(yytext); return ID;}

    /* Strings */
\"                      {adjust(); init_buf(); BEGIN(STRING);}
<STRING>\"              {adjust(); BEGIN(INITIAL); yylval.sval=str_buf; return STRING;}
<STRING>\n              {adjust(); EM_newline();}
<STRING>\\[0-9]{3}      {adjust(); int result; sscanf(yytext+1, "%d", &result); if(result>0xFF) {EM_error(EM_tokPos,"character out of range");} append_char(result);}
<STRING>\\n             {adjust(); append_char('\n');}
<STRING>\\t             {adjust(); append_char('\t');}
<STRING>\\\"            {adjust(); append_char('\"');}
<STRING>\\\\            {adjust(); append_char('\\');}
<STRING>\\(.|\n)        {adjust(); append_char(yytext[1]);}
<STRING>[^\\\n\"]+      {char *p=yytext; adjust(); while(*p) append_char(*p++);}

.	                    {adjust(); EM_error(EM_tokPos,"illegal token");}
%%