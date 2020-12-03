#include "DataStructure.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* List::codeGen(CodeGenContext& context)
{
    llvm::Type* elementType = context.builder.getInt8PtrTy();
    llvm::Type* int32type = context.builder.getInt32Ty();

    auto layoutAllocSize = context.dataLayout.getTypeAllocSize(elementType);
    std::cout << layoutAllocSize << std::endl;

    auto elementSize = llvm::ConstantInt::get(int32type, layoutAllocSize);
    auto arraySize = llvm::ConstantInt::get(int32type, 1);
    auto allocSize = llvm::ConstantExpr::getMul(elementSize, arraySize);

    llvm::BasicBlock* block = context.builder.GetInsertBlock();
    auto elTyPtr = elementType->getPointerTo();

    // malloc:
    auto arr = llvm::CallInst::CreateMalloc(
        block, 
        elTyPtr, // T*
        elementType,                 // T
        allocSize,                   // sizeof(T) * 100
        arraySize,
        nullptr, 
        "");

    context.builder.Insert(arr);

    return arr;
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