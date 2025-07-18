%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lang.tab.h"

extern FILE *yyin;
extern int yylineno;

void yyerror(const char *s);
int yylex(void);

%}

%union {
    int   ival;   // For integer constants or character codes
    char *sval;   // For string constants or identifiers
}

%token <sval> IDENTIFIER STRING_CONST
%token <ival> INT_CONST CHAR_CONST
%token ARRAY CHAR CONST ELSE IF INT OF READ WHILE PRINT STRING
%token PLUS MINUS MULT DIV MOD ASSIGN LT LE EQ NEQ GE GT
%token LPAREN RPAREN LBRACE RBRACE LBRACK RBRACK SEMI COMMENT

%type <sval> print_type
%type <ival> expression factor

%%

program
   : LBRACE statement_list RBRACE
	{
     	 printf("\n Parsing completed successfully.\n");
    	}
       ;

statement_list
	: statement_list statement
		{ printf("PRODUCTION: statement_list -> statement_list statement\n"); }
        | statement 
		{ printf("PRODUCTION: statement_list -> statement\n"); }
              ; 
statement
  : simple_statement SEMI
    { printf("PRODUCTION: statement -> simple_statement ;\n"); }
  | struct_statement
    { printf("PRODUCTION: statement -> struct_statement\n"); }
  | comment
    { printf("PRODUCTION: statement -> comment ;\n"); }
  ;

comment: COMMENT
       ;

/* ---------- Simple Statements ---------- */
simple_statement
  : read_statement
    { printf("PRODUCTION: simple_statement -> read_statement\n"); }
  | print_statement
    { printf("PRODUCTION: simple_statement -> print_statement\n"); }
  | assign_statement
    { printf("PRODUCTION: simple_statement -> assign_statement\n"); }
  | declaration_statement
    { printf("PRODUCTION: simple_statement -> declaration_statement\n"); }
  ;


read_statement
  : READ LPAREN IDENTIFIER RPAREN
    {
      printf("PRODUCTION: read_statement -> read ( identifier )\n");
    }
  ;

print_statement
  : PRINT LPAREN print_type RPAREN
    {
      printf("PRODUCTION: print_statement -> print ( print_type )\n");
    }
  ;

print_type: IDENTIFIER       { $$ = $1; }
          | STRING_CONST     { $$ = $1; }
          | INT_CONST        { $$ = strdup("integer"); }
          | CHAR_CONST       { $$ = strdup("character"); }
          ;

assign_statement: IDENTIFIER ASSIGN expression
	{
      printf("PRODUCTION: assign_statement -> identifier = expression\n");
    }
  ;

declaration_statement
  : type IDENTIFIER
    {
      printf("PRODUCTION: declaration_statement -> type identifier\n");
    }
  ;

/* ---------- Types ---------- */
type
  : simple_type
    { printf("PRODUCTION: type -> simple_type\n"); }
  | arraydecl
    { printf("PRODUCTION: type -> arraydecl\n"); }
  ;


simple_type
  : STRING
    { printf("simple_type -> string\n"); }
  | INT
    { printf("simple_type -> int\n"); }
  | CHAR
    { printf("simple_type -> char\n"); }
  ;


arraydecl
  : ARRAY LBRACK INT_CONST RBRACK simple_type
    {
      printf("arraydecl -> array [ no ] simple_type\n");
    }
  ;

/* ---------- Structural Statements ---------- */
struct_statement
  : decision_statement
    {
      printf("struct_statement -> decision_statement\n");
    }
  | while_statement
    {
      printf("struct_statement -> while_statement\n");
    }
  ;

decision_statement
  : if_statement else_clause
    {
      printf("decision_statement -> if_statement else_clause\n");
    }
  ;

if_statement
  : IF LPAREN condition RPAREN LBRACE statement_list RBRACE
    {
      printf("if_statement -> if ( condition ) { statement_list }\n");
    }
  ;

else_clause
  : ELSE LBRACE statement_list RBRACE
    {
      printf("else_clause -> else { statement_list }\n");
    }
  | /* epsilon */
    {
      printf("else_clause -> epsilon\n");
    }
  ;

while_statement
  : WHILE LPAREN condition RPAREN LBRACE statement_list RBRACE
    {
      printf("while_statement -> while ( condition ) { statement_list }\n");
    }
  ;

/* ---------- Condition ---------- */
condition
  : expression relation expression
    {
      printf("condition -> expression relation expression\n");
    }
  ;
relation
  : LT   { printf("relation -> <\n"); }
  | LE   { printf("relation -> <=\n"); }
  | EQ   { printf("relation -> ==\n"); }
  | NEQ   { printf("relation -> !=\n"); }
  | GE    { printf("relation -> >=\n"); }
  | GT    { printf("relation -> >\n"); }
  ;


/* ---------- Expressions ---------- */
expression: factor int_expression_rest
          ;

int_expression_rest: PLUS expression
                   | MINUS expression
                   | MULT expression
                   | DIV expression
                   | MOD expression
                   | /* epsilon */
                   ;

factor: INT_CONST        { $$ = $1; }
      | IDENTIFIER       { $$ = 0; }  // Placeholder for identifiers
      | CHAR_CONST       { $$ = $1; }
      | STRING_CONST     { $$ = 0; }  // Placeholder for string literals
      ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error on line %d: %s\n", yylineno, s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            perror(argv[1]);
            return 1;
        }
        yyin = f;    
}
    yyparse();
    return 0;
}
