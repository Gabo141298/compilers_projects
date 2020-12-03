#include "Read.hh"

#include "node.hh"
#include "llvm/IR/Instructions.h"

namespace SNode
{

llvm::Value* Read::codeGen(CodeGenContext& context)
{
    // Gets the function
    llvm::Function *theScanf = context.module->getFunction("scanf");


    // Format
    llvm::Value *scanfFormat = SNode::createString(context, "%s");

    auto charType = llvm::IntegerType::get(context.context, 8);
    std::vector<llvm::Constant *> chars(256);
    for(unsigned int i = 0; i < 256; i++) {
        chars[i] = llvm::ConstantInt::get(charType, '\0');
    }

    auto stringType = llvm::ArrayType::get(charType, chars.size());
    auto globalDeclaration = (llvm::GlobalVariable*) context.module->getOrInsertGlobal("", stringType);
    globalDeclaration->setInitializer(llvm::ConstantArray::get(stringType, chars));
    globalDeclaration->setConstant(false);
    globalDeclaration->setLinkage(llvm::GlobalValue::LinkageTypes::PrivateLinkage);
    globalDeclaration->setUnnamedAddr (llvm::GlobalValue::UnnamedAddr::Global);



    //4. Return a cast to an i8*
    auto buffer = llvm::ConstantExpr::getBitCast(globalDeclaration, charType->getPointerTo());

    // Vector with args
    std::vector<llvm::Value *> scanfArgs = {scanfFormat, buffer};


    // Build the call
    llvm::Value* response = context.builder.CreateCall(theScanf, scanfArgs);

    context.insertVar(this->identifier.name, buffer);

    return buffer;

}
void Read::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Read: " << std::endl;
    identifier.print(tabs + 1);
}
void Read::createSymbolTable(SymbolTable& table, std::string, size_t*) const
{
    // Can't infer datatype that is read from an input.
    table.insertToCurrentSubtable(identifier.name, Datatype::UNKNOWN);
}

}
