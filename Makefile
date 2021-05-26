parser: scanner.l parser.y ast.h ast.c interpreter.cpp Interpreter.h codegen.cpp Codegen.h
	bison -d parser.y
	flex scanner.l
	g++ -std=c++11 -w -o metamorphose ast.c interpreter.cpp codegen.cpp parser.tab.c lex.yy.c -ll `llvm-config --cppflags --ldflags --libs core --system-libs`

clean:
	rm lex.yy.c parser.tab.c parser.tab.h metamorphose

