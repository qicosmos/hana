/*!
@file
Defines `boost::hana::all`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ALL_HPP
#define BOOST_HANA_ALL_HPP

#include <boost/hana/fwd/all.hpp>

#include <boost/hana/all_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>


namespace boost { namespace hana { inline namespace v1 {
    //! @cond
    template <typename Xs>
    constexpr auto all_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using All = BOOST_HANA_DISPATCH_IF(all_impl<S>,
            Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(Searchable<S>::value,
        "hana::all(xs) requires 'xs' to be a Searchable");
    #endif

        return All::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct all_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::all_of(static_cast<Xs&&>(xs), hana::id); }
    };
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_ALL_HPP
