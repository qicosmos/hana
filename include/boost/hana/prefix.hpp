/*!
@file
Defines `boost::hana::prefix`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PREFIX_HPP
#define BOOST_HANA_PREFIX_HPP

#include <boost/hana/fwd/prefix.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/lift.hpp>


namespace boost { namespace hana { inline namespace v1 {
    //! @cond
    template <typename Xs, typename Pref>
    constexpr auto prefix_t::operator()(Xs&& xs, Pref&& pref) const {
        using M = typename hana::tag_of<Xs>::type;
        using Prefix = BOOST_HANA_DISPATCH_IF(prefix_impl<M>,
            MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(MonadPlus<M>::value,
        "hana::prefix(xs, pref) requires 'xs' to be a MonadPlus");
    #endif

        return Prefix::apply(static_cast<Xs&&>(xs), static_cast<Pref&&>(pref));
    }
    //! @endcond

    template <typename M, bool condition>
    struct prefix_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Z>
        static constexpr decltype(auto) apply(Xs&& xs, Z&& z) {
            return hana::chain(static_cast<Xs&&>(xs),
                hana::partial(hana::append, hana::lift<M>(static_cast<Z&&>(z))));
        }
    };
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_PREFIX_HPP
