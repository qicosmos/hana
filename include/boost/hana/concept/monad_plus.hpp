/*!
@file
Defines `boost::hana::MonadPlus`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_PLUS_HPP
#define BOOST_HANA_CONCEPT_MONAD_PLUS_HPP

#include <boost/hana/fwd/concept/monad_plus.hpp>

#include <boost/hana/concat.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/empty.hpp>


namespace boost { namespace hana { inline namespace v1 {
    template <typename M>
    struct MonadPlus {
        using Tag = typename tag_of<M>::type;
        static constexpr bool value = !is_default<concat_impl<Tag>>::value &&
                                      !is_default<empty_impl<Tag>>::value;
    };
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_CONCEPT_MONAD_PLUS_HPP
