/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/assert.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/not_equal.hpp>
#include <boost/hana/string.hpp>
namespace hana = boost::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(
        BOOST_HANA_STRING("abcdef") == BOOST_HANA_STRING("abcdef")
    );

    BOOST_HANA_CONSTANT_CHECK(
        BOOST_HANA_STRING("abcdef") != BOOST_HANA_STRING("abef")
    );
}
