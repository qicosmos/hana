/*!
@file
Defines `boost::hana::detail::fast_and`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_FAST_AND_HPP
#define BOOST_HANA_DETAIL_FAST_AND_HPP

#include <type_traits>


namespace boost { namespace hana { inline namespace v1 { namespace detail {
    template <bool ...b>
    struct fast_and
        : std::is_same<fast_and<b...>, fast_and<(b, true)...>>
    { };
}}}} // end namespace boost::hana::v1::detail

#endif // !BOOST_HANA_DETAIL_FAST_AND_HPP
