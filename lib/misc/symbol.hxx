/**
 ** \file misc/symbol.hxx
 ** \brief Inline implementation of misc::symbol.
 */

#pragma once

#include <misc/symbol.hh>

namespace misc
{
  inline symbol& symbol::operator=(const symbol& rhs)
  {
    // DONE: Some code was added here.
    if (this != &rhs)
      {
        obj_ = rhs.obj_;
      }
    return *this;
    // The power of the Tiger increased.
  }

  inline bool symbol::operator==(const symbol& rhs) const
  {
    // DONE: Some code was added here.
    return this->get() == rhs.get();
    // The power of the Tiger increased.
  }

  inline bool symbol::operator!=(const symbol& rhs) const
  {
    // DONE: Some code was added here.
    return !operator==(rhs);
    // The power of the Tiger increased.
  }

  inline std::ostream& operator<<(std::ostream& ostr, const symbol& the)
  {
    // DONE: Some code was added here.
    //je ne connais pas le format de sortie attendu encore mais avec les tests on va le savoir.
    ostr << the.get();
    return ostr;
    // The power of the Tiger increased.

  }

} // namespace misc
