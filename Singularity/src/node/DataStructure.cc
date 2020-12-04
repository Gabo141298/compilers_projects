#include "DataStructure.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* List::codeGen(CodeGenContext& context)
{
    llvm::Type* elementType = context.builder.getInt64Ty();

    auto layoutAllocSize = context.dataLayout.getTypeAllocSize(elementType);

    auto elementSize = context.builder.getInt64(layoutAllocSize);
    auto arraySize = context.builder.getInt64(10);
    auto allocSize = context.builder.CreateMul(elementSize, arraySize);

    std::vector<llvm::Value*> mallocArgs;

    mallocArgs.push_back(allocSize);

    return context.builder.CreateCall(context.module->getFunction("malloc"), mallocArgs);
}

void List::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "List" << std::endl;
}

llvm::Value* Matrix::codeGen(CodeGenContext&) { return nullptr; }
void Matrix::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Matrix: " << std::endl;

    printTabs(tabs + 1);
    std::cout << "Row:" << std::endl;
    row->print(tabs + 1);

    printTabs(tabs + 1);
    std::cout << "Col:" << std::endl;
    col->print(tabs + 1);
}

}