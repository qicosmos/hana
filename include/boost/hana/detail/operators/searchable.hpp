/*!
@file
Defines operators for Searchables.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP

#include <boost/hana/fwd/at_key.hpp>


namespace boost { namespace hana { inline namespace v1 { namespace detail {
    template <typename Derived>
    struct searchable_operators {
        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) & {
            return hana::at_key(static_cast<Derived&>(*this),
                                static_cast<Key&&>(key));
        }

        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) && {
            return hana::at_key(static_cast<Derived&&>(*this),
                                static_cast<Key&&>(key));
        }

        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) const& {
            return hana::at_key(static_cast<Derived const&>(*this),
                                static_cast<Key&&>(key));
        }
    };
}}}} // end namespace boost::hana::v1::detail

#endif // !BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP
