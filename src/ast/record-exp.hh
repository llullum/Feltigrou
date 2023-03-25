/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// RecordExp.
  class RecordExp : public Exp
  {
    // DONE: Some code was added here.

  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a RecordExp node.
    RecordExp(const Location& location,
           NameTy* type_name,
           fieldinits_type* fields);
    RecordExp(const RecordExp&) = delete;
    RecordExp& operator=(const RecordExp&) = delete;
    /// Destroy a RecordExp node.
    ~RecordExp() override;
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
    const fieldinits_type* fields_get() const;
    fieldinits_type* fields_get();

    /** \} */

  protected:
    /// Optional type of the declared variable.
    NameTy* type_name_;
    fieldinits_type* fields_;
  };

  // The power of the Tiger increased.
  
} // namespace ast
#include <ast/record-exp.hxx>
