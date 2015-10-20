/*!
@file
Defines `boost::hana::Comparable`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_COMPARABLE_HPP
#define BOOST_HANA_CONCEPT_COMPARABLE_HPP

#include <boost/hana/fwd/concept/comparable.hpp>

#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/equal.hpp>


namespace boost { namespace hana { inline namespace v1 {
    template <typename T>
    struct Comparable {
        using Tag = typename tag_of<T>::type;
        static constexpr bool value = !is_default<equal_impl<Tag, Tag>>::value;
    };
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_CONCEPT_COMPARABLE_HPP
