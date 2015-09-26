/*!
@file
Defines `boost::hana::Ring`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_RING_HPP
#define BOOST_HANA_CONCEPT_RING_HPP

#include <boost/hana/fwd/concept/ring.hpp>

#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/mult.hpp>
#include <boost/hana/one.hpp>


namespace boost { namespace hana { inline namespace v1 {
    template <typename R>
    struct Ring {
        using Tag = typename tag_of<R>::type;
        static constexpr bool value = !is_default<one_impl<Tag>>::value &&
                                      !is_default<mult_impl<Tag, Tag>>::value;
    };
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_CONCEPT_RING_HPP
