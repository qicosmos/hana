/*!
@file
Defines `boost::hana::Monad`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_HPP
#define BOOST_HANA_CONCEPT_MONAD_HPP

#include <boost/hana/fwd/concept/monad.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/flatten.hpp>


namespace boost { namespace hana { inline namespace v1 {
    template <typename M>
    struct Monad {
        using Tag = typename tag_of<M>::type;
        static constexpr bool value = !is_default<flatten_impl<Tag>>::value ||
                                      !is_default<chain_impl<Tag>>::value;
    };
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_CONCEPT_MONAD_HPP
