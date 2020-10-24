#include "Block.hh"

#include "node.hh"
#include "node_headers.hh"
namespace SNode
{

llvm::Value* Block::codeGen(CodeGenContext&) { return nullptr; }
void Block::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Block: " << std::endl;
    
    printTabs(tabs + 1);
    std::cout << "Statements:" << std::endl;
    for(size_t index = 0; index < statements.size(); ++index)
        statements[index]->print(tabs + 1);
}
void Block::createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const
{
    for(auto itr = statements.begin(); itr != statements.end(); ++itr)
    {
        (*itr)->createSymbolTable(table, name, subtableCounter);
    }
}

bool hasRecursionInExpression(std::vector<std::string>& calls, std::string& name )
{
    bool hasRecursion = false;
    for(std::string foundName : calls)
    {
        if(foundName == name)
        {
            hasRecursion = true;
            break;
        }
    }
    return hasRecursion;
}

bool Block::hasInfiniteRecursion(std::string name)
{
    bool hasRecursion = false;
    bool hasCondition = false;
    for(auto itr = statements.begin(); itr != statements.end(); ++itr)
    {
        switch ((*itr)->getType())
        {
        case NodeTypes::While:
        case NodeTypes::If:
        case NodeTypes::WhileCounting:
            hasCondition = true;
            break;
        case NodeTypes::ExpressionStatement:
        {
            std::vector<std::string> calls = reinterpret_cast<ExpressionStatement*>((*itr))->expression.getFunctionCalls();
            hasRecursion = hasRecursionInExpression(calls, name) ? true : hasRecursion;
            break;
        }
        case NodeTypes::Answer:
        {
            std::vector<std::string> calls = reinterpret_cast<Answer*>((*itr))->returnExpression.getFunctionCalls();
            hasRecursion = hasRecursionInExpression(calls, name) ? true : hasRecursion;
            break;                        
        }
        case NodeTypes::Print:
        {
            std::vector<std::string> calls = reinterpret_cast<Print*>((*itr))->expression.getFunctionCalls();
            hasRecursion = hasRecursionInExpression(calls, name) ? true : hasRecursion;
            break;                        
        }
        case NodeTypes::VariableAssignment:
        {
            std::vector<std::string> calls = reinterpret_cast<VariableAssignment*>((*itr))->assignmentExpr->getFunctionCalls();
            hasRecursion = hasRecursionInExpression(calls, name) ? true : hasRecursion;
            break;                        
        }
        case NodeTypes::DataPositionAssignment:
        {
            std::vector<std::string> calls = reinterpret_cast<DataPositionAssignment*>((*itr))->expression.getFunctionCalls();
            hasRecursion = hasRecursionInExpression(calls, name) ? true : hasRecursion;
            break;                        
        }
        case NodeTypes::Block:
        {                
            hasRecursion = reinterpret_cast<Block*>((*itr))->hasInfiniteRecursion(name) ? true : hasRecursion;
        }
        default:
            break;
        }
    }

    // std::cout << hasRecursion << hasCondition << name << std::endl;
    return hasRecursion && !hasCondition;
}

}