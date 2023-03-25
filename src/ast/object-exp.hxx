/**
 ** \file ast/object-exp.hxx
 ** \brief Inline methods of ast::ObjectExp.
 */

#pragma once

#include <ast/object-exp.hh>

namespace ast
{
  // DONE: Some code was added here.
    inline const NameTy* ObjectExp::type_name_get() const { return type_name_; }
    inline NameTy* ObjectExp::type_name_get() { return type_name_; }


    // The power of the Tiger increased.

} // namespace ast
