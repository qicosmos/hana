/*!
@file
Defines `boost::hana::ordering`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ORDERING_HPP
#define BOOST_HANA_ORDERING_HPP

#include <boost/hana/fwd/ordering.hpp>

#include <boost/hana/less.hpp>

#include <type_traits>


namespace boost { namespace hana { inline namespace v1 {
    namespace detail {
        template <typename F>
        struct less_by {
            F f;

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const&
            { return hana::less(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) &
            { return hana::less(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }
        };
    }

    //! @cond
    template <typename F>
    constexpr auto ordering_t::operator()(F&& f) const {
        return detail::less_by<typename std::decay<F>::type>{static_cast<F&&>(f)};
    }
    //! @endcond
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_ORDERING_HPP
