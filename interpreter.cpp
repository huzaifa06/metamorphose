#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>

#include "ast.h"
#include "Interpreter.h"

using namespace std;

map<string, what_it_returns> symbol_table;
map<string, what_it_returns> symbol2_table;
map<string, functionss> function_table;

what_it_returns interpret(struct ASTNode *root)
{
	switch (root->nodetype) 
	{
		case expression:
			what_it_returns lol1, lol2;
			lol1 = interpret(root->expression_node.left); 
			lol2 = interpret(root->expression_node.right); 
			return lol2;
			break;

		case declaration:
			what_it_returns temp;
			temp.return_type = NOTHING_RET;
			temp.nothing_value = 0;

			symbol_table[root->declaration_node.right->identifier_node] = temp;
			
			return temp;
			break;

		case functiondef:
		{
			functionss funcobj;
			
			funcobj.returntype = "int";
			funcobj.block = root->functiondef_node.right;
			// cout<< root->functiondef_node.left->identifier_node;
			function_table[root->functiondef_node.left->identifier_node] = funcobj;

			temp.return_type = NOTHING_RET;
			temp.nothing_value = 0;
			return temp;
			break;
		}

		case functioncall:
		{
			functionss funcobj;
			string funcname;
			funcname = root->functioncall_node.left->identifier_node;
			if(function_table.find(funcname) == function_table.end())
			{
				cout<<"Function not declared :("<<endl;
				exit(0);
				break;
			}
			funcobj = function_table[funcname];
			lol1 = interpret(root->functioncall_node.right);
			lol2 = interpret(funcobj.block);
			return lol2;
			break;
		}

		case Return:
			what_it_returns return_obj;
			// cout<<"LOL"<<symbol_table[root->return_node.left->identifier_node].int_value<<endl;
			return_obj.int_value = symbol_table[root->return_node.left->identifier_node].int_value;
			return_obj.return_type = INT_RET;
			return return_obj;
			break;


		case args:
			lol1 = interpret(root->args_node.left);
			lol2 = interpret(root->args_node.right);
			symbol_table["funca"] = lol1;
			symbol_table["funcb"] = lol2;
			return lol1;
			break;

		case arraydeclaration:
			
			temp.return_type = ARRAY_RET;
			temp.array_value.no_of_elements = root->arraydeclaration_node.right->litval;

			symbol_table[root->arraydeclaration_node.left->identifier_node] = temp;
			
			return temp;
			break;

		case Assignment:

			// if(root->assignment_node.right->nodetype == functioncall)
			// {

			// }

			temp = interpret(root->assignment_node.right);
			
			//checking if variable is there in the symbol table
			if(symbol_table.find(root->assignment_node.left->identifier_node) == symbol_table.end())
			{
				cout<<"Variable not declared :("<<endl;
				exit(0);
				break;
			}
			symbol_table[root->assignment_node.left->identifier_node] = temp;
			return temp;
			break;

		case ArrayAssignment:

			temp = interpret(root->arrayassignment_node.right);
			//checking if array variable is there in the symbol table
			if(symbol_table.find(root->arrayassignment_node.left->identifier_node) == symbol_table.end())
			{
				cout<<"Variable not declared :("<<endl;
				exit(0);
				break;
			}

			char* arrayname;
			int newvalue;
			arrayname = root->arrayassignment_node.left->identifier_node;
			newvalue = temp.int_value;
			
			struct ASTNode *location;
			location = root->arrayassignment_node.center;
			temp = interpret(location);
			
			int locvalue;
			if(location->nodetype == INTLITERAL)
				locvalue = location->litval;
			else if(location->nodetype == identifier)
				locvalue = symbol_table[location->identifier_node].int_value; 
			else
				locvalue = temp.int_value;
			
			symbol_table[arrayname].array_value.arr[locvalue] = newvalue;
			return symbol_table[arrayname];
			break;

		case BinaryOp:
			what_it_returns a,b,final;
			a = interpret(root->binarynode.left);
			b = interpret(root->binarynode.right);
			switch (root->binarynode.op) 
			{
				case ADD: 	
					final.return_type = INT_RET;
					final.int_value = (a.int_value + b.int_value);
					return(final);
					break;

				case SUB: 	
					final.return_type = INT_RET;
					final.int_value = (a.int_value - b.int_value);
					return(final);
					break;

				case MUL: 	
					final.return_type = INT_RET;
					final.int_value = (a.int_value * b.int_value);
					return(final);
					break;

				case DIV: 	
					final.return_type = INT_RET;
					final.int_value = (a.int_value / b.int_value);
					return(final);
					break;

				case MOD:
					final.return_type = INT_RET;
					final.int_value = (a.int_value % b.int_value);
					return(final);
					break;


				case AND: 	
					final.return_type = INT_RET;
					final.int_value = (a.int_value & b.int_value);
					return(final);
					break;

			}
			break;

		case Condition:
			a = interpret(root->condition_node.left);
			b = interpret(root->condition_node.right);
			// cout<<"left value = "<< a.int_value;
			// cout<<endl;
			// cout<<"right value = "<< b.int_value;
			// cout<<endl;
			final.return_type = BOOL_RET;
			switch (root->condition_node.op) 
			{
				case EQ: 	
					final.return_type = BOOL_RET;
					if(a.int_value == b.int_value)
						final.bool_value = 1;
					else
						final.bool_value = 0;
					return(final);
					break;

				case LT: 	
					final.return_type = BOOL_RET;
					if(a.int_value < b.int_value)
						final.bool_value = 1;
					else
						final.bool_value = 0;
					return(final);
					break;

				case GT: 	
					final.return_type = BOOL_RET;
					if(a.int_value > b.int_value)
						final.bool_value = 1;
					else
						final.bool_value = 0;
					return(final);
					break;
			}
			break;
		
		case ForStatement:

			// checking if loop_variable is declared 
			temp = interpret(root->forstatement_node.left);

			char* loop_variable; 
			loop_variable = root->forstatement_node.left->identifier_node; // the loop variable 
			
			/* ------------------------------------------------------------------------------
			Interpreting the for loop boundary conditions
			Ideally, should've written another recursive function for this, but no time xD 
			---------------------------------------------------------------------------------*/
			int start, end, increment;
			location = root->forstatement_node.center->forloop_node.end;

			start = root->forstatement_node.center->forloop_node.start->litval;
			
			if(root->forstatement_node.center->forloop_node.end->nodetype == INTLITERAL)
				end = location->litval;
			else
				end = symbol_table[location->identifier_node].int_value; 
			increment = root->forstatement_node.center->forloop_node.increment->litval;

			temp.return_type = INT_RET;
			temp.int_value = start;
			symbol_table[loop_variable] = temp;

			while(symbol_table[loop_variable].int_value < end)
			{
				// cout<<"Iteration"<<endl;
				a = interpret(root->forstatement_node.right);
				if(a.return_type == BREAK_RET)
				{
					// cout<<"BREAKING"<<endl;
					break;
				}
				else
					// cout<<"GO ON"<<endl;
				symbol_table[loop_variable].int_value = symbol_table[loop_variable].int_value + increment; 
			}

			// cout<<"ANSWER: "<<a.int_value;
			return a;
			break;

		case Break:
			what_it_returns break_obj;
			break_obj.nothing_value = 0;
			break_obj.return_type = BREAK_RET;
			return break_obj;
			break;
			
		case IfStatement:
			what_it_returns temp_condition, temp_exprs;
			temp_condition = interpret(root->ifstatement_node.left);
			// cout<< " Condition Result "<< temp_condition.bool_value << endl;
			if(temp_condition.bool_value == (1==1))
			{
				// cout<<"BON JOVI"<<endl;
				temp_exprs = interpret(root->ifstatement_node.right);
				return temp_exprs;
			}
			else
			{
				// cout<<"ALOK"<<endl;
				what_it_returns tempnew;
				tempnew.return_type = MESSAGE_RET;
				tempnew.message = "if statement condition not satisfied";
				return tempnew;
			}
			break;

		case IfElseStatement:
			what_it_returns temp2_exprs;
			temp_condition = interpret(root->ifelse_node.left);
			// cout<< " Condition Result "<< temp_condition.bool_value << endl;
			if(temp_condition.bool_value == (1==1))
			{
				// cout<<"BON JOVI"<<endl;
				temp_exprs = interpret(root->ifelse_node.center);
				return temp_exprs;
			}
			else
			{
				temp2_exprs = interpret(root->ifelse_node.right);
				return temp2_exprs;
			}
			break;


		case INTLITERAL:
			what_it_returns obj;
			obj.return_type = INT_RET;
			obj.int_value = root->litval;
			return obj;
			break;

		case identifier:
			if(symbol_table.find(root->identifier_node) == symbol_table.end())
			{
				obj.return_type = PRINT_RET;
				obj.print_value = root->identifier_node;
				return obj;
				break;
			}
			obj.return_type = ID_RET;
			obj.int_value = symbol_table[root->identifier_node].int_value ;
			return obj;
			break;

		case MultipleID:
			a = interpret(root->multipleid_node.left);
			b = interpret(root->multipleid_node.right);
			return b; 
			break;

		case arrayvariable:
			
			arrayname = root->arrayvariable_node.left->identifier_node;
			location = root->arrayvariable_node.right;
			obj = interpret(location);
			if(symbol_table.find(arrayname) == symbol_table.end())
			{
				cout<<"Variable not declared :("<<endl;
				exit(0);
				break;
			}

			if(location->nodetype == INTLITERAL)
				locvalue = location->litval;
			else if(location->nodetype == identifier)
				locvalue = symbol_table[location->identifier_node].int_value; 
			else
				locvalue = obj.int_value; 

			obj.return_type = ARRAY_RET;
			obj.int_value = symbol_table[arrayname].array_value.arr[locvalue];
			return obj;
			break;

		case Print:
			// cout<<"Reached here";
			location = root->print_node.left;
			
			// if(location->nodetype == INTLITERAL)
			// 	locvalue = location->litval;
			// if(symbol_table.find(location->identifier_node) == symbol_table.end())
			// {
			// 	cout<<"Variable not declared"<<endl;
			// 	exit(0);
			// 	break;
			// }

			what_it_returns lol3;
			lol3 = interpret(location);
			if(lol3.return_type == PRINT_RET)
			{
				cout<<lol3.print_value<<" ";
				return lol3;
				break;
			}
			lol3 = symbol_table[location->identifier_node];
			if(lol3.return_type == ARRAY_RET)
			{
				for(int i=0; i<lol3.array_value.no_of_elements; i++ )
					cout<<lol3.array_value.arr[i]<<" ";
				cout<<endl;
			}
			else if(lol3.return_type == INT_RET)
				cout<<lol3.int_value<<endl;
			else if(lol3.return_type == NOTHING_RET)
			{
				cout<<"variable has not been assigned any value yet"<<endl;
			}
			return lol3;
			break;

		case Scan:
			location = root->scan_node.left;
			int input;
			cin>>input;

			if(symbol_table.find(location->identifier_node) == symbol_table.end())
			{
				cout<<"Variable not declared :("<<endl;
				exit(0);
				break;
			}

			lol3.return_type = INT_RET;
			lol3.int_value = input;
			symbol_table[location->identifier_node] = lol3;
			return lol3;
			break;
		
		case PrintPossibilities:
			lol1 = interpret(root->printpossibilities_node.left);
			lol2 = interpret(root->printpossibilities_node.right);
			cout<<lol2.print_value<<endl;
			break;
	}
};

/* Printing the symbol table out
for(auto k:symbol_table)              
{
	cout<<k.first<< " ";
	cout<<k.second.int_value<<endl;
}
-------------------------------*/