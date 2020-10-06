// A Bison parser, made by GNU Bison 3.7.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 1 "parse.yy"
     /* PARSER */

#include "parser.hh"
#include "scanner.hh"

#define yylex driver.scanner_->yylex

SNode::Program* programBlock;

#line 51 "parse.tab.cc"


#include "parse.tab.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 44 "parse.yy"
namespace parse {
#line 149 "parse.tab.cc"

  /// Build a parser object.
  Parser::Parser (Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  Parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  Parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // input: program
#line 150 "parse.yy"
               { programBlock = (yystack_[0].value.program); }
#line 616 "parse.tab.cc"
    break;

  case 3: // program: function
#line 152 "parse.yy"
                  { (yylhs.value.program) = new SNode::Program(); (yylhs.value.program)->functions.push_back((yystack_[0].value.function)); }
#line 622 "parse.tab.cc"
    break;

  case 4: // program: program function
#line 153 "parse.yy"
                               { (yystack_[1].value.program)->functions.push_back((yystack_[0].value.function)); }
#line 628 "parse.tab.cc"
    break;

  case 5: // block: BEGIN_BLOCK body END_BLOCK
#line 158 "parse.yy"
                  { (yylhs.value.block) = new SNode::Block(*(yystack_[1].value.body)); }
#line 634 "parse.tab.cc"
    break;

  case 6: // body: statement
#line 161 "parse.yy"
                      { (yylhs.value.body) = new SNode::Body(); (yylhs.value.body)->statements.push_back((yystack_[0].value.statement)); }
#line 640 "parse.tab.cc"
    break;

  case 7: // body: body statement
#line 162 "parse.yy"
                             { (yystack_[1].value.body)->statements.push_back((yystack_[0].value.statement)); }
#line 646 "parse.tab.cc"
    break;

  case 8: // statement: read
#line 165 "parse.yy"
                { (yylhs.value.statement) = (yystack_[0].value.statement); }
#line 652 "parse.tab.cc"
    break;

  case 9: // statement: set
#line 166 "parse.yy"
                  { (yylhs.value.statement) = (yystack_[0].value.statement); }
#line 658 "parse.tab.cc"
    break;

  case 10: // statement: print
#line 167 "parse.yy"
                    { (yylhs.value.statement) = (yystack_[0].value.statement); }
#line 664 "parse.tab.cc"
    break;

  case 11: // statement: if_condition
#line 168 "parse.yy"
                           { (yylhs.value.statement) = (yystack_[0].value.ifStatement); }
#line 670 "parse.tab.cc"
    break;

  case 12: // statement: while
#line 169 "parse.yy"
                    { (yylhs.value.statement) = (yystack_[0].value.statement); }
#line 676 "parse.tab.cc"
    break;

  case 13: // statement: while_counting
#line 170 "parse.yy"
                             { (yylhs.value.statement) = (yystack_[0].value.statement); }
#line 682 "parse.tab.cc"
    break;

  case 14: // statement: answer
#line 171 "parse.yy"
                     { (yylhs.value.statement) = (yystack_[0].value.statement); }
#line 688 "parse.tab.cc"
    break;

  case 15: // statement: func_call
#line 172 "parse.yy"
                        { (yylhs.value.statement) = new SNode::ExpressionStatement(*(yystack_[0].value.expression)); }
#line 694 "parse.tab.cc"
    break;

  case 16: // set: SET IDENTIFIER assignment
#line 176 "parse.yy"
            { (yylhs.value.statement) = new SNode::VariableAssignment(*(new SNode::Identifier(*(yystack_[1].value.var))), (yystack_[0].value.expression)); delete (yystack_[1].value.var); }
#line 700 "parse.tab.cc"
    break;

  case 17: // read: READ TO IDENTIFIER
#line 179 "parse.yy"
                         { (yylhs.value.statement) = new SNode::Read(*(yystack_[0].value.var)); delete (yystack_[0].value.var); }
#line 706 "parse.tab.cc"
    break;

  case 18: // assignment: TO expression
#line 181 "parse.yy"
                          { (yylhs.value.expression) = (yystack_[0].value.expression); }
#line 712 "parse.tab.cc"
    break;

  case 19: // assignment: AS data_structure
#line 182 "parse.yy"
                                { (yylhs.value.expression) = (yystack_[0].value.dataStructure); }
#line 718 "parse.tab.cc"
    break;

  case 20: // assignment: pos_assignment
#line 183 "parse.yy"
                             { (yylhs.value.expression) = (yystack_[0].value.dataPosAssignment); }
#line 724 "parse.tab.cc"
    break;

  case 21: // print: PRINT expression
#line 186 "parse.yy"
                        { (yylhs.value.statement) = new SNode::Print(*(yystack_[0].value.expression)); }
#line 730 "parse.tab.cc"
    break;

  case 22: // function: DEFINE FUNCTION IDENTIFIER block
#line 189 "parse.yy"
            { (yylhs.value.function) = new SNode::Function(*(new SNode::Identifier(*(yystack_[1].value.var))), *(yystack_[0].value.block)); delete (yystack_[1].value.var); }
#line 736 "parse.tab.cc"
    break;

  case 23: // function: DEFINE FUNCTION IDENTIFIER WITH ARGUMENTS arguments block
#line 191 "parse.yy"
            { (yylhs.value.function) = new SNode::Function(*(new SNode::Identifier(*(yystack_[4].value.var))), *(yystack_[1].value.variableList), *(yystack_[0].value.block)); delete (yystack_[4].value.var); }
#line 742 "parse.tab.cc"
    break;

  case 24: // arguments: IDENTIFIER
#line 194 "parse.yy"
                      { (yylhs.value.variableList) = new SNode::VariableList(); (yylhs.value.variableList)->push_back(new SNode::Identifier(*(yystack_[0].value.var))); delete (yystack_[0].value.var); }
#line 748 "parse.tab.cc"
    break;

  case 25: // arguments: arguments COMMA IDENTIFIER
#line 195 "parse.yy"
                                         { (yystack_[2].value.variableList)->push_back(new SNode::Identifier(*(yystack_[0].value.var))); delete (yystack_[0].value.var); }
#line 754 "parse.tab.cc"
    break;

  case 26: // parameters: expression
#line 197 "parse.yy"
                       { (yylhs.value.expressionList) = new SNode::ExpressionList(); (yylhs.value.expressionList)->push_back((yystack_[0].value.expression)); }
#line 760 "parse.tab.cc"
    break;

  case 27: // parameters: parameters COMMA expression
#line 198 "parse.yy"
                                          { (yystack_[2].value.expressionList)->push_back((yystack_[0].value.expression));  }
#line 766 "parse.tab.cc"
    break;

  case 28: // pos_assignment: OPEN_BRACKETS position CLOSE_BRACKETS TO expression
#line 201 "parse.yy"
            { (yylhs.value.dataPosAssignment) = new SNode::DataPositionAssignment(*(yystack_[3].value.position), *(yystack_[0].value.expression)); }
#line 772 "parse.tab.cc"
    break;

  case 29: // position: expression
#line 204 "parse.yy"
                     { (yylhs.value.position) = new SNode::ListPosition(*(yystack_[0].value.expression)); }
#line 778 "parse.tab.cc"
    break;

  case 30: // position: expression COMMA expression
#line 205 "parse.yy"
                                          { (yylhs.value.position) = new SNode::MatrixPosition(*(yystack_[2].value.expression), *(yystack_[0].value.expression)); }
#line 784 "parse.tab.cc"
    break;

  case 31: // data_structure: LIST
#line 207 "parse.yy"
                     { (yylhs.value.dataStructure) = new SNode::List(); }
#line 790 "parse.tab.cc"
    break;

  case 32: // data_structure: MATRIX intvalue BY intvalue
#line 208 "parse.yy"
                                          { (yylhs.value.dataStructure) = new SNode::Matrix((yystack_[2].value.value), (yystack_[0].value.value)); }
#line 796 "parse.tab.cc"
    break;

  case 33: // if_condition: IF bool_cond block if_statement
#line 211 "parse.yy"
                                              { (yylhs.value.ifStatement) = new SNode::If(*(yystack_[2].value.expression), *(yystack_[1].value.block), (yystack_[0].value.statement)); }
#line 802 "parse.tab.cc"
    break;

  case 34: // if_statement: %empty
#line 214 "parse.yy"
                     { (yylhs.value.statement) = nullptr; }
#line 808 "parse.tab.cc"
    break;

  case 35: // if_statement: OTHERWISE otherwise
#line 215 "parse.yy"
                                      { (yylhs.value.statement) = (yystack_[0].value.statement); }
#line 814 "parse.tab.cc"
    break;

  case 36: // otherwise: if_condition
#line 218 "parse.yy"
                        { (yylhs.value.statement) = new SNode::OtherwiseIf(*(yystack_[0].value.ifStatement)); }
#line 820 "parse.tab.cc"
    break;

  case 37: // otherwise: block
#line 219 "parse.yy"
                    { (yylhs.value.statement) = new SNode::Otherwise(*(yystack_[0].value.block)); }
#line 826 "parse.tab.cc"
    break;

  case 38: // while: WHILE bool_cond block
#line 222 "parse.yy"
                             { (yylhs.value.statement) = new SNode::While(*(yystack_[1].value.expression), *(yystack_[0].value.block)); }
#line 832 "parse.tab.cc"
    break;

  case 39: // while_counting: WHILE IDENTIFIER COUNTING FROM expression TO expression block
#line 225 "parse.yy"
                { (yylhs.value.statement) = new SNode::WhileCounting(*(new SNode::Identifier(*(yystack_[6].value.var))), *(yystack_[3].value.expression), *(yystack_[1].value.expression), *(yystack_[0].value.block)); delete (yystack_[6].value.var); }
#line 838 "parse.tab.cc"
    break;

  case 40: // bool_cond: condition bool_cond2
#line 227 "parse.yy"
                                {
                if((yystack_[0].value.rsBoolExpr))
                {
                    (yylhs.value.expression) = new SNode::BooleanOperator(*(yystack_[1].value.expression), (yystack_[0].value.rsBoolExpr)->op, (yystack_[0].value.rsBoolExpr)->exp);
                    delete (yystack_[0].value.rsBoolExpr);
                }
                else
                {
                    (yylhs.value.expression) = (yystack_[1].value.expression);
                }
            }
#line 854 "parse.tab.cc"
    break;

  case 41: // bool_cond: NOT bool_cond
#line 238 "parse.yy"
                            { (yylhs.value.expression) = new SNode::NotOperator(*(yystack_[0].value.expression)); }
#line 860 "parse.tab.cc"
    break;

  case 42: // bool_cond2: boolean_operator bool_cond
#line 241 "parse.yy"
                                       { (yylhs.value.rsBoolExpr) = new SNode::RightSideBoolExpr((yystack_[1].value.boolOper), *(yystack_[0].value.expression)); }
#line 866 "parse.tab.cc"
    break;

  case 43: // bool_cond2: %empty
#line 242 "parse.yy"
                     { (yylhs.value.rsBoolExpr) = nullptr; }
#line 872 "parse.tab.cc"
    break;

  case 44: // condition: comparison
#line 245 "parse.yy"
                      { (yylhs.value.expression) = (yystack_[0].value.rsCompExpr); }
#line 878 "parse.tab.cc"
    break;

  case 45: // condition: IDENTIFIER
#line 246 "parse.yy"
                         { (yylhs.value.expression) = new SNode::Identifier(*(yystack_[0].value.var)); delete (yystack_[0].value.var); }
#line 884 "parse.tab.cc"
    break;

  case 46: // condition: boolean
#line 247 "parse.yy"
                      { (yylhs.value.expression) = (yystack_[0].value.value); }
#line 890 "parse.tab.cc"
    break;

  case 47: // comparison: expression comp_operator expression
#line 251 "parse.yy"
            { (yylhs.value.rsCompExpr) = new SNode::ComparisonOperator(*(yystack_[2].value.expression), (yystack_[1].value.compOper), *(yystack_[0].value.expression)); }
#line 896 "parse.tab.cc"
    break;

  case 48: // comp_operator: LEQ
#line 254 "parse.yy"
                   { (yylhs.value.compOper) = SNode::ComparisonOperation::leq; }
#line 902 "parse.tab.cc"
    break;

  case 49: // comp_operator: GEQ
#line 255 "parse.yy"
                  { (yylhs.value.compOper) = SNode::ComparisonOperation::geq; }
#line 908 "parse.tab.cc"
    break;

  case 50: // comp_operator: GREATER
#line 256 "parse.yy"
                      { (yylhs.value.compOper) = SNode::ComparisonOperation::greater; }
#line 914 "parse.tab.cc"
    break;

  case 51: // comp_operator: LESS
#line 257 "parse.yy"
                   { (yylhs.value.compOper) = SNode::ComparisonOperation::less; }
#line 920 "parse.tab.cc"
    break;

  case 52: // comp_operator: EQUALS
#line 258 "parse.yy"
                     { (yylhs.value.compOper) = SNode::ComparisonOperation::equals; }
#line 926 "parse.tab.cc"
    break;

  case 53: // comp_operator: IS NOT
#line 259 "parse.yy"
                     { (yylhs.value.compOper) = SNode::ComparisonOperation::isNot; }
#line 932 "parse.tab.cc"
    break;

  case 54: // boolean_operator: XOR
#line 262 "parse.yy"
                      { (yylhs.value.boolOper) = SNode::BooleanOperation::bXor; }
#line 938 "parse.tab.cc"
    break;

  case 55: // boolean_operator: OR
#line 263 "parse.yy"
                 { (yylhs.value.boolOper) = SNode::BooleanOperation::bOr; }
#line 944 "parse.tab.cc"
    break;

  case 56: // boolean_operator: AND
#line 264 "parse.yy"
                  { (yylhs.value.boolOper) = SNode::BooleanOperation::bAnd; }
#line 950 "parse.tab.cc"
    break;

  case 57: // boolean: TRUE
#line 267 "parse.yy"
              { (yylhs.value.value) = new SNode::Boolean(true); }
#line 956 "parse.tab.cc"
    break;

  case 58: // boolean: FALSE
#line 268 "parse.yy"
                    { (yylhs.value.value) = new SNode::Boolean(false); }
#line 962 "parse.tab.cc"
    break;

  case 59: // intvalue: INTEGER
#line 271 "parse.yy"
                   { (yylhs.value.value) = new SNode::Integer(atoll((yystack_[0].value.var)->c_str())); delete (yystack_[0].value.var); }
#line 968 "parse.tab.cc"
    break;

  case 60: // intvalue: IDENTIFIER
#line 272 "parse.yy"
                         { (yylhs.value.value) = new SNode::Identifier(*(yystack_[0].value.var)); delete (yystack_[0].value.var); }
#line 974 "parse.tab.cc"
    break;

  case 61: // value: FLOAT
#line 275 "parse.yy"
                  { (yylhs.value.value) = new SNode::Double(atof((yystack_[0].value.var)->c_str())); delete (yystack_[0].value.var); }
#line 980 "parse.tab.cc"
    break;

  case 62: // value: INTEGER
#line 276 "parse.yy"
                      { (yylhs.value.value) = new SNode::Integer(atoll((yystack_[0].value.var)->c_str())); delete (yystack_[0].value.var); }
#line 986 "parse.tab.cc"
    break;

  case 63: // value: IDENTIFIER
#line 277 "parse.yy"
                         { (yylhs.value.value) = new SNode::Identifier(*(yystack_[0].value.var)); delete (yystack_[0].value.var); }
#line 992 "parse.tab.cc"
    break;

  case 64: // value: STRING
#line 278 "parse.yy"
                     { (yylhs.value.value) = new SNode::String(*(yystack_[0].value.var)); delete (yystack_[0].value.var); }
#line 998 "parse.tab.cc"
    break;

  case 65: // value: boolean
#line 279 "parse.yy"
                      { (yylhs.value.value) = (yystack_[0].value.value); }
#line 1004 "parse.tab.cc"
    break;

  case 66: // expression: IDENTIFIER OPEN_BRACKETS position CLOSE_BRACKETS
#line 282 "parse.yy"
                                                             {  (yylhs.value.expression) = new SNode::PositionAccess( *(new SNode::Identifier(*(yystack_[3].value.var))), *(yystack_[1].value.position)); delete (yystack_[3].value.var); }
#line 1010 "parse.tab.cc"
    break;

  case 67: // expression: value expression2
#line 283 "parse.yy"
                                { 
                if((yystack_[0].value.rsArithExpr)) 
                {
                    (yylhs.value.expression) = new SNode::ArithmeticOperator(*(yystack_[1].value.value), (yystack_[0].value.rsArithExpr)->op, (yystack_[0].value.rsArithExpr)->exp);
                    delete (yystack_[0].value.rsArithExpr);
                }
                else
                {
                    (yylhs.value.expression) = (yystack_[1].value.value);
                }
            }
#line 1026 "parse.tab.cc"
    break;

  case 68: // expression: func_call
#line 294 "parse.yy"
              { (yylhs.value.expression) = (yystack_[0].value.expression); }
#line 1032 "parse.tab.cc"
    break;

  case 69: // expression2: %empty
#line 297 "parse.yy"
                    { (yylhs.value.rsArithExpr) = nullptr; }
#line 1038 "parse.tab.cc"
    break;

  case 70: // expression2: arith_oper expression
#line 298 "parse.yy"
                                    { (yylhs.value.rsArithExpr) = new SNode::RightSideArithExpr((yystack_[1].value.arithOper), *(yystack_[0].value.expression)); }
#line 1044 "parse.tab.cc"
    break;

  case 71: // arith_oper: ADDITION
#line 301 "parse.yy"
                     { (yylhs.value.arithOper) = SNode::Operation::addition; }
#line 1050 "parse.tab.cc"
    break;

  case 72: // arith_oper: SUBSTRACTION
#line 302 "parse.yy"
                           { (yylhs.value.arithOper) = SNode::Operation::substraction; }
#line 1056 "parse.tab.cc"
    break;

  case 73: // arith_oper: MULTIPLICATION
#line 303 "parse.yy"
                             { (yylhs.value.arithOper) = SNode::Operation::multiplication; }
#line 1062 "parse.tab.cc"
    break;

  case 74: // arith_oper: DIVISION
#line 304 "parse.yy"
                       { (yylhs.value.arithOper) = SNode::Operation::division; }
#line 1068 "parse.tab.cc"
    break;

  case 75: // arith_oper: MODULO
#line 305 "parse.yy"
                     { (yylhs.value.arithOper) = SNode::Operation::modulo; }
#line 1074 "parse.tab.cc"
    break;

  case 76: // func_call: CALL IDENTIFIER
#line 308 "parse.yy"
                           { (yylhs.value.expression) = new SNode::FunctionCall(*(new SNode::Identifier(*(yystack_[0].value.var)))); delete (yystack_[0].value.var); }
#line 1080 "parse.tab.cc"
    break;

  case 77: // func_call: CALL IDENTIFIER WITH PARAMETERS OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS
#line 310 "parse.yy"
            { (yylhs.value.expression) = new SNode::FunctionCall(*(new SNode::Identifier(*(yystack_[5].value.var))), *(yystack_[1].value.expressionList)); delete (yystack_[5].value.var); }
#line 1086 "parse.tab.cc"
    break;

  case 78: // answer: ANSWER expression
#line 314 "parse.yy"
        { (yylhs.value.statement) = new SNode::Answer(*(yystack_[0].value.expression)); }
#line 1092 "parse.tab.cc"
    break;


#line 1096 "parse.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -44;

  const signed char Parser::yytable_ninf_ = -47;

  const signed char
  Parser::yypact_[] =
  {
       8,   -21,    34,     8,   -44,    48,   -44,   -44,    26,    70,
      13,   -44,    50,    56,    17,     6,    11,    17,    72,    96,
     -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,    75,
      18,    78,    36,   -44,   -44,   -44,   -44,   -44,   -44,    38,
     -44,   -44,    29,     6,    87,    67,   -44,    61,    85,     7,
      87,   -44,    81,   -44,   -44,   -44,     1,    17,    77,    17,
     -44,   -44,   -44,    17,   -44,   -44,   -44,   -44,   -44,   -44,
      17,   -44,    91,   -44,   -44,   -44,   -44,     6,   -44,   -44,
     -44,   -44,   -44,    80,    17,    64,   -44,    92,   111,   -44,
     -44,   -44,    97,   -44,    79,    69,    82,   -44,    30,   -44,
     -44,   -44,   -44,    17,    86,   -44,   -44,   -44,   116,   123,
      17,   -44,   -44,   -44,   -44,   124,    17,    97,    17,   -44,
      17,   -20,   -44,   -44,   -44,    87,   -44,    17,   -44,   -44
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     2,     3,     0,     1,     4,     0,     0,
       0,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     9,     8,    10,    11,    12,    13,    15,    14,     0,
       0,     0,    63,    62,    61,    64,    58,    57,    65,    69,
      21,    68,    63,     0,     0,    43,    44,    65,     0,    63,
       0,    78,    76,     5,     7,    24,     0,     0,     0,     0,
      16,    20,    17,     0,    71,    72,    73,    74,    75,    67,
       0,    41,    34,    56,    55,    54,    40,     0,    52,    49,
      48,    50,    51,     0,     0,     0,    38,     0,     0,    23,
      18,    31,     0,    19,     0,    29,     0,    70,     0,    33,
      42,    53,    47,     0,     0,    25,    60,    59,     0,     0,
       0,    66,    37,    36,    35,     0,     0,     0,     0,    30,
       0,     0,    26,    32,    28,     0,    77,     0,    39,    27
  };

  const short
  Parser::yypgoto_[] =
  {
     -44,   -44,   -44,   -43,   -44,   114,   -44,   -44,   -44,   -44,
     131,   -44,   -44,   -44,    73,   -44,    39,   -44,   -44,   -44,
     -44,   -10,   -44,   -44,   -44,   -44,   -44,   -11,    21,   -44,
     -14,   -44,   -44,    -1,   -44
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,    11,    19,    20,    21,    22,    60,    23,
       4,    56,   121,    61,    94,    93,    24,    99,   114,    25,
      26,    44,    76,    45,    46,    84,    77,    38,   108,    39,
      48,    69,    70,    41,    28
  };

  const short
  Parser::yytable_[] =
  {
      40,    72,     5,    51,    47,    47,    50,    86,    27,    42,
      33,    34,    35,    89,    49,    33,    34,    35,    27,     9,
      32,    33,    34,    35,   126,   -45,    57,    58,    85,   127,
       1,    18,    47,    71,     6,    43,    18,   -45,   -45,   -45,
      43,    29,    18,    90,     9,    95,    15,   -45,     9,    95,
      88,     8,    10,    30,    63,   112,    97,    36,    37,   -45,
     -45,   -45,    36,    37,    31,    59,    47,   100,    36,    37,
     102,    64,    65,    66,    67,    52,    63,    12,    55,   -46,
      68,    62,   128,    63,    13,    14,    15,    91,    92,   115,
      16,   -46,   -46,   -46,    17,    18,   119,    73,    74,    75,
     106,   107,   122,    12,   124,     9,   125,    87,    98,   101,
      13,    14,    15,   129,   105,    53,    16,   103,   110,   104,
      17,    18,    78,    79,    80,    81,    82,   109,   117,   116,
     111,   118,   120,    54,     7,    83,    96,   113,   123
  };

  const signed char
  Parser::yycheck_[] =
  {
      14,    44,    23,    17,    15,    16,    16,    50,     9,     3,
       4,     5,     6,    56,     3,     4,     5,     6,    19,    18,
       3,     4,     5,     6,    44,    18,     8,     9,    21,    49,
      22,    25,    43,    43,     0,    29,    25,    30,    31,    32,
      29,    28,    25,    57,    18,    59,    16,    18,    18,    63,
      49,     3,    26,     3,    47,    98,    70,    51,    52,    30,
      31,    32,    51,    52,     8,    47,    77,    77,    51,    52,
      84,    33,    34,    35,    36,     3,    47,     7,     3,    18,
      42,     3,   125,    47,    14,    15,    16,    10,    11,   103,
      20,    30,    31,    32,    24,    25,   110,    30,    31,    32,
       3,     4,   116,     7,   118,    18,   120,    26,    17,    29,
      14,    15,    16,   127,     3,    19,    20,    53,    49,    27,
      24,    25,    37,    38,    39,    40,    41,    48,    12,    43,
      48,     8,     8,    19,     3,    50,    63,    98,   117
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    22,    55,    56,    64,    23,     0,    64,     3,    18,
      26,    57,     7,    14,    15,    16,    20,    24,    25,    58,
      59,    60,    61,    63,    70,    73,    74,    87,    88,    28,
       3,     8,     3,     4,     5,     6,    51,    52,    81,    83,
      84,    87,     3,    29,    75,    77,    78,    81,    84,     3,
      75,    84,     3,    19,    59,     3,    65,     8,     9,    47,
      62,    67,     3,    47,    33,    34,    35,    36,    42,    85,
      86,    75,    57,    30,    31,    32,    76,    80,    37,    38,
      39,    40,    41,    50,    79,    21,    57,    26,    49,    57,
      84,    10,    11,    69,    68,    84,    68,    84,    17,    71,
      75,    29,    84,    53,    27,     3,     3,     4,    82,    48,
      49,    48,    57,    70,    72,    84,    43,    12,     8,    84,
       8,    66,    84,    82,    84,    84,    44,    49,    57,    84
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    54,    55,    56,    56,    57,    58,    58,    59,    59,
      59,    59,    59,    59,    59,    59,    60,    61,    62,    62,
      62,    63,    64,    64,    65,    65,    66,    66,    67,    68,
      68,    69,    69,    70,    71,    71,    72,    72,    73,    74,
      75,    75,    76,    76,    77,    77,    77,    78,    79,    79,
      79,    79,    79,    79,    80,    80,    80,    81,    81,    82,
      82,    83,    83,    83,    83,    83,    84,    84,    84,    85,
      85,    86,    86,    86,    86,    86,    87,    87,    88
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     3,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     2,     2,
       1,     2,     4,     7,     1,     3,     1,     3,     5,     1,
       3,     1,     4,     4,     0,     2,     1,     1,     3,     8,
       2,     2,     2,     0,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     2,     1,     0,
       2,     1,     1,     1,     1,     1,     2,     7,     2
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "TOK_EOF", "error", "\"invalid token\"", "IDENTIFIER", "INTEGER",
  "FLOAT", "STRING", "SET", "TO", "AS", "LIST", "MATRIX", "BY", "AT",
  "READ", "PRINT", "IF", "OTHERWISE", "BEGIN_BLOCK", "END_BLOCK", "WHILE",
  "COUNTING", "DEFINE", "FUNCTION", "ANSWER", "CALL", "WITH", "PARAMETERS",
  "ARGUMENTS", "NOT", "AND", "OR", "XOR", "ADDITION", "SUBSTRACTION",
  "MULTIPLICATION", "DIVISION", "EQUALS", "GEQ", "LEQ", "GREATER", "LESS",
  "MODULO", "OPEN_PARENTHESIS", "CLOSE_PARENTHESIS", "QUOTES_ERROR",
  "HASH", "OPEN_BRACKETS", "CLOSE_BRACKETS", "COMMA", "IS", "FALSE",
  "TRUE", "FROM", "$accept", "input", "program", "block", "body",
  "statement", "set", "read", "assignment", "print", "function",
  "arguments", "parameters", "pos_assignment", "position",
  "data_structure", "if_condition", "if_statement", "otherwise", "while",
  "while_counting", "bool_cond", "bool_cond2", "condition", "comparison",
  "comp_operator", "boolean_operator", "boolean", "intvalue", "value",
  "expression", "expression2", "arith_oper", "func_call", "answer", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   150,   150,   152,   153,   156,   161,   162,   165,   166,
     167,   168,   169,   170,   171,   172,   175,   179,   181,   182,
     183,   186,   188,   190,   194,   195,   197,   198,   200,   204,
     205,   207,   208,   211,   214,   215,   218,   219,   222,   224,
     227,   238,   241,   242,   245,   246,   247,   250,   254,   255,
     256,   257,   258,   259,   262,   263,   264,   267,   268,   271,
     272,   275,   276,   277,   278,   279,   282,   283,   294,   297,
     298,   301,   302,   303,   304,   305,   308,   309,   313
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
    };
    // Last valid token kind.
    const int code_max = 308;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 44 "parse.yy"
} // parse
#line 1706 "parse.tab.cc"

#line 317 "parse.yy"


namespace parse
{
    void Parser::error(const location&, const std::string& m)
    {
        std::cerr << *driver.location_ << ": " << m << std::endl;
        driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
    }
}
