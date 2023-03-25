/**
 ** \file ast/array-exp.hh
 ** \brief Declaration of ast::ArrayExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ArrayExp.
  class ArrayExp : public Exp
  {
    // DONE: Some code was added here.

  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a ArrayExp node.
    ArrayExp(const Location& location,
           NameTy* type_name,
           Exp* size_,
           Exp* init);
    ArrayExp(const ArrayExp&) = delete;
    ArrayExp& operator=(const ArrayExp&) = delete;
    /// Destroy a ArrayExp node.
    ~ArrayExp() override;
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
    /// Return optional type of the declared variable.
    const NameTy* type_name_get() const;
    /// Return optional type of the declared variable.
    NameTy* type_name_get();
    const Exp* size_get() const;
    Exp* size_get();

    const Exp* init_get() const;
    Exp* init_get();
    /** \} */

  protected:
    /// Optional type of the declared variable.
    NameTy* type_name_;
    Exp* size_;
    Exp* init_;
  };

  // The power of the Tiger increased.
  
} // namespace ast
#include <ast/array-exp.hxx>
