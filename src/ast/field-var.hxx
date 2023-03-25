/**
 ** \file ast/field-var.hxx
 ** \brief Inline methods of ast::FieldVar.
 */

#pragma once

#include <ast/field-var.hh>

namespace ast
{

  inline misc::symbol FieldVar::name_get() const { return name_; }
  inline void FieldVar::name_set(misc::symbol name) { name_ = name; }

  inline const Var* FieldVar::def_get() const { return var_; }
  inline Var* FieldVar::def_get() { return var_; }
  inline void FieldVar::def_set(Var* def) { var_ = def; }
} // namespace ast
