/**
 ** \file ast/object-visitor.hxx
 ** \brief Implementation for ast/object-visitor.hh.
 */

#pragma once

#include <ast/all.hh>
#include <ast/object-visitor.hh>
#include <misc/contract.hh>

namespace ast
{
  template <template <typename> class Const>
  GenObjectVisitor<Const>::GenObjectVisitor()
    : GenVisitor<Const>()
  {}

  template <template <typename> class Const>
  GenObjectVisitor<Const>::~GenObjectVisitor()
  {}

  /*-------------------------------.
  | Object-related visit methods.  |
  `-------------------------------*/

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<ClassTy>& e)
  {
    e.super_get().accept(*this);
    for (const auto& dec : e.chunks_get())
      dec->accept(*this);
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<MethodChunk>& e)
  {
    //e.result_get().accept(*this);
    for (const auto& dec : e.decs_get())
      dec->accept(*this);
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<MethodDec>& e)
  {
    e.result_get()->accept(*this);
    e.body_get()->accept(*this);
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<MethodCallExp>& e)
  {
    e.var_get()->accept(*this);
    for (const auto arg : *e.exps_get())
      arg->accept(*this);
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<ObjectExp>& e)
  {
    e.type_name_get()->accept(*this);
  }

} // namespace ast