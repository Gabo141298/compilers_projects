#include "parse/driver.hh"

#include <iostream>
#include <string>

#include "parse/node.h"
#include "parse/symbol_table.hh"

extern SNode::Program* programBlock;
extern SymbolTable symbolTable;

int main(int argc, char** argv)
{
    parse::Driver driver;
    if(argc < 2)
    {
    	std::cout << "Ponga el archivo, no haga el ridi" << std::endl;
    	return 1;
    }
    std::string filename(argv[1]);
    driver.parse_file(filename);

    programBlock->print();

    programBlock->createSymbolTable(symbolTable);

    symbolTable.print();

    return 0;
}
