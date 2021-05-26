#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

struct ASTNode *getASTNodeForLoop(struct ASTNode *start, struct ASTNode *end, struct ASTNode *increment)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = ForLoop;

	node->forloop_node.start = start;
	node->forloop_node.end = end;
	node->forloop_node.increment = increment;

	return node;
}

struct ASTNode *getASTNodeForStatement(struct ASTNode *left, struct ASTNode *center, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = ForStatement;

	node->forstatement_node.left = left;
	node->forstatement_node.center = center;
	node->forstatement_node.right = right;

	return node;
}

struct ASTNode *getASTNodeIfStatement(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = IfStatement;

	node->ifstatement_node.left = left;
	node->ifstatement_node.right = right;

	return node;
}


struct ASTNode *getASTNodeIfElseStatement(struct ASTNode *left, struct ASTNode *center, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = IfElseStatement;;

	node->ifelse_node.left = left;
	node->ifelse_node.center = center;
	node->ifelse_node.right = right;

	return node;
}

struct ASTNode *getASTNodeAssignment(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Assignment;

	node->assignment_node.left = left;
	node->assignment_node.right = right;

	return node;
}

struct ASTNode *getASTNodeArrayAssignment(struct ASTNode *left, struct ASTNode *center, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = ArrayAssignment;

	node->arrayassignment_node.left = left;
	node->arrayassignment_node.center = center;
	node->arrayassignment_node.right = right;

	return node;
}

struct ASTNode *getASTNodeExpression(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = expression;

	node->expression_node.left = left;
	node->expression_node.right = right;
	return node;
}

struct ASTNode *getASTNodeFunctionDef(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = functiondef;

	node->functiondef_node.left = left;
	node->functiondef_node.right = right;
	return node;
}

struct ASTNode *getASTNodeFunctionCall(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = functioncall;

	node->functioncall_node.left = left;
	node->functioncall_node.right = right;
	return node;
}

struct ASTNode *getASTNodeArgs(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = args;

	node->args_node.left = left;
	node->args_node.right = right;
	return node;
}

struct ASTNode *getASTNodePrintPossibilities(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = PrintPossibilities;

	node->expression_node.left = left;
	node->expression_node.right = right;
	return node;
}

struct ASTNode *getASTNodeBinaryOp(struct ASTNode *left, struct ASTNode *right, BinaryOpType opera)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = BinaryOp;

	node->binarynode.left = left;
	node->binarynode.right = right;
	node->binarynode.op = opera;

	return node;
}

struct ASTNode *getASTNodeCondition(struct ASTNode *left, struct ASTNode *right, CondOpType opera)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Condition;

	node->condition_node.left = left;
	node->condition_node.right = right;
	node->condition_node.op = opera;

	return node;
}

struct ASTNode *getASTNodeDeclaration(DataType opera, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = declaration;

	node->declaration_node.op = opera;
	node->declaration_node.right = right;

	return node;
}

struct ASTNode *getASTNodeArrayDeclaration(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = arraydeclaration;

	node->arraydeclaration_node.left = left;
	node->arraydeclaration_node.right = right;

	return node;
}

struct ASTNode *getASTNodeArrayVariable(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = arrayvariable;

	node->arrayvariable_node.left = left;
	node->arrayvariable_node.right = right;

	return node;
}


// struct ASTNode *getASTNodeTernaryOp(struct ASTNode *first, 
// 									struct ASTNode *second,
// 									struct ASTNode *third)
// {
// 	struct ASTNode *node; 

// 	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

// 	node->nodetype = TernaryOp;
// 	node->ternarynode.first = first;
// 	node->ternarynode.second = second;
// 	node->ternarynode.third = third;

// 	return node;
// }

struct ASTNode *getASTNodeIntLiteral(int litval)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = INTLITERAL;
	node->litval = litval;

	return node;
}

struct ASTNode *getASTNodeID(char* str)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = identifier;
	node->identifier_node = str;

	return node;
}

struct ASTNode *getASTNodeBreak(char* str)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Break;
	node->break_node = str;

	return node;
}

struct ASTNode *getASTNodePrint(struct ASTNode *root)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Print;
	node->print_node.left = root;

	return node;
}

struct ASTNode *getASTNodeScan(struct ASTNode *root)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Scan;
	node->scan_node.left = root;

	return node;
}

struct ASTNode *getASTNodeReturn(struct ASTNode *root)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Return;
	node->return_node.left = root;

	return node;
}

struct ASTNode *getASTNodeMultipleID(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = MultipleID;

	node->multipleid_node.left = left;
	node->multipleid_node.right = right;

	return node;
}

void printPostFix(struct ASTNode *root)
{
	switch (root->nodetype) 	
	{

		case BinaryOp:
			printf("Binary Operator Node: ");
			printPostFix(root->binarynode.left);
			printPostFix(root->binarynode.right);
			switch (root->binarynode.op) 
			{
				case ADD: printf("+ ");
						  break; 
				case SUB: printf("- ");
						  break;
				case MUL: printf("* ");
						  break;
				case DIV: printf("/ ");
						  break;
			}
			// printf("\n");
			break;
			// case TernaryOp: printPostFix(root->ternarynode.first);
			// 				printPostFix(root->ternarynode.second);
			// 				printPostFix(root->ternarynode.third);
			// 				printf("? ");
			// 				break;
		case INTLITERAL:
			printf("%d ", root->litval);
			break;
		
		case Assignment:
			printf("Assignment Node: ");
			printPostFix(root->assignment_node.left);
			printf(" equals_to ");
			printPostFix(root->assignment_node.right);
			printf("\n");
			break;
		
		case ArrayAssignment:
			printPostFix(root->arrayassignment_node.left);
			printPostFix(root->arrayassignment_node.center);
			printPostFix(root->arrayassignment_node.right);
			printf("\n");
			break;
		
		case ForLoop:
			printf("For Loop: ");	
			printPostFix(root->forloop_node.start);
			printPostFix(root->forloop_node.end);
			printPostFix(root->forloop_node.increment);
			printf("\n");
			break;
		
		case ForStatement:
			printf("For Statement: ");
			printPostFix(root->forstatement_node.left);
			printPostFix(root->forstatement_node.center);
			printPostFix(root->forstatement_node.right);
			break;
		
		case Condition:
			// printf("Condition Operation\n");
			printPostFix(root->condition_node.left);
			printPostFix(root->condition_node.right);
			switch (root->condition_node.op) 
			{
				case EQ: printf("== ");
						break; 
				case LE: printf("<= ");
						break;
				case GE: printf(">= ");
						break;
				case LT: printf("< ");
						break;
				case GT: printf("> ");
						break;
			}
			printf("\n");
			break;

		case identifier:
			printf("%s ", root->identifier_node);
			break;

		// case MultipleID:
		// 	printPostFix(root->multipleid_node.left);
		// 	printPostFix(root->multipleid_node.right);
		// 	break;
		
		case expression:
			// printf("For Loop\n");	
			printPostFix(root->expression_node.left);
			printPostFix(root->expression_node.right);
			printf("\n");
			break;
		
		case declaration:
			printf("Declaration Node: ");
			switch (root->declaration_node.op) 
			{
				case INTS: printf("(type) int, ");
						break; 
				case CHARS: printf("(type) char, ");
						break;
				case UINTS: printf("(type) uint, ");
						break;
				case BOOLS: printf("(type) bool, ");
						break;
				case STRINGS: printf("(type) string, ");
						break;
				case ARRAYS: printf("(type) array, ");
						break;
			}
			printf("(identifier): ");
			printPostFix(root->declaration_node.right);
			printf("\n");
			break;
		case arraydeclaration:
			printf("Array Declaration node: ");
			printf("(type) int, ");
			printf("(variable) ");
			printPostFix(root->arraydeclaration_node.left);
			printf(", (size) ");
			printPostFix(root->arraydeclaration_node.right);
			printf("\n");
			break;
		case functioncall:
			printf("Function Call: ");
			printPostFix(root->functioncall_node.left);
			printPostFix(root->functioncall_node.right);
			
}
};