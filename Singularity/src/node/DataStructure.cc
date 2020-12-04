#include "DataStructure.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* List::codeGen(CodeGenContext& context)
{
    llvm::Type* elementType = context.builder.getDoubleTy();

    auto layoutAllocSize = context.dataLayout.getTypeAllocSize(elementType);

    auto elementSize = context.builder.getInt64(layoutAllocSize);
    this->size = context.builder.getInt64(100);
    auto allocSize = context.builder.CreateMul(elementSize, size);

    std::vector<llvm::Value*> mallocArgs;

    mallocArgs.push_back(allocSize);

    return context.builder.CreateCall(context.module->getFunction("malloc"), mallocArgs);
}

void List::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "List" << std::endl;
}

llvm::Value* Matrix::codeGen(CodeGenContext& context)
{
    this->rowVal = this->row->codeGen(context);
    this->colVal = this->col->codeGen(context);

    llvm::Type* elementType = context.builder.getDoubleTy();
    auto layoutAllocSize = context.dataLayout.getTypeAllocSize(elementType);
    auto elementSize = context.builder.getInt64(layoutAllocSize);
    auto allocSize = context.builder.CreateMul(elementSize, rowVal);
    allocSize = context.builder.CreateMul(allocSize, colVal);
    
    std::vector<llvm::Value*> mallocArgs;

    mallocArgs.push_back(allocSize);

    return context.builder.CreateCall(context.module->getFunction("malloc"), mallocArgs);
}

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