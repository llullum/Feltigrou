/**
 ** \file ast/string-exp.hh
 ** \brief Declaration of ast::StringExp.
 */

#pragma once

#include <string>
#include <ast/exp.hh>

namespace ast
{
  /// StringExp.
  class StringExp : public Exp
  {
  // DONE: Some code was added here.

  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an StringExp node.
    StringExp(const Location& location, std::string string);
    StringExp(const StringExp&) = delete;
    StringExp& operator=(const StringExp&) = delete;
    /// Destroy an StringExp node.
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
    /// Return stored string string.
    std::string string_get() const;
    /** \} */

  protected:
    /// Stored string string.
    std::string string_;
  };

  // The power of the Tiger increased.
} // namespace ast
#include <ast/string-exp.hxx>
