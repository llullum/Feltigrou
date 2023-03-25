/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <ast/chunk-list.hh>
#include <ast/exp.hh>
#include <misc/contract.hh>

namespace ast
{
  /// LetExp.
  class LetExp : public Exp
  {
    // DONE: Some code was added here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a IfExp node.
    LetExp(const Location& location, ChunkList* decs, Exp* body);
    LetExp(const LetExp&) = delete;
    LetExp& operator=(const LetExp&) = delete;
    /// Destroy a IfExp node.
    ~LetExp() override;
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

    /// Return instructions executed in the if body.
    const ChunkList* decs_get() const;
    /// Return instructions executed in the if body.
    ChunkList* decs_get();

    /// Return instructions executed in the else body.
    const Exp* body_get() const;
    /// Return instructions executed in the else body.
    Exp* body_get();
    /** \} */

  protected:
    ChunkList* decs_;
    Exp* body_;
  };
  // The power of the Tiger increased.
} // namespace ast
#include <ast/let-exp.hxx>
