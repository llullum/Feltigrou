/* -*- C++ -*- */
// %option defines the parameters with which the reflex will be launched
%option noyywrap
// To enable compatibility with bison
%option bison-complete
%option bison-cc-parser=parser
%option bison_cc_namespace=parse
%option bison-locations

%option lex=lex
// Add a param of function lex() generate in Lexer class
%option params="::parse::TigerParser& tp"
%option namespace=parse
// Name of the class generate by reflex
%option lexer=Lexer

%top{

#define YY_EXTERN_C extern "C" // For linkage rule

#include <cerrno>
#include <climits>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << '\n';
  //
  // reports about `\n' instead of an actual new-line character.
#include <misc/escape.hh>
#include <misc/symbol.hh>
#include <parse/parsetiger.hh>
#include <parse/tiger-parser.hh>

// DONE: Some code was added here.
#define YY_USER_ACTION  \
  do {                       \          
    tp.location_ = location();  \
  } while (false) ;
 /* The power of the Tiger increased. */

#define TOKEN(Type)                             \
  parser::make_ ## Type(tp.location_)

#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, tp.location_)

# define CHECK_EXTENSION()                              \
  do {                                                  \
    if (!tp.enable_extensions_p_)                       \
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(text()) << "'\n";       \
  } while (false)


%}

%x SC_COMMENT SC_STRING

/* Abbreviations.  */
int             [0-9]+
// DONE: Some code was added here.
integer        {int}

letter [a-zA-Z_]+

white_characters [ \t]+

end_of_line (\n\r)|(\r)|(\r\n)|\n

identifiers    ([a-zA-Z][a-zA-Z0-9_]*)|"_main"

reserved_identifiers    ([_][a-zA-Z0-9_]*)

invalid_character .

%class{
  public:
    int val;
    int comment_nesting = 0;
    std::string grown_string;
}

%%

/* The rules.  */
/* DONE: Some code was added here. */
"/*"             { BEGIN(SC_COMMENT); }
<SC_COMMENT>{
"/*"           { ++comment_nesting; }
"*"+"/"        { if (comment_nesting) --comment_nesting;
                   else BEGIN(INITIAL); }
"*"+           ;
[^\/\*\n]+       ; /* pas sur pour lui*/
[/]            ; 
\n             ;
<<EOF>> {
  tp.error_ << misc::error::error_type::scan
                            << tp.location_
                                 << ": invalid EOF: `" << text() << "'\n"
                                << &misc::error::exit;
}
}

"\""        {grown_string.clear(); start(SC_STRING);};
<SC_STRING>{
"\""    { start(INITIAL); return TOKEN_VAL(STRING, grown_string);}

\\a {
  grown_string += "\\a";
}

\\b {
  grown_string += "\\b";
}

\\f {
  grown_string += "\\f";
}

\\n {
  grown_string += "\n";
}

\\r {
  grown_string += "\\r";
}

\\t {
  grown_string += "\\t";
}

\\v {
  grown_string += "\\v";
}

\\\" {
  grown_string += "\"";
}

\\x[0-9a-fA-F]{2} {
  grown_string += strtol(text()+2, 0, 16);
}

\\[0-7]{3} {
  if (strtol(text()+1, 0, 8) >= 0 && strtol(text()+1, 0, 8) <= 255)
  {
    grown_string += strtol(text()+1, 0, 8);
  }
  else
  {
    tp.error_ << misc::error::error_type::scan
                          << tp.location_
                          << ": bad octal: `" << text() << "'\n"
                                            << &misc::error::exit;
  }
}

\\ {
  grown_string += "\\";
}

\\. {
  tp.error_ << misc::error::error_type::scan
                            << tp.location_
                            << ": invalid escaped: `" << text() << "'\n"
                                             << &misc::error::exit;
}

<<EOF>> {
  tp.error_ << misc::error::error_type::scan
                            << tp.location_
                                 << ": invalid EOF: `" << text() << "'\n"
                                << &misc::error::exit;
} 

. {
  grown_string += text();
}
}

{int}         {
                val = 0;
                try
                {
                  val = std::stoi(text());
                }
                catch(std::out_of_range& e)
                {
                  tp.error_ << misc::error::error_type::scan
                            << tp.location_
                            << ": invalid integer: `" << text() << "'\n"
                                             << &misc::error::exit;
                }
                return TOKEN_VAL(INT, val);
              }


{end_of_line} {
                YY_USER_ACTION;
              }

{white_characters} {
                      YY_USER_ACTION;
                   }

"_cast" return TOKEN(CAST);

"_exp" return TOKEN(EXP);

"_lvalue" return TOKEN(LVALUE);

"_namety" return TOKEN(NAMETY);

"_chunks" return TOKEN(CHUNKS);

"array" return TOKEN(ARRAY);

"if" return TOKEN(IF);

"then" return TOKEN(THEN);

"else" return TOKEN(ELSE);

"while" return TOKEN(WHILE);

"for" return TOKEN(FOR);

"to" return TOKEN(TO);

"do" return TOKEN(DO);

"let" return TOKEN(LET);

"in" return TOKEN(IN);

"end" return TOKEN(END);

"of" return TOKEN(OF);

"break" return TOKEN(BREAK);

"nil" return TOKEN(NIL);

"function" return TOKEN(FUNCTION);

"var" return TOKEN(VAR);

"type" return TOKEN(TYPE);

"import" return TOKEN(IMPORT);

"primitive" return TOKEN(PRIMITIVE);


"class" {
  if (tp.enable_object_extensions_p_)
    return TOKEN(CLASS);

  tp.error_ << misc::error::error_type::scan
                          << tp.location_
                          << ": object extensions is disabled: `" << text() << "'\n"
                          << &misc::error::exit;

}
  
"extends" {
  if (tp.enable_object_extensions_p_)
    return TOKEN(EXTENDS);

  tp.error_ << misc::error::error_type::scan
                          << tp.location_
                          << ": object extensions is disabled: `" << text() << "'\n"
                          << &misc::error::exit;
}

"method" {
  if (tp.enable_object_extensions_p_)
    return TOKEN(METHOD);

  tp.error_ << misc::error::error_type::scan
                          << tp.location_
                          << ": object extensions is disabled: `" << text() << "'\n"
                          << &misc::error::exit;
}

"new" {
  if (tp.enable_object_extensions_p_)
    return TOKEN(NEW);

  tp.error_ << misc::error::error_type::scan
                          << tp.location_
                          << ": object extensions is disabled: `" << text() << "'\n"
                          << &misc::error::exit;
}

"," return TOKEN(COMMA);

":" return TOKEN(COLON);

";" return TOKEN(SEMI);

"(" return TOKEN(LPAREN);

")" return TOKEN(RPAREN);

"[" return TOKEN(LBRACK);

"]" return TOKEN(RBRACK);

"{" return TOKEN(LBRACE);

"}" return TOKEN(RBRACE);

"." return TOKEN(DOT);

"+" return TOKEN(PLUS);

"-" return TOKEN(MINUS);

"*" return TOKEN(TIMES);

"/" return TOKEN(DIVIDE);

"=" return TOKEN(EQ);

"<>" return TOKEN(NE);

"<" return TOKEN(LT);

"<=" return TOKEN(LE);

">" return TOKEN(GT);

">=" return TOKEN(GE);

"&" return TOKEN(AND);

"|" return TOKEN(OR);

":=" return TOKEN(ASSIGN);


{identifiers} {
                return TOKEN_VAL(ID, text());
              }

{reserved_identifiers} {
  CHECK_EXTENSION();
  return TOKEN_VAL(ID, text());
}

<<EOF>> {
  return TOKEN(EOF);
} 

{invalid_character} {
                tp.error_ << misc::error::error_type::scan
                          << tp.location_
                          << ": invalid character: `" << text() << "'\n"
                                           << &misc::error::exit;
              }


%%