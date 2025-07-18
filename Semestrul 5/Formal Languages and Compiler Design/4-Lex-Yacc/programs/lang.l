%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lang.tab.h"


%}

%option noyywrap
%option yylineno

%x COMMENT

DIGIT      [0-9]
LETTER     [a-zA-Z]
ID_FIRST   [a-zA-Z]
ID_FOLLOW  [a-zA-Z0-9_]

%%
	
	/* ---------- Reserved Words ---------- */
"array"     { printf("TOKEN: ARRAY\n"); return ARRAY; }
"char"      { printf("TOKEN: CHAR\n"); return CHAR; }
"const"     { printf("TOKEN: CONST\n"); return CONST; }
"else"      { printf("TOKEN: ELSE\n"); return ELSE; }
"if"        { printf("TOKEN: IF\n"); return IF; }
"int"       { printf("TOKEN: INT\n"); return INT; }
"of"        { printf("TOKEN: OF\n"); return OF; }
"read"      { printf("TOKEN: READ\n"); return READ; }
"while"     { printf("TOKEN: WHILE\n"); return WHILE; }
"print"     { printf("TOKEN: PRINT\n"); return PRINT; }
"string"    { printf("TOKEN: STRING\n"); return STRING; }

	/* ---------- Operators & Delimiters ---------- */
"=="        { printf("TOKEN: EQ\n"); return EQ; }
"!="        { printf("TOKEN: NEQ\n"); return NEQ; }
"<="        { printf("TOKEN: LE\n"); return LE; }
">="        { printf("TOKEN: GE\n"); return GE; }
"<"         { printf("TOKEN: LT\n"); return LT; }
">"         { printf("TOKEN: GT\n"); return GT; }
"="         { printf("TOKEN: ASSIGN\n"); return ASSIGN; }
"+"         { printf("TOKEN: PLUS\n"); return PLUS; }
"-"         { printf("TOKEN: MINUS\n"); return MINUS; }
"*"         { printf("TOKEN: MULT\n"); return MULT; }
"/"         { printf("TOKEN: DIV\n"); return DIV; }
"%"         { printf("TOKEN: MOD\n"); return MOD; }
"("         { printf("TOKEN: LPAREN\n"); return LPAREN; }
")"         { printf("TOKEN: RPAREN\n"); return RPAREN; }
"{"         { printf("TOKEN: LBRACE\n"); return LBRACE; }
"}"         { printf("TOKEN: RBRACE\n"); return RBRACE; }
"["         { printf("TOKEN: LBRACK\n"); return LBRACK; }
"]"         { printf("TOKEN: RBRACK\n"); return RBRACK; }
";"         { printf("TOKEN: SEMI\n"); return SEMI; }

	/* ---------- Comments ---------- */
#[^\n]*     { /* Ignore comments starting with '#' */ }

	/* ---------- Identifiers ---------- */
{ID_FIRST}{ID_FOLLOW}*  {
    yylval.sval = strdup(yytext);
    printf("TOKEN: IDENTIFIER (%s)\n", yytext);
    return IDENTIFIER;
}

	/* ---------- Integer Constants ---------- */
{DIGIT}+   {
    yylval.ival = atoi(yytext);
    printf("TOKEN: INT_CONST (%s)\n", yytext);
    return INT_CONST;
}

	/* ---------- Character Constants ---------- */
\'[a-zA-Z0-9_]\'  {
    yylval.ival = yytext[1];
    printf("TOKEN: CHAR_CONST (%s)\n", yytext);
    return CHAR_CONST;
}

	/* ---------- String Constants ---------- */
\"[^\"]*\"  {
    size_t len = strlen(yytext);
    char *str  = (char *)malloc(len);
    strncpy(str, yytext + 1, len - 2);
    str[len - 2] = '\0';
    yylval.sval = str;
    printf("TOKEN: STRING_CONST (%s)\n", str);
    return STRING_CONST;
}

	/* ---------- Whitespace ---------- */
[ \t]+      { /* Skip spaces and tabs */ }
\n          { yylineno++; }

	/* ---------- Unknown Characters ---------- */
. { fprintf(stderr, "Unexpected character '%s' on line %d\n", yytext, yylineno); }

%%

