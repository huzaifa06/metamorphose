%{
#include <stdio.h>
#include "ast.h"
#include "Interpreter.h"
#include "Codegen.h"
#define YYSTYPE struct ASTNode *

extern int yylex();
extern int yyparse();
extern FILE *yyin;
void yyerror(char *s);
using namespace llvm;
void evaluate(what_it_returns temp);
%}

%{
// Defining Tokens, which the parser obtains from the scanner
// These block of statements have C code inside of them! 
%}

%token NUMBER IDD IDD2
%token IF ELSE FI

%token INT_TYPE CHAR_TYPE BOOL_TYPE UINT_TYPE STRING_TYPE  

%token SEMICOLON
%token EQUAL_TO
%token DOLLAR

%token UNARY_OP AND_OP OR_OP ADD_OP SUB_OP MUL_OP DIV_OP MOD_OP
%token EQ_COMP LE_COMP GE_COMP LT_COMP GT_COMP


%token FOR LEFT_BRACKET RIGHT_BRACKET FOR_SEPARATE IN
%token WHILE

%token INPUT
%token OUTPUT
%token COMMA
%token BREAK
%token FUNC RETURN
%%

/* Now, we define the Context Free Grammar of our language
After every substitution rule, the stuff inside the brackets: { } is C code.  
Any code written in this language must end with a '$' symbol. 
*/

Goal2: DOLLAR {cout<<"Code Accepted :') "<<endl; return(0); }
	 | Goal DOLLAR {$$ = $1; cout<<"Code Accepted :') "<<endl; return(0);}

Goal: 
	  | Goal control_flow_statement {what_it_returns temp = interpret($2); printPostFix($2); }
	  | Goal function_definition { $$ = $2; what_it_returns temp = interpret($2); }
	  | Goal Expr {$$ = $2; what_it_returns temp = interpret($2); printPostFix($2); }

// goal :(goal) expr | decl| conflow | io | func
Exprs: Expr Exprs { $$ = getASTNodeExpression($1, $2); }
     | Expr { $$ = $1; }
     | control_flow_statement {$$ = $1; }
     // | control_flow_statement Exprs 
     | BREAK { $$ = yylval; }
     | RETURN variable SEMICOLON { $$ = getASTNodeReturn($2); }
     ;

/* An Expression would comprise of multiple statements. 
The statements can be of various types, as given in the CFG rule below.
*/

// { $$ = $1; what_it_returns temp = interpret($1); evaluate(temp);}
// { $$ = $1; what_it_returns temp = interpret($1);  }
Expr: assignment { $$ = $1; }
	| declaration { $$ = $1; 
							GlobalVariable *gVar = createGlob(Builder, "x");
	 						Function *fooFunc = createFunc(Builder, "main");
							setFuncArgs(fooFunc, FunArgs);
							BasicBlock *entry = createBB(fooFunc, "entry");
							Builder.SetInsertPoint(entry);
							Builder.CreateRet(Codegen($1)); 
							TheModule->print(errs(), nullptr); 
				  }   
	| io_statement { $$ = $1; }
	| function_call {$$ = $1; }
	| operation { $$ = $1;  
							GlobalVariable *gVar = createGlob(Builder, "x");
	 						Function *fooFunc = createFunc(Builder, "main");
							setFuncArgs(fooFunc, FunArgs);
							BasicBlock *entry = createBB(fooFunc, "entry");
							Builder.SetInsertPoint(entry);
							Builder.CreateRet(Codegen($1)); 
							TheModule->print(errs(), nullptr); 
				}
	//| control_flow_statement {$$ = $1;}
	;

control_flow_statement: for_statement {$$ = $1; }
					  | while_statement
					  | if_statement {$$ = $1;  }
					  | if_else_statement {$$ =$1; }

io_statement: print_statement {$$ = $1; }
			| scan_statement {$$ = $1; }

/* Defining declaration statements
eg. int a;
and there is provision for multiple declarations too! eg. int a,b = 5; 
*/

declaration: INT_TYPE variable SEMICOLON { $$ = getASTNodeDeclaration(INTS, $2);}
		   | CHAR_TYPE variable SEMICOLON { $$ = getASTNodeDeclaration(CHARS, $2); }
		   | UINT_TYPE variable SEMICOLON { $$ = getASTNodeDeclaration(UINTS, $2); }
		   | BOOL_TYPE variable SEMICOLON { $$ = getASTNodeDeclaration(BOOLS, $2); }
		   | STRING_TYPE variable SEMICOLON { $$ = getASTNodeDeclaration(STRINGS, $2); }
		   | INT_TYPE variable LEFT_BRACKET Term RIGHT_BRACKET 
		   	 SEMICOLON { $$ = getASTNodeArrayDeclaration($2, $4); }
		   ;


/* Defining assignment statements
eg. a = 5;
*/

assignment: variable EQUAL_TO operation SEMICOLON { $$ = getASTNodeAssignment($1, $3); }
		  | variable LEFT_BRACKET operation RIGHT_BRACKET 
		  	EQUAL_TO operation SEMICOLON { $$ = getASTNodeArrayAssignment($1, $3, $6); }
		  | variable EQUAL_TO function_call { $$ = getASTNodeAssignment($1, $3); }
		  ;

operation: operation AND_OP Term { $$ = getASTNodeBinaryOp($1, $3, AND);}
		 | operation OR_OP Term  { $$ = getASTNodeBinaryOp($1, $3, OR);}
		 | operation ADD_OP Term { $$ = getASTNodeBinaryOp($1, $3, ADD);}
		 | operation SUB_OP Term { $$ = getASTNodeBinaryOp($1, $3, SUB);}
		 | operation MUL_OP Term { $$ = getASTNodeBinaryOp($1, $3, MUL);}
		 | operation DIV_OP Term { $$ = getASTNodeBinaryOp($1, $3, DIV);}
		 | operation MOD_OP Term { $$ = getASTNodeBinaryOp($1, $3, MOD);}
		 | Term 				 { $$ = $1; }
		 | UNARY_OP Term 
		 ;

/* Defining IO statements
eg. cout{a}; cin{n, k};
*/

print_statement: OUTPUT '(' variable ')' SEMICOLON { $$ = getASTNodePrint($3); }
			   | OUTPUT LEFT_BRACKET prints_possibilities RIGHT_BRACKET SEMICOLON { $$ = $3; }

scan_statement:  INPUT '(' variable ')' SEMICOLON { $$ = getASTNodeScan($3); }

prints_possibilities: prints_possibilities variable {$$ = getASTNodePrintPossibilities($1, $2); }
					| variable {$$ = getASTNodePrint($1);}

/* Defining Function declarations and calls
eg. func add(a, b) { return a+b; }
	add(2,3);
*/

function_definition: FUNC variable '(' multiple_ids ')' '{' Exprs '}' {$$ = getASTNodeFunctionDef($2, $7);}
function_call: variable '(' multiple_args ')' SEMICOLON {$$ = getASTNodeFunctionCall($1, $3);}

multiple_ids: variable COMMA multiple_ids 
			| variable {$$ = $1;}
			;

multiple_args: Term COMMA Term {$$ = getASTNodeArgs($1, $3); }
			| Term {$$ = $1;}
			;

/* Defining Control Flow statements
eg. if[a<5] { } else { }
	while[a<5]
	for var in [1:3:1] { } 
*/

condition: operation EQ_COMP operation { $$ = getASTNodeCondition($1, $3, EQ);}
		 | operation LE_COMP operation { $$ = getASTNodeCondition($1, $3, LE);}
		 | operation GE_COMP operation { $$ = getASTNodeCondition($1, $3, GE);}
		 | operation LT_COMP operation { $$ = getASTNodeCondition($1, $3, LT);}
		 | operation GT_COMP operation { $$ = getASTNodeCondition($1, $3, GT);}

for_statement: FOR variable IN for_loop '{' Exprs '}' {$$ = getASTNodeForStatement($2, $4, $6); }
for_loop: LEFT_BRACKET Term FOR_SEPARATE Term FOR_SEPARATE Term RIGHT_BRACKET {$$=getASTNodeForLoop($2, $4, $6);}
			   
while_statement: WHILE LEFT_BRACKET condition RIGHT_BRACKET '{' Exprs '}' 

if_statement: IF '(' condition ')' '{' Exprs '}' FI {$$ = getASTNodeIfStatement($3, $6); }
if_else_statement: IF '(' condition ')' '{' Exprs '}' ELSE '{' Exprs '}' FI {$$ = getASTNodeIfElseStatement($3, $6, $10);}

Term: NUMBER { $$ = yylval; }
	| variable { $$ = $1; }
	| variable LEFT_BRACKET operation RIGHT_BRACKET { $$ = getASTNodeArrayVariable($1, $3); }
	;

// function_variable: variable {$$ = getASTNodeFunctionVariable($1); }
variable: IDD {$$ = yylval;}
%%

void yyerror(char *s)
{
    fprintf(stderr, "error: %s\n", s);
}

void evaluate(what_it_returns obj)
{
	switch (obj.return_type)
	{
		case INT_RET: 
			cout<<obj.int_value<<endl;
			break;
		case BOOL_RET: 
			cout<<obj.bool_value<<endl;
			break;
		case ARRAY_RET:
			for(int i=0; i<5; i++ )
				cout<<obj.array_value.arr[i]<<" ";
			cout<<endl;
			break;
		case MESSAGE_RET:
			cout<<obj.message;
	}

}

int main(int argc, char **argv)
{
    yyparse();
    // printf("Parsing Over\n")
    return 0;
}
