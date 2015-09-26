/*!
@file
Forward declares `boost::hana::less`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LESS_HPP
#define BOOST_HANA_FWD_LESS_HPP

#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


namespace boost { namespace hana { inline namespace v1 {
    //! Returns a `Logical` representing whether `x` is less than `y`.
    //! @relates Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{less} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/less.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto less = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct less_impl : less_impl<T, U, when<true>> { };

    struct less_t : detail::nested_than<less_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    constexpr less_t less{};
#endif
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_FWD_LESS_HPP
