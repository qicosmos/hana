/*!
@file
Defines `boost::hana::Comonad`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_COMONAD_HPP
#define BOOST_HANA_CONCEPT_COMONAD_HPP

#include <boost/hana/fwd/concept/comonad.hpp>

#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/duplicate.hpp>
#include <boost/hana/extend.hpp>
#include <boost/hana/extract.hpp>


namespace boost { namespace hana { inline namespace v1 {
    template <typename W>
    struct Comonad {
        using Tag = typename tag_of<W>::type;
        static constexpr bool value = !is_default<extract_impl<Tag>>::value &&
                                      (!is_default<duplicate_impl<Tag>>::value ||
                                       !is_default<extend_impl<Tag>>::value);
    };
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_CONCEPT_COMONAD_HPP
