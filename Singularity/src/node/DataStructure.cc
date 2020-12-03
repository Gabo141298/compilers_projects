#include "DataStructure.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* List::codeGen(CodeGenContext& context)
{
    llvm::Type* elementType = context.builder.getInt8PtrTy();

    auto layoutAllocSize = context.dataLayout.getTypeAllocSize(elementType);

    auto elementSize = context.builder.getInt64(layoutAllocSize);
    auto arraySize = context.builder.getInt64(10);
    auto allocSize = context.builder.CreateMul(elementSize, arraySize);

    std::vector<llvm::Value*> mallocArgs;

    mallocArgs.push_back(allocSize);

    return context.builder.CreateCall(context.module->getFunction("malloc"), mallocArgs);

    /*llvm::BasicBlock* block = context.builder.GetInsertBlock();
    auto elTyPtr = elementType->getPointerTo();

    // malloc:
    auto arr = llvm::CallInst::CreateMalloc(
        block, 
        elTyPtr, // T*
        elementType,                 // T
        elementSize,                   // sizeof(T) * 10
        arraySize,
        nullptr, 
        "arr");

    context.builder.Insert(arr);

    return arr;*/
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