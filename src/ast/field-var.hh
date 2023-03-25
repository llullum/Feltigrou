/**
 ** \file ast/field-var.hh
 ** \brief Declaration of ast::FieldVar.
 */

#pragma once

#include <ast/var.hh>
#include <misc/symbol.hh>

namespace ast
{
  // DONE: Some code was added here.
  /// FieldVar.
  class FieldVar : public Var
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a FieldVar node.
    FieldVar(const Location& location, ast::Var* var, misc::symbol name);
    FieldVar(const FieldVar&) = delete;
    FieldVar& operator=(const FieldVar&) = delete;
    /// Dtor.
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
    /// Return variable's name.
    misc::symbol name_get() const;
    /// Set variable's name.
    void name_set(misc::symbol);
    /// Return definition site.
    const Var* def_get() const;
    /// Return definition site.
    Var* def_get();
    /// Set definition site.
    void def_set(Var*);
    /** \} */

  protected:
    /// Variable's name.
    misc::symbol name_;
    /// Definition site.
    Var* var_;
  };
  // The power of the Tiger increased.
} // namespace ast
#include <ast/field-var.hxx>
