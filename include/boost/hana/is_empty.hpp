/*!
@file
Defines `boost::hana::is_empty`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IS_EMPTY_HPP
#define BOOST_HANA_IS_EMPTY_HPP

#include <boost/hana/fwd/is_empty.hpp>

#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/core/dispatch.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs>
    constexpr auto is_empty_t::operator()(Xs&& xs) const {
        using It = typename hana::tag_of<Xs>::type;
        using IsEmpty = BOOST_HANA_DISPATCH_IF(is_empty_impl<It>,
            Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(Iterable<It>::value,
        "hana::is_empty(xs) requires 'xs' to be an Iterable");
    #endif

        return IsEmpty::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename It, bool condition>
    struct is_empty_impl<It, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_IS_EMPTY_HPP