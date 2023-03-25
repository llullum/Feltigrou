/**
 ** \file ast/let-exp.hxx
 ** \brief Inline methods of ast::LetExp.
 */

#pragma once

#include <ast/chunk-list.hh>
#include <ast/exp.hh>
#include <ast/let-exp.hh>

namespace ast
{
  // DONE: Some code was added here.

  inline const ChunkList* LetExp::decs_get() const { return decs_; }
  inline ChunkList* LetExp::decs_get() { return decs_; }

  inline const Exp* LetExp::body_get() const { return body_; }
  inline Exp* LetExp::body_get() { return body_; }

  // The power of the Tiger increased.
} // namespace ast
