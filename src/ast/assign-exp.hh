/**
 ** \file ast/assign-exp.hh
 ** \brief Declaration of ast::AssignExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

namespace ast
{
  /// AssignExp.
  class AssignExp : public Exp
  {
  public:
    AssignExp(const Location& location, Var* var, Exp* exp);
    AssignExp(const AssignExp&) = delete;
    AssignExp& operator=(const AssignExp&) = delete;

    //Destructor
    ~AssignExp() override;

    //for visitor
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    //accessors
    const Var* var_get() const;
    Var* var_get();
    void var_set(Var* var);

    const Exp* exp_get() const;
    Exp* exp_get();
    void exp_set(Exp* exp);

  protected:
    Var* var_;
    Exp* exp_;
  };
} // namespace ast
#include <ast/assign-exp.hxx>
