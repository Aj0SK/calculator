%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.4.1"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
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
}

%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  DASH  ","
  ASSIGN  "="
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  DSTAR   "**"
  LPAREN  "("
  RPAREN  ")"
;

%token <std::string> CONSTANT "constant"
%token <std::string> IDENTIFIER "identifier"
%token <int> NATURAL "natural"
%token <double> FLOATING "floating"
%nterm <std::unique_ptr<Variable> > exp

%%
%start unit;
unit: assignments exp { drv.result = std::move($2); };

assignments:
  %empty                 {}
| assignments assignment {};

assignment:
  "identifier" "=" "natural"  { drv.vars[$1] = std::make_unique<Int>($3); }
| "identifier" "=" "floating" { drv.vars[$1] = std::make_unique<Double>($3); };

%left "+" "-";
%left "*" "/" "**";

exp:
  "identifier"  { $$ = std::move(drv.vars[$1]); }
| "constant"    { $$ = std::move(drv.consts[$1]); }
| "natural"     { $$ = std::make_unique<Int>($1); }
| "floating"    { $$ = std::make_unique<Double>($1); }
| exp "+" exp   { $$ = *$1 + *$3; }
| exp "-" exp   { $$ = *$1 - *$3; }
| exp "*" exp   { $$ = *$1 * *$3; }
| exp "/" exp   { $$ = *$1 / *$3; }
| "(" exp ")"   { $$ = std::move($2); }
| "(" "-" "natural" ")"     { $$ = std::make_unique<Int>(-$3); }
| "(" "-" "floating" ")"     { $$ = std::make_unique<Double>(-$3); }
| "identifier" "(" exp ")"  { $$ = drv.fn1[$1](*$3); }
| "identifier" "(" exp "," exp ")"  { $$ = drv.fn2[$1](*$3, *$5); }
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
