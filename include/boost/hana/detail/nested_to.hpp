/*!
@file
Defines `boost::hana::detail::nested_to`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_TO_HPP
#define BOOST_HANA_DETAIL_NESTED_TO_HPP

#include <boost/hana/detail/nested_to_fwd.hpp>

#include <boost/hana/functional/partial.hpp>


namespace boost { namespace hana { inline namespace v1 { namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename X>
    constexpr decltype(auto) nested_to_t<Algorithm>::operator()(X&& x) const
    { return hana::partial(Algorithm{}, static_cast<X&&>(x)); }
    //! @endcond
}}}} // end namespace boost::hana::v1::detail

#endif // !BOOST_HANA_DETAIL_NESTED_TO_HPP
