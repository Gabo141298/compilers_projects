
#include <iostream>
#include <strstream>
#include <string>

#include "antlr4-runtime.h"
#include "chess_parseLexer.h"
#include "chess_parseParser.h"
#include "chess_parseCustomVisitor.h"

#include "src/SemanticAnalyzer.h"

using namespace antlr4;

class MyParserErrorListener : public antlr4::BaseErrorListener
{
  virtual void syntaxError(
      antlr4::Recognizer *recognizer,
      antlr4::Token *offendingSymbol,
      size_t line,
      size_t charPositionInLine,
      const std::string &msg,
      std::exception_ptr e) override
  {
    std::ostrstream s;
    s << "Line(" << line << ":" << charPositionInLine << ") Error(" << msg << ")";
    throw std::invalid_argument(s.str());
  }
};

int main(int argc, char *argv[])
{
  std::ifstream t(argv[1]);
  std::stringstream buffer;
  buffer << t.rdbuf();

  antlr4::ANTLRInputStream input(buffer.str().c_str());

  chess_parseLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);

  MyParserErrorListener errorListner;

  tokens.fill();
  // Only if you want to list the tokens
  // for (auto token : tokens.getTokens()) {
  //  std::cout << token->toString() << std::endl;
  // }


  chess_parseParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(&errorListner);
  try
  {
    chess_parseParser::GameContext *tree = parser.game();
    chess_parseCustomVisitor visitor;
    SemanticAnalyzer* semanticAnalyzer = visitor.visitGame(tree);

    std::cout << "Holix";
    std::cout << *semanticAnalyzer ;

    //   std::cout << tree->toStringTree() << std::endl;
    //   return 0;
  }
  catch (std::invalid_argument &e)
  {
    std::cout << e.what() << std::endl;
    return 10;
  }
}
