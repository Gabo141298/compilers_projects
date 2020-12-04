#include "Position.hh"

#include "node.hh"
#include "Print.hh"

namespace SNode
{

llvm::Value* ListPosition::codeGen(CodeGenContext&) { return nullptr; }
void ListPosition::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "ListPosition: " << std::endl;

    printTabs(tabs + 1);
    std::cout << "Position:" << std::endl;
    position.print(tabs + 1);
}
void ListPosition::checkPosition()
{
    Datatype type = position.getExpressionType();
    switch(type)
    {
        case Datatype::UNKNOWN:
        case Datatype::INTEGER: return ;
        case Datatype::BOOLEAN: throw SingularityException(ExceptionType::LIST_POSITION_BOOLEAN);
        case Datatype::DOUBLE: throw SingularityException(ExceptionType::LIST_POSITION_DOUBLE);
        case Datatype::STRING: throw SingularityException(ExceptionType::LIST_POSITION_STRING);
        case Datatype::FUNCTION: throw SingularityException(ExceptionType::LIST_POSITION_FUNCTION);
        case Datatype::LIST: throw SingularityException(ExceptionType::LIST_POSITION_LIST);
        case Datatype::MATRIX: throw SingularityException(ExceptionType::LIST_POSITION_MATRIX);
        default: break;
    }
}

llvm::Value* ListPosition::calculateMemDir(CodeGenContext& context, llvm::Value* ptr, VariableInfo*)
{
    llvm::Value* val = this->position.codeGen(context);
    auto dataSize = context.builder.getInt64(context.dataLayout.getTypeAllocSize(context.builder.getDoubleTy()));
    if(val->getType()->isDoubleTy())
        val = context.builder.CreateCast(llvm::Instruction::FPToSI, val, context.builder.getInt64Ty());
    llvm::Value* pos = context.builder.CreateMul(val, dataSize);

    llvm::Value* intPtr = context.builder.CreatePtrToInt(ptr, context.builder.getInt64Ty());

    return context.builder.CreateIntToPtr(context.builder.CreateAdd(intPtr, pos), context.builder.getDoubleTy()->getPointerTo());
}

llvm::Value* MatrixPosition::codeGen(CodeGenContext&) { return nullptr; }
void MatrixPosition::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "MatrixPosition: " << std::endl;

    printTabs(tabs + 1);
    std::cout << "Row:" << std::endl;
    row.print(tabs + 1);

    printTabs(tabs + 1);
    std::cout << "Col:" << std::endl;
    col.print(tabs + 1);
}
void MatrixPosition::checkPosition()
{
    Datatype rowType = row.getExpressionType();
    Datatype colType = col.getExpressionType();

    // If any of the expressions is boolean, throw an error
    if(rowType == Datatype::BOOLEAN || colType == Datatype::BOOLEAN)
        throw SingularityException(ExceptionType::MATRIX_POSITION_BOOLEAN);
    // If any of the expressions is a function, throw an error
    else if(rowType == Datatype::FUNCTION || colType == Datatype::FUNCTION)
        throw SingularityException(ExceptionType::MATRIX_POSITION_FUNCTION);
    // If any of the expressions is a list name, throw an error
    else if(rowType == Datatype::LIST || colType == Datatype::LIST)
        throw SingularityException(ExceptionType::MATRIX_POSITION_LIST);
    // If any of the expressions is a matrix name, throw an error
    else if(rowType == Datatype::MATRIX || colType == Datatype::MATRIX)
        throw SingularityException(ExceptionType::MATRIX_POSITION_MATRIX);
    // If any of the expressions is a string, throw an error.
    else if(rowType == Datatype::STRING || colType == Datatype::STRING)
        throw SingularityException(ExceptionType::MATRIX_POSITION_STRING);
    // If any of the two expressions is a double, throw an error.
    else if(rowType == Datatype::DOUBLE || colType == Datatype::DOUBLE)
        throw SingularityException(ExceptionType::MATRIX_POSITION_DOUBLE);
}

llvm::Value* MatrixPosition::calculateMemDir(CodeGenContext& context, llvm::Value* ptr, VariableInfo* varInfo)
{
    llvm::Value* rowVal = this->row.codeGen(context);
    llvm::Value* colVal = this->col.codeGen(context);
    auto dataSize = context.builder.getInt64(context.dataLayout.getTypeAllocSize(context.builder.getDoubleTy()));
    if(rowVal->getType()->isDoubleTy())
        rowVal = context.builder.CreateCast(llvm::Instruction::FPToSI, rowVal, context.builder.getInt64Ty());
    if(colVal->getType()->isDoubleTy())
        colVal = context.builder.CreateCast(llvm::Instruction::FPToSI, colVal, context.builder.getInt64Ty());

    llvm::Value* totalCol = varInfo->col;

    llvm::Value* rowPos = context.builder.CreateMul(rowVal, totalCol);

    llvm::Value* pos = context.builder.CreateMul(context.builder.CreateAdd(rowPos, colVal), dataSize);

    llvm::Value* intPtr = context.builder.CreatePtrToInt(ptr, context.builder.getInt64Ty());

    return context.builder.CreateIntToPtr(context.builder.CreateAdd(intPtr, pos), context.builder.getDoubleTy()->getPointerTo());
}

}