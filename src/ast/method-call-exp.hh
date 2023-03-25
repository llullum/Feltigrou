/**
 ** \file ast/method-call-exp.hh
 ** \brief Declaration of ast::MethodCallExp.
 */

#pragma once

#include <ast/call-exp.hh>
#include <ast/method-dec.hh>
#include <ast/var.hh>

namespace ast
{
  /** \class ast::MethodCallExp
   ** \brief Method call.
   **
   ** A method call is \em not a function call in the strict sense
   ** of object-oriented programming.  Inheritance is used as a
   ** factoring tool here.
   */

  class MethodCallExp : public CallExp
  {
  public:
    MethodCallExp(const Location& location,
                  misc::symbol name,
                  exps_type* exps,
                  Var* var);
    MethodCallExp(const MethodCallExp&) = delete;
    MethodCallExp& operator=(const MethodCallExp&) = delete;

    //Destructor
    ~MethodCallExp() override;

    //for visitor
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    //accessors
    const Var* var_get() const;
    Var* var_get();
    void var_set(Var* var);
    
  protected:
    Var* var_;

  };
} // namespace ast
#include <ast/method-call-exp.hxx>
