#include "parse/driver.hh"

#include <iostream>
#include <string>

#include "node.h"
extern SNode::Block* programBlock;

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

    std::cout << programBlock << std::endl;

    return 0;
}
