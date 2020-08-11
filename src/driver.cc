#include "driver.hh"
#include "parser.hh"

driver::driver ()
  : trace_parsing (false), trace_scanning (false)
{
    consts["PI"] = std::unique_ptr<Variable> (new Double(3.14159265358));
    consts["E"] = std::unique_ptr<Variable> (new Double(2.71828182845));
}

int
driver::parse (const std::string &f)
{
  file = f;
  location.initialize (&file);
  scan_begin ();
  yy::parser parse (*this);
  parse.set_debug_level (trace_parsing);
  int res = parse ();
  scan_end ();
  return res;
}
