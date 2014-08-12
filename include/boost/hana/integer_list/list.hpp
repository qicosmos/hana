/*!
@file
Defines the instance of `boost::hana::List` for `boost::hana::IntegerList`.

@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INTEGER_LIST_LIST_HPP
#define BOOST_HANA_INTEGER_LIST_LIST_HPP

#include <boost/hana/integer_list/integer_list.hpp>
#include <boost/hana/list/mcd.hpp>

// Mcd
#include <boost/hana/integer_list/monad.hpp>
#include <boost/hana/integer_list/foldable.hpp>
#include <boost/hana/integer_list/iterable.hpp>


namespace boost { namespace hana {
    //! @details
    //! An `Integral` can be prepended to an `IntegerList` by using `cons`;
    //! however the `cons`ed value has to be convertible to the type of the
    //! integers in the list. An empty `IntegerList` can be created with
    //! `nil<IntegerList>`; the type of the `Integral`s it contains will be
    //! set when an element is added to the list.
    template <>
    struct List::instance<IntegerList> : List::mcd<IntegerList> {
        template <typename X, typename T, T ...xs>
        static constexpr auto cons_impl(X x, ilist_detail::integer_list<T, xs...>) {
            return integer_list<T, static_cast<T>(x), xs...>;
        }

        template <typename X>
        static constexpr auto cons_impl(X x, ilist_detail::integer_list<void>) {
            return integer_list<decltype(x()), x()>;
        }

        static constexpr auto nil_impl() {
            return integer_list<void>;
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_INTEGER_LIST_LIST_HPP