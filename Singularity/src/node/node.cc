#include "ArithmeticOperation.hh"
#include "BooleanOperation.hh"
#include "ComparisonOperation.hh"
#include "node.hh"

std::ostream& SNode::operator<<(std::ostream& out, SNode::ArithmeticOperator value){
    const char* s = 0;
    switch(value){
        PROCESS_VAL(addition)
        PROCESS_VAL(substraction)
        PROCESS_VAL(multiplication)
        PROCESS_VAL(division)
        PROCESS_VAL(modulo)
    }

    return out << s;
}

std::ostream& SNode::operator<<(std::ostream& out, SNode::ComparisonOperator value){
    const char* s = 0;
    switch(value){
        PROCESS_VAL(leq)
        PROCESS_VAL(geq)
        PROCESS_VAL(greater)
        PROCESS_VAL(less)
        PROCESS_VAL(equals)
        PROCESS_VAL(isNot)
    }

    return out << s;
}

std::ostream& SNode::operator<<(std::ostream& out, SNode::BooleanOperator value){
    const char* s = 0;
    switch(value){
        PROCESS_VAL(bAnd)
        PROCESS_VAL(bOr)
        PROCESS_VAL(bXor)
    }

    return out << s;
}

SNode::Expression* SNode::createOperation(SNode::Expression& left, int op, SNode::Expression& right)
{
    if(SNode::OperationType::ARITHMETIC_OP <= op && op < SNode::OperationType::COMPARISON_OP)
        return new ArithmeticOperation(left, (SNode::ArithmeticOperator)op, right);
    else if(SNode::OperationType::COMPARISON_OP <= op && op < SNode::OperationType::BOOLEAN_OP)
        return new ComparisonOperation(left, (SNode::ComparisonOperator)op, right);
    else if(op >= SNode::OperationType::BOOLEAN_OP)
        return new BooleanOperation(left, (SNode::BooleanOperator)op, right);
    return nullptr;
}

std::vector<std::string> SNode::Expression::getFunctionCalls()
{
    return std::vector<std::string>();
}

llvm::Value* SNode::Integer::codeGen(CodeGenContext& context)
{
    // return llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.context), this->value);
    return context.builder.getInt64(this->value);
}

llvm::Value* SNode::Double::codeGen(CodeGenContext& context)
{
    return llvm::ConstantFP::get(llvm::Type::getDoubleTy(context.context), this->value);
    //return context.builder.getDouble(this->value);
}

// Tomado de https://stackoverflow.com/questions/51809274/llvm-defining-strings-and-arrays-via-c-api

llvm::Value* SNode::createString(CodeGenContext& context, std::string str)
{
    //0. Defs
    auto charType = llvm::IntegerType::get(context.context, 8);


    //1. Initialize chars vector
    std::vector<llvm::Constant *> chars(str.length());
    for(unsigned int i = 0; i < str.size(); i++) {
        chars[i] = llvm::ConstantInt::get(charType, str[i]);
    }

    //1b. add a zero terminator too
    chars.push_back(llvm::ConstantInt::get(charType, 0));


    //2. Initialize the string from the characters
    auto stringType = llvm::ArrayType::get(charType, chars.size());

    //3. Create the declaration statement
    auto globalDeclaration = (llvm::GlobalVariable*) context.module->getOrInsertGlobal(str + ".str", stringType);
    globalDeclaration->setInitializer(llvm::ConstantArray::get(stringType, chars));
    globalDeclaration->setConstant(true);
    globalDeclaration->setLinkage(llvm::GlobalValue::LinkageTypes::PrivateLinkage);
    globalDeclaration->setUnnamedAddr (llvm::GlobalValue::UnnamedAddr::Global);

    //4. Return a cast to an i8*
    return llvm::ConstantExpr::getBitCast(globalDeclaration, charType->getPointerTo());
}

llvm::Value* SNode::String::codeGen(CodeGenContext& context)
{
    return createString(context, this->value);
}

llvm::Value* SNode::Boolean::codeGen(CodeGenContext& context)
{
    // return llvm::ConstantInt::get(llvm::Type::getInt1Ty(context.context), this->value);
    return context.builder.getInt1(this->value);
}

llvm::Value* SNode::ExpressionStatement::codeGen(CodeGenContext& context)
{
    return this->expression.codeGen(context);
}

llvm::Value* SNode::Identifier::codeGen(CodeGenContext& context)
{
    llvm::Value* memVal = context.searchVar(this->name);
    return context.builder.CreateLoad(memVal);
}