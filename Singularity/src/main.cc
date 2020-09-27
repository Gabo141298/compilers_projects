#include "parse/driver.hh"

#include <iostream>
#include <string>

#include "parse/node.h"
extern SNode::Program* programBlock;

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

    /*std::cout << programBlock << ' ' << programBlock->functions.size() << std::endl;

    for(size_t curFunc = 0; curFunc < programBlock->functions.size(); ++curFunc)
    {
    	std::cout << "Función: " << programBlock->functions[curFunc]->id.name << std::endl;
    	for(size_t curStat = 0; curStat < programBlock->functions[curFunc]->block.body.statements.size(); ++curStat)
    	{
    		std::cout << &(programBlock->functions[curFunc]->block.body.statements[curStat]) << std::endl;
    	}
    }*/

    return 0;
}
