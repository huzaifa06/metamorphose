#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>

using namespace std;

#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

Function *createFunc(IRBuilder<> &, std::string);
BasicBlock *createBB(Function *, std::string);
GlobalVariable *createGlob(IRBuilder<> &, std::string);
Value *createArith(IRBuilder<> &, Value *, Value *);
AllocaInst *CreateEntryBlockAlloca(Function *, string , string ) ;
void setFuncArgs(Function *, std::vector<std::string>);

extern Module *TheModule;
extern IRBuilder <> Builder;
extern std::vector<std::string> FunArgs;
extern LLVMContext Context;

extern Value* Codegen(struct ASTNode *root);