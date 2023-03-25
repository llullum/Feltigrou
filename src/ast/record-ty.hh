/**
 ** \file ast/record-ty.hh
 ** \brief Declaration of ast::RecordTy.
 */

#pragma once

#include <ast/field.hh>
#include <ast/ty.hh>

namespace ast
{
  /// RecordTy.
  class RecordTy : public Ty
  // DONE: Some code was added here.
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a ObjectExp node.
    RecordTy(const Location& location,
           fields_type* fields);
    RecordTy(const RecordTy&) = delete;
    RecordTy& operator=(const RecordTy&) = delete;
    /// Destroy a ObjectExp node.
    ~RecordTy() override;
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
    const fields_type* fields_get() const;
    /// Return optional type of the declared variable.
    fields_type* fields_get();
    /** \} */

  protected:
    fields_type* fields_;

    // The power of the Tiger increased.
  };
} // namespace ast
#include <ast/record-ty.hxx>
