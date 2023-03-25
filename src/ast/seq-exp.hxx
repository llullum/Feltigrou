/**
 ** \file ast/seq-exp.hxx
 ** \brief Inline methods of ast::SeqExp.
 */

#pragma once

#include <ast/seq-exp.hh>

namespace ast
{
  inline exps_type* SeqExp::exps_get() const { return exps_; }
} // namespace ast
