/**
 ** \file ast/object-exp.hh
 ** \brief Declaration of ast::ObjectExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ObjectExp.
  class ObjectExp : public Exp

  // DONE: Some code was added here.
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a ObjectExp node.
    ObjectExp(const Location& location,
           NameTy* type_name);
    ObjectExp(const ObjectExp&) = delete;
    ObjectExp& operator=(const ObjectExp&) = delete;
    /// Destroy a ObjectExp node.
    ~ObjectExp() override;
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
    /** \} */

  protected:
    /// Optional type of the declared variable.
    NameTy* type_name_;

    // The power of the Tiger increased.
  };
} // namespace ast
#include <ast/object-exp.hxx>
