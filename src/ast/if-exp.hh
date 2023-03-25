/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{
  /// IfExp.
  class IfExp : public Exp
  {
    // DONE: Some code was added here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a IfExp node.
    IfExp(const Location& location,
          Exp* test,
          Exp* thenclause,
          Exp* elseclause = nullptr);
    IfExp(const IfExp&) = delete;
    IfExp& operator=(const IfExp&) = delete;
    /// Destroy a IfExp node.
    ~IfExp() override;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return condition in the if.
    const Exp* test_get() const;
    /// Return condition in the if.
    Exp* test_get();

    /// Return instructions executed in the if body.
    const Exp* thenclause_get() const;
    /// Return instructions executed in the if body.
    Exp* thenclause_get();

    /// Return instructions executed in the else body.
    const Exp* elseclause_get() const;
    /// Return instructions executed in the else body.
    Exp* elseclause_get();
    /** \} */

  protected:
    /// Condition of the if
    Exp* test_;
    /// Instructions executed in the if body.
    Exp* thenclause_;
    /// else body of the if
    Exp* elseclause_ = nullptr;
  };
  // The power of the Tiger increased.

} // namespace ast
#include <ast/if-exp.hxx>
