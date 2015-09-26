/*!
@file
Defines `boost::hana::first`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FIRST_HPP
#define BOOST_HANA_FIRST_HPP

#include <boost/hana/fwd/first.hpp>

#include <boost/hana/concept/product.hpp>
#include <boost/hana/core/dispatch.hpp>


namespace boost { namespace hana { inline namespace v1 {
    //! @cond
    template <typename Pair>
    constexpr decltype(auto) first_t::operator()(Pair&& pair) const {
        using P = typename hana::tag_of<Pair>::type;
        using First = BOOST_HANA_DISPATCH_IF(first_impl<P>,
            Product<P>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(Product<P>::value,
        "hana::first(pair) requires 'pair' to be a Product");
    #endif

        return First::apply(static_cast<Pair&&>(pair));
    }
    //! @endcond

    template <typename P, bool condition>
    struct first_impl<P, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_FIRST_HPP
