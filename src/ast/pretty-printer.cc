/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <ast/pretty-printer.hh>
#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/separator.hh>
#include "op-exp.hh"

namespace ast
{
  // Anonymous namespace: these functions are private to this file.
  namespace
  {

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline std::ostream& operator<<(std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      return ostr;
    }
  } // namespace

  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}

  void PrettyPrinter::operator()(const SimpleVar& e) { ostr_ << e.name_get(); }

  void PrettyPrinter::operator()(const FieldVar& e)
  {
    // DONE: Some code was added here.

    if (e.def_get())
      {
        ostr_ << *e.def_get();
        ostr_ << '.' << e.name_get();
      }
    // The power of the Tiger increased.
  }

  /* Foo[10]. */
  void PrettyPrinter::operator()(const SubscriptVar& e)
  {
    ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
          << misc::decindent << ']';
  }

  void PrettyPrinter::operator()(const CastExp& e)
  {
    ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
  }

  // DONE: Some code was added here.

  void PrettyPrinter::operator()(const IntExp& e) { ostr_ << e.value_get(); }

  void PrettyPrinter::operator()(const StringExp& e)
  {
    ostr_ << '"' << misc::escape(e.string_get()) << '"';
  }

  void PrettyPrinter::operator()(const CallExp& e)
  {
    // DONE: Some code was added here.
    ostr_ << e.name_get() << '(' << misc::incindent
          << misc::separate(*(e.exps_get()), ", ") << misc::decindent << ')';
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const MethodCallExp& e)
  {
    // DONE: Some code was added here.
    if (e.var_get())
      {
        ostr_ << *e.var_get() << '.' << e.name_get();
      }

    /*if (e.method_get())
      {
        e.method_get()->accept(*this);
      }*/

    ostr_ << '(' << misc::incindent << misc::separate(*(e.exps_get()), ", ")
          << misc::decindent << ')';
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const RecordExp& e)
  {
    // DONE: Some code was added here.
    /*if (e.type_name_get())
      {
        e.type_name_get()->accept(*this);
      }*/

    ostr_ << e.type_name_get() << " {"
          << misc::separate(*(e.fields_get()), ", ") << "}";
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const ArrayExp& e)
  {
    // DONE: Some code was added here.
    /*if (e.type_name_get())
      {
        e.type_name_get()->accept(*this);
      }*/

    ostr_ << e.type_name_get() << "[" << e.size_get();

    /*if (e.size_get())
      {
        e.size_get()->accept(*this);
      }*/

    ostr_ << "] "
          << "of ";

    if (e.init_get())
      {
        e.init_get()->accept(*this);
      }
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const NilExp& e)
  {
    // DONE: Some code was added here.
    ostr_ << "nil";
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const SeqExp& e)
  {
    // DONE: Some code was added here. //check if null
    if (e.exps_get())
      {
        ostr_ << misc::separate(*(e.exps_get()),
                                std::make_pair(";", misc::iendl));
        // on verra mais c'est pas mal
        if (e.exps_get()->empty())
          ostr_ << misc::iendl << "()"; //<< misc::decindent;
        //else
        //  ostr_ << misc::decindent;
      }
    // ON SAIT PAS SI C'EST BON
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const AssignExp& e)
  {
    // DONE: Some code was added here.
    ostr_ << *e.var_get() << " := " << *e.exp_get();
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const IfExp& e)
  {
    // DONE: Some code was added here.
    ostr_ << "(if " << *(e.test_get()) << " then" << misc::incendl
          << *(e.thenclause_get());
    if (e.elseclause_get() == nullptr)
      {
        ostr_ << ")" << misc::decindent;
        return;
      }
    ostr_ << misc::decendl << "else" << misc::incendl << *e.elseclause_get()
          << ")" << misc::decindent;
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const WhileExp& e)
  {
    // DONE: Some code was added here.
    ostr_ << "while " << e.test_get() << " do" << misc::incendl;
    ostr_ << e.body_get();
    ostr_ << misc::decendl;
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const ForExp& e)
  {
    // DONE: Some code was added here.
    ostr_ << "for " << e.vardec_get();
    if (e.vardec_get().init_get())
      {
        ostr_ << " := " << *e.vardec_get().init_get();
      }
    ostr_ << " to " << e.hi_get() << " do" << misc::incendl << e.body_get()
          << misc::decindent;
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const BreakExp& e)
  {
    // DONE: Some code was added here.
    ostr_ << "break";
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const LetExp& e)
  {
    // DONE: Some code was added here.
    ostr_ << "let" << misc::incendl;
    if (e.decs_get())
      {
        ostr_ << *(e.decs_get());
      }
    ostr_ << misc::decendl << "in" << misc::incendl;
    if (e.body_get())
      {
        ostr_ << *(e.body_get());
      }
    ostr_ << misc::decendl << "end";
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const OpExp& e)
  {
    // DONE: Some code was added here.
    if (e.oper_get() == OpExp::Oper::add || e.oper_get() == OpExp::Oper::sub
        || e.oper_get() == OpExp::Oper::eq || e.oper_get() == OpExp::Oper::gt
        || e.oper_get() == OpExp::Oper::ge || e.oper_get() == OpExp::Oper::lt
        || e.oper_get() == OpExp::Oper::le)
      {
        ostr_ << "(" << e.left_get() << " " << str(e.oper_get()) << " "
              << e.right_get() << ")";
        return;
      }

    ostr_ << e.left_get() << " " << str(e.oper_get()) << " "
          << e.right_get(); //faire le fixme dnas le cc
    // The power of the Tiger increased.
  }

  /*void PrettyPrinter::operator()(const ChunkList& e)
  {
    // DONE: Some code was added here.
    ostr_ << e.chunks_get();
    // The power of the Tiger increased.
  }*/

  void PrettyPrinter::operator()(const TypeDec& e)
  {
    // DONE: Some code was added here.
    ostr_ << "type " << e.name_get() << " = " << misc::iendl << e.ty_get();
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const RecordTy& e)
  {
    // DONE: Some code was added here.
    ostr_ << misc::separate(*(e.fields_get()), "; ");
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const ArrayTy& e)
  {
    ostr_ << "array of " << e.base_type_get() << misc::iendl;
  }

  void PrettyPrinter::operator()(const Field& e)
  {
    ostr_ << e.name_get() << " : " << e.type_name_get();
  }

  void PrettyPrinter::operator()(const NameTy& e)
  {
    // DONE: Some code was added here.
    ostr_ << e.name_get();
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const ClassTy& e)
  {
    // DONE: Some code was added here.
    ostr_ << "class ";

    /*if (e.super_get())
    {
      ostr_ << e.super_get().name_get() << " ";
    }*/

    ostr_ << "extends " << e.super_get() << misc::iendl;
    ostr_ << "{" << misc::incendl << e.chunks_get() << misc::decendl << "}"
          << misc::iendl;
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const VarDec& e)
  {
    // DONE: Some code was added here.
    if (!e.type_name_get())
      ostr_ << "var ";

    ostr_ << e.name_get();

    if (e.type_name_get())
      {
        ostr_ << " : ";
        e.type_name_get()->accept(*this);
      }

    if (e.init_get())
      {
        ostr_ << " := " << *e.init_get() << misc::iendl;
      }
    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const MethodDec& e)
  {
    // DONE: Some code was added here.
    ostr_ << "method " << e.name_get() << '('
          << misc::separate(e.formals_get(), ", ") << ")";

    if (e.result_get())
      {
        ostr_ << " : " << *e.result_get();
      }

    ostr_ << " =" << misc::incendl;

    if (e.body_get())
      {
        ostr_ << *e.body_get();
      }

    ostr_ << misc::decindent;

    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const FunctionDec& e)
  {
    // DONE: Some code was added here.
    if (e.body_get() == nullptr)
      {
        ostr_ << "primitive " << e.name_get() << '(';
        ostr_ << misc::separate(e.formals_get(), ", ");
        ostr_ << ')';
        if (e.result_get())
          {
            ostr_ << " : ";
            e.result_get()->accept(*this);
          }
        ostr_ << misc::iendl;
      }
    else
      {
        ostr_ << "function " << e.name_get() << '(';
        ostr_ << misc::separate(e.formals_get(), ", ");
        ostr_ << ")";
        if (e.result_get())
          {
            ostr_ << " : ";
            e.result_get()->accept(*this);
          }
        ostr_ << " =" << misc::incendl << "(" << misc::incendl
              << *(e.body_get()) << misc::decendl << ")" << misc::decindent;
      }
    //ostr_ << misc::iendl;

    // The power of the Tiger increased.
  }

  void PrettyPrinter::operator()(const ObjectExp& e)
  {
    if (e.type_name_get())
      ostr_ << "new " << *e.type_name_get();
  }

} // namespace ast
