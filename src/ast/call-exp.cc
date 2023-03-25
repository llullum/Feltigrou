/**
 ** \file ast/call-exp.cc
 ** \brief Implementation of ast::CallExp.
 */

#include <ast/call-exp.hh>
#include <ast/visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{

  CallExp::CallExp(const Location& location, misc::symbol name, exps_type* exps)
    : Exp(location)
    , name_(name)
    , exps_(exps)
  {}

  CallExp::~CallExp()
  {
    if (exps_)
      {
        for (auto exp : *exps_)
          {
            delete exp;
          }
        delete exps_;
      }
  }

  void CallExp::accept(ConstVisitor& v) const { v(*this); }

  void CallExp::accept(Visitor& v) { v(*this); }
} // namespace ast
