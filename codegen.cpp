#include "Codegen.h"
#include "ast.h"
#include "Interpreter.h"

LLVMContext Context;
Module *TheModule = new Module("Metamorphose", Context); // Contains all functions and variables
IRBuilder<> Builder(Context); // helps to generate LLVM IR with helper functions
map <string, AllocaInst*>NamedValues; // keeps track of all the values defined in the current scope like a symbol table
std::vector<std::string> FunArgs;

Function *createFunc(IRBuilder<> &Builder, std::string Name)
{
	std::vector<Type *> Integers(FunArgs.size(), Type::getInt32Ty(Context));
	FunctionType *funcType = llvm::FunctionType::get(Builder.getInt32Ty(),false);
	Function *fooFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, Name, TheModule);
	return fooFunc;
}

void setFuncArgs(Function *fooFunc, std::vector<std::string> FunArgs) 
{
	unsigned Idx = 0;
	Function::arg_iterator AI, AE;
	for (AI = fooFunc->arg_begin(), AE = fooFunc->arg_end(); AI != AE;++AI, ++Idx)
	AI->setName(FunArgs[Idx]);
}

BasicBlock *createBB(Function *fooFunc, std::string Name) 
{
	return BasicBlock::Create(Context, Name, fooFunc);
}

GlobalVariable *createGlob(IRBuilder<> &Builder, std::string Name) 
{
	TheModule->getOrInsertGlobal(Name, Builder.getInt32Ty());
	GlobalVariable *gVar = TheModule->getNamedGlobal(Name);
	gVar->setLinkage(GlobalValue::CommonLinkage);
	gVar->setAlignment(4);
	return gVar;
}

Value *createArith(IRBuilder<> &Builder, Value *L, Value *R) 
{
	return Builder.CreateMul(L, R, "multmp");
}

AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, string VarName, string type) 
{
	
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    cout<<"reached here"<<endl;
    AllocaInst *alloca_instruction = nullptr;
    if (type == "int") 
    {

        alloca_instruction = TmpB.CreateAlloca(Type::getInt32Ty(Context), 0, VarName);
    } 
    else if (type == "boolean") 
    {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt1Ty(Context), 0, VarName);
    }
    return alloca_instruction;
}

Value *LogErrorV(const char *Str) 
{
  cout<<Str;
  return nullptr;
}

//Mine
Value *Codegen(struct ASTNode *root)
{
	switch (root->nodetype)
	{
		case INTLITERAL:
			int val;
			val = root->litval;
			return ConstantInt::get(Context, APInt(32, val));
			break;
		
		case BinaryOp:
			Value * a;
			Value * b;
			Value * v;
			a = Codegen(root->binarynode.left);
  			b = Codegen(root->binarynode.right);
  			if(!a || !b)
  			{
  				return nullptr;
  			}
  			v = nullptr;
  			switch (root->binarynode.op) 
  			{
  				case ADD:
  					// cout<<"Reached Add Codegen"<<endl;
  					v = Builder.CreateAdd(a, b, "addition");
  					// cout<<"DONE"<<endl;
  					return v;
  				case SUB: 
  					v = Builder.CreateSub(a, b, "subtraction");
  					return v;
  				case MUL:
  					v = Builder.CreateMul(a, b, "subtraction");
  					return v;
  					break;
  			}
  			break;

  		case Assignment:
  			cout<<"WOOHOO";
  			a = Codegen(root->binarynode.left);
  			b = Codegen(root->binarynode.right);
  			v = nullptr;
  			Builder.CreateStore(b, a);
  			return a;
  			break;

  		
  		case identifier:
  			v = NamedValues[root->identifier_node];
  			if (!v)
    			LogErrorV("Unknown variable name");
  			return v;
  			break;

  		case declaration:
			Function* the_func = Builder.GetInsertBlock()->getParent();
			Value* init_val = nullptr;
			AllocaInst* alloc = nullptr;
			
			string var;
			var = root->declaration_node.right->identifier_node;			
			
			init_val = ConstantInt::get(Context, APInt(32,0));
			alloc = CreateEntryBlockAlloca(the_func, var, "int");
			Builder.CreateStore(init_val, alloc);
			NamedValues[var] = alloc;
			// add_context(make_pair(var, alloc));

			return init_val;
			break;
	}

}









