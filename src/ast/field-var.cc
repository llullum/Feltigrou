/**
 ** \file ast/field-var.cc
 ** \brief Implementation of ast::FieldVar.
 */

#include <ast/field-var.hh>
#include <ast/visitor.hh>

namespace ast
{

  FieldVar::FieldVar(const Location& location, Var* var, misc::symbol name)
    : Var(location)
    , name_(name)
    , var_(var)
  {}

  void FieldVar::accept(ConstVisitor& v) const { v(*this); }

  void FieldVar::accept(Visitor& v) { v(*this); }
} // namespace ast
