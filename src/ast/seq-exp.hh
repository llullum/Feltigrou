/**
 ** \file ast/seq-exp.hh
 ** \brief Declaration of ast::SeqExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{
  /// SeqExp.
  class SeqExp : public Exp
  {
  public:
    /// Type of the list of expressions.
    SeqExp(const Location& location, exps_type* exps);
    SeqExp& operator=(const SeqExp&) = delete;
    ~SeqExp() override;

    //for visitor
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    //accessor
    exps_type* exps_get() const;

  protected:
    exps_type* exps_;
  };
} // namespace ast
#include <ast/seq-exp.hxx>
