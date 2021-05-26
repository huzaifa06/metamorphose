typedef enum  astnodetype { BinaryOp, 
							INTLITERAL, 
							Assignment, 
							ArrayAssignment,
							ForLoop, 
							ForStatement,
							Condition, 
							identifier,
							declaration,
							expression, 
							arraydeclaration,
							arrayvariable,
							IfStatement,
							IfElseStatement,
							Print,
							Scan,
							PrintPossibilities,
							Break,
							Return,
							MultipleID,
							args,
							functiondef,
							functioncall} 
							ASTNodeType;

typedef enum  binaryoptype {ADD, SUB, MUL, DIV, AND, OR, MOD} BinaryOpType; 
typedef enum  condoptype {EQ, LE, GE, LT, GT} CondOpType; 
typedef enum  datatype {INTS, CHARS, UINTS, BOOLS, STRINGS, ARRAYS } DataType; 

extern struct ASTNode *getASTNodeBinaryOp(struct ASTNode *left, 
										  struct ASTNode *right, 
										  BinaryOpType opera);

extern struct ASTNode *getASTNodeAssignment(struct ASTNode *left, 
											struct ASTNode *right);

extern struct ASTNode *getASTNodeFunctionDef(struct ASTNode *left, 
											struct ASTNode *right);

extern struct ASTNode *getASTNodeFunctionCall(struct ASTNode *left, 
											struct ASTNode *right);

extern struct ASTNode *getASTNodeArrayAssignment(struct ASTNode *left, 
												 struct ASTNode *center,
												 struct ASTNode *right);

extern struct ASTNode *getASTNodeArrayVariable(struct ASTNode *left, 
											   struct ASTNode *right);

extern struct ASTNode *getASTNodeForLoop(struct ASTNode *start, 
										 struct ASTNode *end, 
										 struct ASTNode *increment);

extern struct ASTNode *getASTNodeForStatement(struct ASTNode *left, 
										 struct ASTNode *right, 
										 struct ASTNode *center);

extern struct ASTNode *getASTNodeIfStatement(struct ASTNode *left, 
										     struct ASTNode *right);

extern struct ASTNode *getASTNodeIfElseStatement(struct ASTNode *left, 
										 		struct ASTNode *center, 
										 		struct ASTNode *right);

extern struct ASTNode *getASTNodeCondition(struct ASTNode *left, 				
										   struct ASTNode *right, 
										   CondOpType opera);

extern struct ASTNode *getASTNodeDeclaration(DataType opera, 
											 struct ASTNode *right);

extern struct ASTNode *getASTNodeArrayDeclaration(struct ASTNode *left,
											 	  struct ASTNode *right);

extern struct ASTNode *getASTNodeExpression(struct ASTNode *left, 
											struct ASTNode *right);

extern struct ASTNode *getASTNodeMultipleID(struct ASTNode *left, 
											struct ASTNode *right);

extern struct ASTNode *getASTNodeArgs(struct ASTNode *left, 
											struct ASTNode *right);

extern struct ASTNode *getASTNodePrintPossibilities(struct ASTNode *left, 
													struct ASTNode *right);

extern struct ASTNode *getASTNodeIntLiteral(int litval);
extern struct ASTNode *getASTNodeID(char* str);
extern struct ASTNode *getASTNodeBreak(char* str);
extern struct ASTNode *getASTNodeReturn(struct ASTNode *root);
extern struct ASTNode *getASTNodePrint(struct ASTNode *root);
extern struct ASTNode *getASTNodeScan(struct ASTNode *root);
//extern struct ASTNode *getASTNodeTernaryOp(struct ASTNode *first, struct ASTNode *second, struct ASTNode *third);

extern void printPostFix(struct ASTNode *root);

struct ASTNode {
	ASTNodeType nodetype;

	union {
		
		//binary operation
		struct 
		{
			BinaryOpType op; 
			struct ASTNode *left;
			struct ASTNode *right; 
		} binarynode;

		//condition operation
		struct 
		{
			CondOpType op; 
			struct ASTNode *left;
			struct ASTNode *right; 
		} condition_node;

		//declaration
		struct 
		{
			DataType op; 
			struct ASTNode *right; 
		} declaration_node;

		//array declaration
		struct 
		{
			struct ASTNode *left; 
			struct ASTNode *right; 
		} arraydeclaration_node;

		struct 
		{
			struct ASTNode *left; 
			struct ASTNode *right; 
		} functiondef_node;

		struct 
		{
			struct ASTNode *left; 
			struct ASTNode *right; 
		} functioncall_node;

		//array variable
		struct 
		{
			struct ASTNode *left; 
			struct ASTNode *right; 
		} arrayvariable_node;

		//assignment operation
		struct
		{
			struct ASTNode *left;
			struct ASTNode *right;
		} assignment_node;

		//array assignment operation
		struct
		{
			struct ASTNode *left;
			struct ASTNode *center;
			struct ASTNode *right;
		} arrayassignment_node;

		//for loop parameters
		struct
		{
			struct ASTNode *start;
			struct ASTNode *end;
			struct ASTNode *increment;
		} forloop_node;

		//for loop statement
		struct
		{
			struct ASTNode *left;
			struct ASTNode *center;
			struct ASTNode *right;
		} forstatement_node;

		//if statement
		struct
		{
			struct ASTNode *left;
			struct ASTNode *right;
		} ifstatement_node;

		//if else
		struct
		{
			struct ASTNode *left;
			struct ASTNode *center;
			struct ASTNode *right;
		} ifelse_node;

		//expression
		struct 
		{
			struct ASTNode *left;
			struct ASTNode *right; 
		} expression_node;

		struct 
		{
			struct ASTNode *left;
			struct ASTNode *right; 
		} printpossibilities_node;

		//multiple id
		struct
		{
			struct ASTNode *left;
			struct ASTNode *right;
		} multipleid_node;

		//args
		struct
		{
			struct ASTNode *left;
			struct ASTNode *right;
		} args_node;

		//numbers
		int litval;

		char* identifier_node;
		char* break_node;
		// char* return_node;

		struct 
		{
			struct ASTNode *left;
		} return_node;

		struct 
		{
			struct ASTNode *left;
		} print_node;

		struct 
		{
			struct ASTNode *left;
		} scan_node;
	};

};

