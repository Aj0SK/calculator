%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.4.1"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  # include <string>
  # include <iomanip>
  class driver;
  class Variable;
  class Int;
  class Double;
}

// The parsing context.
%param { driver& drv }

%locations

%define parse.trace
%define parse.error verbose

%code {
# include "driver.hh"
# include <iostream>
# include <iomanip>
}

%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  ASSIGN  "="
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  DSTAR   "**"
  LPAREN  "("
  RPAREN  ")"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NATURAL "natural"
%token <double> FLOATING "floating"
%nterm <std::unique_ptr<Variable> > exp

%printer { yyo << std::fixed << std::setprecision(3) << "aa"; } <*>;

%%
%start unit;
unit: assignments exp { drv.result = $2->value(); };

assignments:
  %empty                 {}
| assignments assignment {};

assignment:
  "identifier" "=" "natural"  { drv.vars[$1] = std::unique_ptr<Variable> (new Int($3)); }
| "identifier" "=" "floating" { drv.vars[$1] = std::unique_ptr<Variable> (new Double($3)); };

%left "+" "-";
%left "*" "/" "**";

exp:
  "natural"     { $$ = std::unique_ptr<Variable>(new Int($1)); }
| "floating"    { $$ = std::unique_ptr<Variable>(new Double($1)); }
| "identifier"  { $$ = std::move(drv.vars[$1]); }
| exp "+" exp   { $$ = *$1 + *$3; }
| exp "-" exp   { $$ = *$1 - *$3; }
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
