/*!
@file
Forward declares `boost::hana::replace_if`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPLACE_IF_HPP
#define BOOST_HANA_FWD_REPLACE_IF_HPP

#include <boost/hana/core/when.hpp>


namespace boost { namespace hana { inline namespace v1 {
    //! Replace all the elements of a structure satisfying a `predicate`
    //! with a fixed value.
    //! @relates Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor and `Bool` a Logical, the signature is
    //! \f$
    //!     \mathtt{replace_if} : F(T) \times (T \to Bool) \times T \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to replace elements of.
    //!
    //! @param predicate
    //! A function called as `predicate(x)` for element(s) `x` of the
    //! structure and returning a `Logical` representing whether `x`
    //! should be replaced by `value`.
    //!
    //! @param value
    //! A value by which every element `x` of the structure for which
    //! `predicate` returns a true-valued `Logical` is replaced.
    //!
    //!
    //! Example
    //! -------
    //! @include example/replace_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto replace_if = [](auto&& xs, auto&& predicate, auto&& value) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct replace_if_impl : replace_if_impl<Xs, when<true>> { };

    struct replace_if_t {
        template <typename Xs, typename Pred, typename Value>
        constexpr auto operator()(Xs&& xs, Pred&& pred, Value&& value) const;
    };

    constexpr replace_if_t replace_if{};
#endif
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_FWD_REPLACE_IF_HPP
