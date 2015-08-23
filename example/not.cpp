/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/assert.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/not.hpp>
namespace hana = boost::hana;


BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::true_) == hana::false_);
static_assert(hana::not_(false) == true, "");

int main() { }