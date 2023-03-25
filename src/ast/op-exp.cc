/**
 ** \file ast/op-exp.cc
 ** \brief Implementation of ast::OpExp.
 */

#include "op-exp.hh"
#include <ast/op-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  OpExp::OpExp(const Location& location,
               Exp* left,
               OpExp::Oper oper,
               Exp* right)
    : Exp(location)
    , left_(left)
    , oper_(oper)
    , right_(right)
  {}

  OpExp::~OpExp()
  {
    delete left_;
    delete right_;
  }

  void OpExp::accept(ConstVisitor& v) const { v(*this); }

  void OpExp::accept(Visitor& v) { v(*this); }
} // namespace ast

std::string str(ast::OpExp::Oper oper)
{
  std::string res = "";

  switch (oper)
    {
    case ast::OpExp::Oper::add:
      res.append("+");
      return res;
    case ast::OpExp::Oper::sub:
      res.append("-");
      return res;
    case ast::OpExp::Oper::mul:
      res.append("*");
      return res;
    case ast::OpExp::Oper::div:
      res.append("/");
      return res;
    case ast::OpExp::Oper::eq:
      res.append("=");
      return res;
    case ast::OpExp::Oper::ne:
      res.append("<>");
      return res;
    case ast::OpExp::Oper::lt:
      res.append("<");
      return res;
    case ast::OpExp::Oper::le:
      res.append("<=");
      return res;
    case ast::OpExp::Oper::gt:
      res.append(">");
      return res;
    case ast::OpExp::Oper::ge:
      res.append(">=");
      return res;
    }
  return res;
}
