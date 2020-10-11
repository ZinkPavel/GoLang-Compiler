All: bin/app

FLAGS = g++ -Wall -Werror -std=c++17
OBJ = build/main.o $(CODE_GENERATOR) $(SEMANTICS) $(TREE) $(PARSER) $(COMPILER) $(TESTS) $(TOOLS)

CODE_GENERATOR = build/CodeGenerate/CodeGenerator.o
SEMANTICS = build/Semantics/Block.o build/Semantics/Var.o build/Semantics/Semantics.o 
TREE = build/Parser/AST-Tree/ASTree.o build/Parser/AST-Tree/Node.o
PARSER = build/Parser/Expression.o build/Parser/Parser.o
COMPILER = build/Compiler/Token.o build/Compiler/Compiler.o
TESTS = build/Tests/TestsSemantics.o build/Tests/TestsParser.o build/Tests/TestsLexer.o build/Tests/TestController.o build/Tests/TestRunner.o
TOOLS = build/Tools/OperatorsRedefinition.o

# APPLICATION

bin/app: $(OBJ)
	$(FLAGS) $(OBJ) -o bin/app

# MAIN

build/main.o: src/main.cpp
	$(FLAGS) -c src/main.cpp -o build/main.o

# CODE_GENERATOR

build/CodeGenerate/CodeGenerator.o: src/CodeGenerate/CodeGenerator.cpp
	$(FLAGS) -c src/CodeGenerate/CodeGenerator.cpp -o build/CodeGenerate/CodeGenerator.o

# SEMANTICS

build/Semantics/Semantics.o: src/Semantics/Semantics.cpp
	$(FLAGS) -c src/Semantics/Semantics.cpp -o build/Semantics/Semantics.o

build/Semantics/Var.o: src/Semantics/Var.cpp
	$(FLAGS) -c src/Semantics/Var.cpp -o build/Semantics/Var.o

build/Semantics/Block.o: src/Semantics/Block.cpp
	$(FLAGS) -c src/Semantics/Block.cpp -o build/Semantics/Block.o

# TREE

build/Parser/AST-Tree/Node.o: src/Parser/AST-Tree/Node.cpp
	$(FLAGS) -c src/Parser/AST-Tree/Node.cpp -o build/Parser/AST-Tree/Node.o

build/Parser/AST-Tree/ASTree.o: src/Parser/AST-Tree/ASTree.cpp
	$(FLAGS) -c src/Parser/AST-Tree/ASTree.cpp -o build/Parser/AST-Tree/ASTree.o

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

# TESTS

build/Tests/TestsSemantics.o: src/Tests/TestsSemantics.cpp
	$(FLAGS) -c src/Tests/TestsSemantics.cpp -o build/Tests/TestsSemantics.o

build/Tests/TestsParser.o: src/Tests/TestsParser.cpp
	$(FLAGS) -c src/Tests/TestsParser.cpp -o build/Tests/TestsParser.o

build/Tests/TestsLexer.o: src/Tests/TestsLexer.cpp
	$(FLAGS) -c src/Tests/TestsLexer.cpp -o build/Tests/TestsLexer.o

build/Tests/TestController.o: src/Tests/TestController.cpp
	$(FLAGS) -c src/Tests/TestController.cpp -o build/Tests/TestController.o

build/Tests/TestRunner.o: src/Tests/TestRunner.cpp
	$(FLAGS) -c src/Tests/TestRunner.cpp -o build/Tests/TestRunner.o

# TOOLS

build/Tools/OperatorsRedefinition.o: src/Tools/OperatorsRedefinition.cpp
	$(FLAGS) -c src/Tools/OperatorsRedefinition.cpp -o build/Tools/OperatorsRedefinition.o

# OTHER

clear:
	rm -rf build/CodeGenerate/*.o build/Semantics/*.o build/Parser/AST-Tree/*.o build/Parser/*.o build/Compiler/*.o build/Tests/*.o build/Tools/*.o build/*.o bin/* output/*