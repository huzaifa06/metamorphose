# Metamorphose
My own compiler and interpreter, that translates code written in a toy programming language to machine understandable code and interprets it. 

- scanner.l - Flex code, scans the tokens. 
- parser.y - Written in Bison, describes the CFG of the grammar and checks whether the statements are syntactically correct. 
- ast.c - Creates nodes in the AST. 
- ast.h - Function definitions and declarations. 
- interpreter.cpp - Interprets the AST, that is, computes the nodes in the AST. 
- Interpreter.h - Function definitions and declarations. 
- codegen.cpp
- Codegen.h
