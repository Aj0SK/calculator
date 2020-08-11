#ifndef DRIVER_HH
# define DRIVER_HH
# include <string>
# include <unordered_map>
# include <utility>
# include <memory>
# include <cmath>
# include <functional>
# include "variable.h"
# include "parser.hh"

// Give Flex the prototype of yylex we want ...
# define YY_DECL \
  yy::parser::symbol_type yylex (driver& drv)
// ... and declare it for the parser's sake.
YY_DECL;

// Conducting the whole scanning and parsing of Calc++.
class driver
{
public:
  driver ();

  std::unordered_map<std::string, std::unique_ptr<Variable> > vars, consts;
  std::unordered_map<std::string, std::function<std::unique_ptr<Variable> (const Variable& x)> > fn1;
  std::unordered_map<std::string, std::function<std::unique_ptr<Variable> (const Variable& a, const Variable& b)> > fn2;

  double result;

  // Run the parser on file F.  Return 0 on success.
  int parse (const std::string& f);
  // The name of the file being parsed.
  std::string file;
  // Whether to generate parser debug traces.
  bool trace_parsing;

  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  // Whether to generate scanner debug traces.
  bool trace_scanning;
  // The token's location used by the scanner.
  yy::location location;
};
#endif // ! DRIVER_HH
