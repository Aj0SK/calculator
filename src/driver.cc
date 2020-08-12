#include "driver.hh"
#include "parser.hh"

driver::driver ()
  : trace_parsing (false), trace_scanning (false)
{
    consts["PI"] = std::make_unique<Double>(3.14159265358);
    consts["E"] = std::make_unique<Double>(2.71828182845);

    fn1["sin"] = f_sin;
    fn1["cos"] = f_cos;
    fn1["tan"] = f_tan;
    fn1["abs"] = f_abs;

    fn2["gcd"] = f_gcd;
}

int
driver::parse_file (const std::string &f)
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

int
driver::parse_string (const std::string &s)
{
    file = "";
    input = s;
    location.initialize (&input);
    scan_begin ();
    yy::parser parse (*this);
    parse.set_debug_level (trace_parsing);
    int res = parse ();
    scan_end ();
    return res;
}
