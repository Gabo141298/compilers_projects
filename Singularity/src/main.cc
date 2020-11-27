#include "parse/driver.hh"

#include <iostream>
#include <string>

#include "exceptions/exceptions.hh"
#include "node/node_headers.hh"
#include "parse/symbol_table.hh"
#include "parse/codegen.hh"

extern SNode::Program* programBlock;
extern SymbolTable symbolTable;

int main(int argc, char** argv)
{
    parse::Driver driver;
    if(argc < 2)
    {
    	std::cout << "Please specify the file with the source code" << std::endl;
    	return 1;
    }
    std::string filename(argv[1]);
    driver.parse_file(filename);

    // programBlock->print();

    try
    {
        programBlock->createSymbolTable(symbolTable);
        // symbolTable.print();
    }
    catch(SingularityException exception)
    {
        handleException(exception);
    }

    SNode::CodeGenContext context;

    if(argc > 2)
        context.generateCode(*programBlock, argv[2]);
    else
        context.generateCode(*programBlock);
    
    return 0;
}
