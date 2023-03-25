/**
 ** \file ast/if-exp.hxx
 ** \brief Inline methods of ast::IfExp.
 */

#pragma once

#include <ast/if-exp.hh>

namespace ast
{
  // DONE: Some code was added here.

  inline const Exp* IfExp::test_get() const { return test_; }
  inline Exp* IfExp::test_get() { return test_; }

  inline const Exp* IfExp::thenclause_get() const { return thenclause_; }
  inline Exp* IfExp::thenclause_get() { return thenclause_; }

  inline const Exp* IfExp::elseclause_get() const { return elseclause_; }
  inline Exp* IfExp::elseclause_get() { return elseclause_; }

  // The power of the Tiger increased.

} // namespace ast
