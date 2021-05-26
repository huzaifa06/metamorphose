%{
#define YYSTYPE struct ASTNode *
#include "ast.h"
#include "parser.tab.h"
extern int yylex();
int lineno = 0;
%}

%% 
\n				{ ++lineno; }
[ \t] 			;
"int" 			{return INT_TYPE;}
"char" 			{return CHAR_TYPE;}
"uint" 			{printf("encountered uint \n"); return UINT_TYPE;}
"bool" 			{return BOOL_TYPE;}
"string" 		{return STRING_TYPE;}

";" 			{return SEMICOLON;}
"="				{return EQUAL_TO;}

"and"			{ return AND_OP;}
"or"			{ return OR_OP;}
"not"			{ return UNARY_OP;}
"+"             { return ADD_OP;}
"-"				{ return SUB_OP;}
"*"				{ return MUL_OP;}
"/"				{ return DIV_OP;}
"%"				{ return MOD_OP;}

"for"			{ return FOR; }
"while"			{ return WHILE; }
"cout"			{ return OUTPUT; }
"cin"			{ return INPUT; }
"break"			{ yylval = getASTNodeBreak(strdup(yytext)); return BREAK; }
"if"			{ return IF; }
"fi"			{ return FI; }
"else"			{ return ELSE; }
"func"			{ return FUNC; }
"return"		{  return RETURN; }

":"			    { return FOR_SEPARATE;}
","				{ return COMMA;}
"["				{ return LEFT_BRACKET; }
"]"				{ return RIGHT_BRACKET; }	
"{"				{ return '{'; }
"}"				{ return '}'; }	
"("				{ return '('; }
")"				{ return ')'; }

"in"			{ return IN; }
"=="		 	{ return EQ_COMP; }
"<="		 	{ return LE_COMP; }
">="		 	{ return GE_COMP; }
"<"		 		{ return LT_COMP; }
">"		 		{ return GT_COMP; }

[a-zA-Z][a-zA-Z0-9]* 	{ yylval = getASTNodeID(strdup(yytext)); return IDD;}
[0-9][0-9]*				{ yylval = getASTNodeIntLiteral(atoi(yytext)); return NUMBER; }

[$]				{ return DOLLAR; }

.				{ printf("Line No %d: Unrecognized character '%c'\n", lineno + 1, yytext[0]);}
