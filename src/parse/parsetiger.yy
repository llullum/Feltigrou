                                                                // -*- C++ -*-
%require "3.8"
%language "c++"
// Set the namespace name to `parse', instead of `yy'.
%define api.prefix {parse}
%define api.namespace {parse}
%define api.parser.class {parser}
%define api.value.type variant
%define api.token.constructor

// We use a GLR parser because it is able to handle Shift-Reduce and
// Reduce-Reduce conflicts by forking and testing each way at runtime. GLR
// permits, by allowing few conflicts, more readable and maintainable grammars.
%glr-parser
%skeleton "glr2.cc"

// In TC, we expect the GLR to resolve one Shift-Reduce and zero Reduce-Reduce
// conflict at runtime. Use %expect and %expect-rr to tell Bison about it.

  // DONE: Some code was added here.
  %expect 1
  %expect-rr 0
  // The power of the Tiger increased.

%define parse.error verbose
%defines
%debug
// Prefix all the tokens with TOK_ to avoid colisions.
%define api.token.prefix {TOK_}

/* We use pointers to store the filename in the locations.  This saves
   space (pointers), time (no deep copy), but leaves the problem of
   deallocation.  This would be a perfect job for a misc::symbol
   object (passed by reference), however Bison locations require the
   filename to be passed as a pointer, thus forcing us to handle the
   allocation and deallocation of this object.

   Nevertheless, all is not lost: we can still use a misc::symbol
   object to allocate a flyweight (constant) string in the pool of
   symbols, extract it from the misc::symbol object, and use it to
   initialize the location.  The allocated data will be freed at the
   end of the program (see the documentation of misc::symbol and
   misc::unique).  */
%define api.filename.type {const std::string}
%locations

/*---------------------.
| Support for tokens.  |
`---------------------*/
%code requires
{
#include <string>
#include <misc/algorithm.hh>
#include <misc/separator.hh>
#include <misc/symbol.hh>
#include <parse/fwd.hh>

  // Pre-declare parse::parse to allow a ``reentrant'' parsing within
  // the parser.
  namespace parse
  {
    ast_type parse(Tweast& input);
  }
}

// The parsing context.
%param { ::parse::TigerParser& tp }
%parse-param { ::parse::Lexer& lexer }

%printer { yyo << $$; } <int> <std::string> <misc::symbol>;

%token <std::string>    STRING "string"
%token <misc::symbol>   ID     "identifier"
%token <int>            INT    "integer"


/*--------------------------------.
| Support for the non-terminals.  |
`--------------------------------*/

%code requires
{
# include <ast/fwd.hh>
// Provide the declarations of the following classes for the
// %destructor clauses below to work properly.
# include <ast/exp.hh>
# include <ast/var.hh>
# include <ast/ty.hh>
# include <ast/name-ty.hh>
# include <ast/field.hh>
# include <ast/field-init.hh>
# include <ast/function-dec.hh>
# include <ast/type-dec.hh>
# include <ast/var-dec.hh>
# include <ast/chunk.hh>
# include <ast/chunk-list.hh>
}

  // FIXME: Some code was deleted here (Printers and destructors).

/*-----------------------------------------.
| Code output in the implementation file.  |
`-----------------------------------------*/

%code
{
# include <parse/tweast.hh>
# include <misc/separator.hh>
# include <misc/symbol.hh>
# include <ast/all.hh>
# include <ast/libast.hh>
# include <parse/tiger-driver.hh>

  namespace
  {

    /// Get the metavar from the specified map.
    template <typename T>
    T*
    metavar(parse::TigerParser& tp, unsigned key)
    {
      parse::Tweast* input = tp.input_;
      return input->template take<T>(key);
    }

  }
}

%code
{
  #include <parse/scantiger.hh>  // header file generated with reflex --header-file
  #undef yylex
  #define yylex lexer.lex  // Within bison's parse() we should invoke lexer.lex(), not the global lex()
}

// Definition of the tokens, and their pretty-printing.
%token AND          "&"
       ARRAY        "array"
       ASSIGN       ":="
       BREAK        "break"
       CAST         "_cast"
       CLASS        "class"
       COLON        ":"
       COMMA        ","
       DIVIDE       "/"
       DO           "do"
       DOT          "."
       ELSE         "else"
       END          "end"
       EQ           "="
       EXTENDS      "extends"
       FOR          "for"
       FUNCTION     "function"
       GE           ">="
       GT           ">"
       IF           "if"
       IMPORT       "import"
       IN           "in"
       LBRACE       "{"
       LBRACK       "["
       LE           "<="
       LET          "let"
       LPAREN       "("
       LT           "<"
       MINUS        "-"
       METHOD       "method"
       NE           "<>"
       NEW          "new"
       NIL          "nil"
       OF           "of"
       OR           "|"
       PLUS         "+"
       PRIMITIVE    "primitive"
       RBRACE       "}"
       RBRACK       "]"
       RPAREN       ")"
       SEMI         ";"
       THEN         "then"
       TIMES        "*"
       TO           "to"
       TYPE         "type"
       VAR          "var"
       WHILE        "while"
       EOF 0        "end of file"

%type <ast::Exp*>             exp program
%type <ast::ChunkList*>       chunks classfields

%type <ast::TypeChunk*>       tychunk
%type <ast::TypeDec*>         tydec
%type <ast::NameTy*>          typeid VD1 FD1
%type <ast::Ty*>              ty 

%type <ast::Field*>           tyfield
%type <ast::fields_type*>     tyfields tyfields.1 

// DONE: Some code was added here.
%type <ast::fieldinits_type*> expARC1 expARC2 
%type <ast::exps_type*>       exps1 expFC1 expFC2 
%type <ast::SeqExp*>          exps
%type <ast::VarDec*>          forvardec vardec tyfieldch
%type <ast::Var*>             lvalue 
%type <ast::FieldInit*>       expARC3
%type <ast::VarChunk*>        varchunk tyfields.1ch tyfieldsch
%type <ast::FunctionChunk*>   funchunk 
%type <ast::FunctionDec*>     fundec 

%type <ast::MethodChunk*>     methchunk
%type <ast::MethodDec*>       methdec
%type <ast::ClassTy*>         classty

%destructor { delete($$); }   exp program chunks classfields tychunk tydec typeid VD1 FD1 ty tyfield tyfields tyfields.1 expARC1 expARC2 exps1 expFC1 expFC2 exps
%destructor { delete($$); }   forvardec vardec tyfieldch lvalue expARC3 varchunk tyfields.1ch tyfieldsch funchunk fundec methchunk methdec classty

%nonassoc ID
//%nonassoc LBRACK // COMMENTED commented because Tiger has too much power

%nonassoc THEN
%nonassoc ELSE
%right ":="
%left OR AND
%nonassoc EQ NE LT LE GT GE
%left PLUS MINUS
%left TIMES DIVIDE
%precedence CLASS
%right DO OF

// The power of the Tiger increased.

// Solving conflicts on:
// let type foo = bar
//     type baz = bat
// which can be understood as a list of two TypeChunk containing
// a unique TypeDec each, or a single TypeChunk containing two TypeDec.
// We want the latter.

%precedence CHUNKS
%precedence CLASSFIELD
%precedence TYPE
  // DONE: Some code was added here.
  %precedence METHOD
  %precedence FUNCTION
  %precedence PRIMITIVE
  %precedence VAR
  // The power of the Tiger increased.

%start program

%%
program:
  /* Parsing a source program.  */
  exp 
   { tp.ast_ = $1; }
| /* Parsing an imported file.  */
  chunks
   { tp.ast_ = $1; }
;

// DONE: Some code was added here.

exps1:
  exp { $$ = tp.td_.make_exps_type(); $$->emplace_back($1); }
| exps1 ";" exp { $$ = $1; $$->emplace_back($3); }
;

exps:
%empty { $$ = tp.td_.make_SeqExp(@$, tp.td_.make_exps_type()); }
| exps1 { $$ = tp.td_.make_SeqExp(@$, $1); }
;

expARC1:
%empty { $$ = tp.td_.make_fieldinits_type(); }
| expARC2 { $$ = $1; }
;

expARC2:
  expARC2 "," expARC3 { $$ = $1; $$->emplace_back($3); }
| expARC3 { $$ = tp.td_.make_fieldinits_type($1); }
;

expARC3:
  ID "=" exp { $$ = tp.td_.make_FieldInit(@$, $1, $3);}
;

expFC1:
%empty { $$ = tp.td_.make_exps_type(); }
| expFC2 { $$ = $1; }
;

expFC2:
  exp  { $$ = tp.td_.make_exps_type(); $$->emplace_back($1); }
| expFC2 "," exp { $$ = $1; $$->emplace_back($3); }
;

%token EXP "_exp";

exp:
  /* Literals. */
  EXP "(" INT ")" { $$ = metavar<ast::Exp>(tp, $3); }
  | "_cast" "(" exp "," ty ")" {$$ = tp.td_.make_CastExp(@$, $3, $5); }
  |  "nil" { $$ = tp.td_.make_NilExp(@$); } 
  | INT { $$ = tp.td_.make_IntExp(@$, $1); }
  | STRING { $$ = tp.td_.make_StringExp(@$, $1); }

  /* Array and record creations. */
  
  | ID "[" exp "]" "of" exp { $$ = tp.td_.make_ArrayExp(@$, tp.td_.make_NameTy(@1, $1), $3, $6); }
  | typeid "{" expARC1 "}" { $$ = tp.td_.make_RecordExp(@$, $1, $3); }

  /* Variables, field, elements of an array. */
  | lvalue { $$ = $1; }

  /* Function call. */
  | ID "(" expFC1 ")" { $$ = tp.td_.make_CallExp(@$, $1, $3); }

  /* Operations. */
  | "-" exp { $$ = tp.parse(Tweast() << "0 - " <<  $2 ); }
  | exp "+" exp {$$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::add, $3); }
  | exp "-" exp {$$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::sub, $3); }
  | exp "*" exp {$$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::mul, $3); }
  | exp "/" exp {$$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::div, $3); }
  | exp ">=" exp {$$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::ge, $3); }
  | exp "<=" exp {$$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::le, $3); }
  | exp "=" exp {$$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::eq, $3); }
  | exp "<>" exp {$$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::ne, $3); }
  | exp ">" exp {$$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::gt, $3); }
  | exp "<" exp {$$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::lt, $3); }
  | exp AND exp { $$ = tp.parse(Tweast() << "if " << $1 << " then " <<  $3 << " <> 0 else 0" ); }
  | exp OR exp { $$ = tp.parse(Tweast() << "if " <<  $1 << " then " << "1" << " else "  << " if " <<  $3  <<  " then " <<" 1 else 0" ); }
  | "(" exps ")" {$$ = $2; }

  /* Assignment. */
  | lvalue ":=" exp {$$ = tp.td_.make_AssignExp(@$, $1, $3); }

  /* Control structures. */
  | "if" exp "then" exp "else" exp {$$ = tp.td_.make_IfExp(@$, $2, $4, $6); }
  | "if" exp "then" exp {$$ = tp.td_.make_IfExp(@$, $2, $4); }
  | "while" exp "do" exp {$$ = tp.td_.make_WhileExp(@$, $2, $4); }
  | "for" forvardec "to" exp "do" exp {$$ = tp.td_.make_ForExp(@$, $2, $4, $6); }
  | "break" { $$ = tp.td_.make_BreakExp(@$);}
  | "let" chunks "in" exps "end" { $$ = tp.td_.make_LetExp(@$, $2, $4);}

  /* Object creation. */
  | "new" typeid { $$ = tp.td_.make_ObjectExp(@$, $2);}

  /* Method call. */
  | lvalue "." ID "(" expFC1 ")" { $$ = tp.td_.make_MethodCallExp(@$, $3, $5, $1);}

;
   
forvardec:
  ID ":=" exp { $$ = tp.td_.make_VarDec(@$, $1, nullptr /*??*/, $3); } //YAKA
;


%token LVALUE "_lvalue";

lvalue:
  LVALUE "(" INT ")" { $$ = metavar<ast::Var>(tp, $3); }
| ID { $$ = tp.td_.make_SimpleVar(@$, $1); }
|lvalue "." ID { $$ = tp.td_.make_FieldVar(@$, $1, $3); }
/* Array subscript. */
| lvalue "[" exp "]" { $$ = tp.td_.make_SubscriptVar(@$, $1, $3); }
;

// The power of the Tiger increased.


/*---------------.
| Declarations.  |
`---------------*/

// DONE: Some code was added here.
%token CHUNKS "_chunks";

chunks:
  /* Chunks are contiguous series of declarations of the same type
     (TypeDec, FunctionDec...) to which we allow certain specfic behavior like
     self referencing.
     They are held by a ChunkList, that can be empty, like in this case:
        let
        in
            ..
        end
     which is why we end the recursion with a %empty. */
  %empty         { $$ = tp.td_.make_ChunkList(@$); }
| CHUNKS "(" INT ")" chunks { $$ = $5; $$->splice_front(*(metavar<ast::ChunkList>(tp, $3))); }
| tychunk   chunks   { $$ = $2; $$->push_front($1); }
| funchunk chunks { $$ = $2; $$->push_front($1); }
| varchunk chunks { $$ = $2; $$->push_front($1); }
| "import" STRING chunks { $$ = $3; tp.parse_import($2, @2); }  //YAKA

;
// The power of the Tiger increased.

/*--------------------.
| Type Declarations.  |
`--------------------*/

// DONE: Some code was added here.

tychunk:
  /* Use `%prec CHUNKS' to do context-dependent precedence and resolve a
     shift-reduce conflict. */
  tydec %prec CHUNKS  { $$ = tp.td_.make_TypeChunk(@1); $$->push_front(*$1); }
| tydec tychunk { $$ = $2; $$->push_front(*$1); }
;

varchunk:
  vardec %prec CHUNKS  { $$ = tp.td_.make_VarChunk(@1); $$->push_front(*$1); }
;

VD1:
%empty { $$ = nullptr; }
| ":" typeid { $$ = $2; }
;

/* Variable declaration. */
vardec:
"var" ID VD1 ":=" exp { $$ = tp.td_.make_VarDec(@$, $2, $3, $5); }
;

tydec:
  "type" ID "=" ty  { $$ = tp.td_.make_TypeDec(@$, $2, $4); }
| "class" ID classty { $$ = tp.td_.make_TypeDec(@$, $2, $3); } 

;

classty:
  "{" classfields "}" { $$ = tp.td_.make_ClassTy(@$, tp.td_.make_NameTy(@$, "Object"), $2); }
| "extends" typeid "{" classfields "}" { $$ = tp.td_.make_ClassTy(@$, $2, $4); }
;

FD1:
%empty { $$ = nullptr; }
| ":" typeid { $$ = $2; }
;

funchunk:
  fundec %prec CHUNKS  { $$ = tp.td_.make_FunctionChunk(@1); $$->push_front(*$1); }
| fundec funchunk     { $$ = $2; $$->push_front(*$1); }
;

/* Function declaration. */
fundec:
  "function" ID "(" tyfieldsch ")" FD1 "=" exp { $$ = tp.td_.make_FunctionDec(@$, $2, $4, $6, $8); }
| "primitive" ID "(" tyfieldsch ")" FD1 { $$ = tp.td_.make_FunctionDec(@$, $2, $4, $6, nullptr); }
;


// The power of the Tiger increased.

ty:
  typeid               { $$ = $1; }
| "{" tyfields "}"     { $$ = tp.td_.make_RecordTy(@$, $2); }
| "array" "of" typeid  { $$ = tp.td_.make_ArrayTy(@$, $3); }
| "class" "{" classfields "}" { $$ = tp.td_.make_ClassTy(@$, tp.td_.make_NameTy(@$, "Object"), $3); }
| "class" "extends" typeid "{" classfields "}" { $$ = tp.td_.make_ClassTy(@$, $3, $5); }
;

tyfields:
  %empty               { $$ = tp.td_.make_fields_type(); }
| tyfields.1           { $$ = $1; }
;

tyfields.1:
  tyfields.1 "," tyfield { $$ = $1; $$->emplace_back($3); }
| tyfield                { $$ = tp.td_.make_fields_type($1); }
;

tyfield:
  ID ":" typeid     { $$ = tp.td_.make_Field(@$, $1, $3); }
;

tyfieldsch:
  %empty               { $$ = tp.td_.make_VarChunk(@$); }
| tyfields.1ch          { $$ = $1; }
;

tyfields.1ch:
  tyfields.1ch "," tyfieldch { $$ = $1; $$->emplace_back(*$3); }
| tyfieldch             { $$ = tp.td_.make_VarChunk(@$); $$->emplace_back(*$1); }
;

tyfieldch:
  ID ":" typeid     { $$ = tp.td_.make_VarDec(@$, $1, $3, nullptr); } // PAS SUR DU TOUT
;


/* Class fields. */
%token CLASSFIELD "_classfield";
classfields:
%empty { $$ = tp.td_.make_ChunkList(@$); }
| varchunk classfields  { $$ = $2; $$->push_front($1); }
| methchunk classfields { $$ = $2; $$->push_front($1); }
;

methdec:      
  "method" ID "(" tyfields ")" "=" exp { $$ = tp.td_.make_MethodDec(@$, $2, tp.td_.make_VarChunk(@4), nullptr, $7); }
| "method" ID "(" tyfields ")" ":" typeid "=" exp { $$ = tp.td_.make_MethodDec(@$, $2, tp.td_.make_VarChunk(@4), $7, $9); }
;

methchunk:
  methdec %prec CLASSFIELD { $$ = tp.td_.make_MethodChunk(@1); $$->push_front(*$1); }
| methdec methchunk { $$ = $2; $$->push_front(*$1); }
;


%token NAMETY "_namety";
typeid:
  ID                    { $$ = tp.td_.make_NameTy(@$, $1); }
  /* This is a metavariable. It it used internally by TWEASTs to retrieve
     already parsed nodes when given an input to parse. */
| NAMETY "(" INT ")"    { $$ = metavar<ast::NameTy>(tp, $3); }
;

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
  // DONE: Some code was added here.
  tp.error_ << misc::error::error_type::parse
            << "Parsing error" << l << ": " << m << "\n";
  // The power of the Tiger increased.
}
