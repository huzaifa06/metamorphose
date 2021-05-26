#include <bits/stdc++.h>
using namespace std;

typedef enum returnvaluetype { INT_RET, BOOL_RET, ID_RET, ARRAY_RET, MESSAGE_RET, NOTHING_RET, PRINT_RET, BREAK_RET, FUNC_RET }ReturnValueType; 

typedef struct Return_Entity
{
	ReturnValueType return_type;
	union
	{
		int int_value;
		bool bool_value;
		char* id_value;
		char* print_value;
		int nothing_value;
		struct
		{
			int arr[100];
			int no_of_elements;
		} array_value;
		char* message;
		int funca;
		int funcb;
		
	};

} what_it_returns;

//To keep track of all functions
typedef struct Functions
{
	string returntype;
	// std::vector<string> argument_names; 
	// std::vector<string> argument_types;
	struct ASTNode* block;

} functionss;

extern what_it_returns interpret(struct ASTNode *root);

extern void print_answer(what_it_returns var); 