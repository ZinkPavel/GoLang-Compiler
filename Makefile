All: clear bin/main # bin/test

FLAGS = g++ -Wall -Werror -std=c++17
OBJ = $(TREE) $(PARSER) $(COMPILER) build/main.o $(TESTS)

TREE = build/Tree/Tree.o build/Tree/Node.o
PARSER = build/Parser/Expression.o build/Parser/Parser.o
COMPILER = build/Compiler/Token.o build/Compiler/Compiler.o
TESTS = build/Tests/TestsParser.o build/Tests/TestsLexer.o build/Tests/TestController.o build/Tests/TestRunner.o

bin/main: $(OBJ)
	$(FLAGS) $(OBJ) -o bin/main

# TREE

build/Tree/Tree.o: src/Tree/Tree.cpp
	$(FLAGS) -c src/Tree/Tree.cpp -o build/Tree/Tree.o

build/Tree/Node.o: src/Tree/Node.cpp
	$(FLAGS) -c src/Tree/Node.cpp -o build/Tree/Node.o

# PARSER

build/Parser/Expression.o: src/Parser/Expression.cpp
	$(FLAGS) -c src/Parser/Expression.cpp -o build/Parser/Expression.o

build/Parser/Parser.o: src/Parser/Parser.cpp
	$(FLAGS) -c src/Parser/Parser.cpp -o build/Parser/Parser.o

# COMPILER

build/Compiler/Token.o: src/Compiler/Token.cpp
	$(FLAGS) -c src/Compiler/Token.cpp -o build/Compiler/Token.o

build/Compiler/Compiler.o: src/Compiler/Compiler.cpp
	$(FLAGS) -c src/Compiler/Compiler.cpp -o build/Compiler/Compiler.o

# MAIN

build/main.o: src/main.cpp
	$(FLAGS) -c src/main.cpp -o build/main.o

# TESTS

build/Tests/TestsParser.o: src/Tests/TestsParser.cpp
	$(FLAGS) -c src/Tests/TestsParser.cpp -o build/Tests/TestsParser.o

build/Tests/TestsLexer.o: src/Tests/TestsLexer.cpp
	$(FLAGS) -c src/Tests/TestsLexer.cpp -o build/Tests/TestsLexer.o

build/Tests/TestController.o: src/Tests/TestController.cpp
	$(FLAGS) -c src/Tests/TestController.cpp -o build/Tests/TestController.o

build/Tests/TestRunner.o: src/Tests/TestRunner.cpp
	$(FLAGS) -c src/Tests/TestRunner.cpp -o build/Tests/TestRunner.o
	
# clear:
# 	rm -rf build/Tree/*.o build/Parser/*.o build/Compiler/*.o build/Tests/*.o bin/* 

clear:
	rm -rf build/Parser/*.o build/Tests/*.o bin/* 