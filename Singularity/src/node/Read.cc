#include "Read.hh"

#include "node.hh"
#include "VariableAssignment.hh"
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

    //Creates an empty string to use as a buffer
    auto stringType = llvm::ArrayType::get(charType, chars.size());
    auto globalDeclaration = (llvm::GlobalVariable*) context.module->getOrInsertGlobal("", stringType);
    globalDeclaration->setInitializer(llvm::ConstantArray::get(stringType, chars));
    globalDeclaration->setConstant(false);
    globalDeclaration->setLinkage(llvm::GlobalValue::LinkageTypes::PrivateLinkage);
    globalDeclaration->setUnnamedAddr (llvm::GlobalValue::UnnamedAddr::Global);



    //4. Return a cast to an i8*
    llvm::Constant* buffer = llvm::ConstantExpr::getBitCast(globalDeclaration, charType->getPointerTo());

    // Vector with args
    std::vector<llvm::Value *> scanfArgs = {scanfFormat, buffer};


    // Build the call to scanf
    context.builder.CreateCall(theScanf, scanfArgs);

    VariableAssignment::assignVariable(context, this->identifier.name, buffer);

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

llvm::Value *Read::getConvertedValue(CodeGenContext& context, llvm::Value *buffer)
{
    // Get nullptr to use as a parameter
    llvm::Value* nullPointer = llvm::ConstantExpr::getBitCast( context.builder.getInt64(0), context.builder.getInt8PtrTy());
//    llvm::Value* intVal = context.builder.getInt64(0);
    // Build parameters for strtol
    std::vector<llvm::Value*> args;
    args.push_back(buffer);
    args.push_back(nullPointer);
    args.push_back(context.builder.getInt32(10));

    //Call strtol
    llvm::Value* intVal =  context.builder.CreateCall(context.module->getFunction("strtol"), args);

    // Check if the read value is an integer
    llvm::Value* cond = context.builder.CreateICmpNE(intVal, context.builder.getInt64(0));
    llvm::BasicBlock* thenBlock = llvm::BasicBlock::Create(context.context, "then", context.dummy);
    context.insertFunctionBlock(thenBlock);
    llvm::BasicBlock* merge = llvm::BasicBlock::Create(context.context, "merge", context.dummy);
    context.insertFunctionBlock(merge);



    // If it is an integer,
    llvm::BasicBlock* elseBlock = llvm::BasicBlock::Create(context.context, "else", context.dummy);
    context.insertFunctionBlock(elseBlock);
    context.builder.CreateCondBr(cond, thenBlock, elseBlock);
    context.builder.SetInsertPoint(elseBlock);
    VariableAssignment::assignVariable(context, this->identifier.name, buffer);
    context.builder.CreateBr(merge);

    context.builder.SetInsertPoint(thenBlock);
    VariableAssignment::assignVariable(context, this->identifier.name, intVal);

    context.builder.CreateBr(merge);

    context.builder.SetInsertPoint(merge);
    context.replaceBlock(merge);
}

}
