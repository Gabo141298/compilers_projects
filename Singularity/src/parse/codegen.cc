#include "codegen.hh"
#include "../node/Program.hh"

/* Compile the AST into a module */
void SNode::CodeGenContext::generateCode(SNode::Program& root)
{
    root.codeGen(*this);
}
