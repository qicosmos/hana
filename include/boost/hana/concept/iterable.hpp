/*!
@file
Defines `boost::hana::Iterable`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_ITERABLE_HPP
#define BOOST_HANA_CONCEPT_ITERABLE_HPP

#include <boost/hana/fwd/concept/iterable.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/is_empty.hpp>
#include <boost/hana/tail.hpp>


namespace boost { namespace hana { inline namespace v1 {
    template <typename It>
    struct Iterable {
        using Tag = typename tag_of<It>::type;
        static constexpr bool value = !is_default<at_impl<Tag>>::value &&
                                      !is_default<tail_impl<Tag>>::value &&
                                      !is_default<is_empty_impl<Tag>>::value;
    };
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_CONCEPT_ITERABLE_HPP
