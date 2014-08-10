/*
@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/ext/boost/fusion.hpp>

#include <boost/hana/detail/assert.hpp>
#include <boost/hana/detail/cnumber/constant.hpp>
#include <boost/hana/detail/constexpr.hpp>
#include <boost/hana/maybe.hpp>

#include "helper.hpp"
using namespace boost::hana;


BOOST_HANA_CONSTEXPR_LAMBDA auto is_even = [](auto x) {
    return x % 2 == 0;
};

int main() {
    with_nonassociative_forward_sequences([=](auto container) {
        // all
        {
            BOOST_HANA_RUNTIME_ASSERT(all(container(), is_even));
            BOOST_HANA_RUNTIME_ASSERT(!all(container(1), is_even));
            BOOST_HANA_RUNTIME_ASSERT( all(container(2), is_even));
            BOOST_HANA_RUNTIME_ASSERT( all(container(2, 4), is_even));
            BOOST_HANA_RUNTIME_ASSERT(!all(container(1, 2), is_even));
            BOOST_HANA_RUNTIME_ASSERT(!all(container(1, 3), is_even));
            BOOST_HANA_RUNTIME_ASSERT(!all(container(1, 3, 4), is_even));
        }

        // any
        {
            BOOST_HANA_RUNTIME_ASSERT(!any(container(), is_even));
            BOOST_HANA_RUNTIME_ASSERT( !any(container(1), is_even));
            BOOST_HANA_RUNTIME_ASSERT(  any(container(2), is_even));
            BOOST_HANA_RUNTIME_ASSERT(  any(container(1, 2), is_even));
            BOOST_HANA_RUNTIME_ASSERT( !any(container(1, 3), is_even));
            BOOST_HANA_RUNTIME_ASSERT(  any(container(1, 3, 4), is_even));
        }

        // none
        {
            BOOST_HANA_RUNTIME_ASSERT(none(container(), is_even));
            BOOST_HANA_RUNTIME_ASSERT( none(container(1), is_even));
            BOOST_HANA_RUNTIME_ASSERT(!none(container(2), is_even));
            BOOST_HANA_RUNTIME_ASSERT(!none(container(1, 2), is_even));
            BOOST_HANA_RUNTIME_ASSERT( none(container(1, 3), is_even));
            BOOST_HANA_RUNTIME_ASSERT(!none(container(1, 3, 4), is_even));
        }

        // find
        {
            BOOST_HANA_CONSTEXPR_LAMBDA auto is = [](auto x) {
                return [=](auto y) { return equal(x, y); };
            };
            constexpr auto x = detail::cnumber<int, 0>;
            constexpr auto y = detail::cnumber<int, 1>;
            constexpr auto z = detail::cnumber<int, 2>;
            BOOST_HANA_CONSTANT_ASSERT(find(container(), is(z)) == nothing);

            BOOST_HANA_CONSTANT_ASSERT(find(container(x), is(x)) == just(x));
            BOOST_HANA_CONSTANT_ASSERT(find(container(x), is(z)) == nothing);

            BOOST_HANA_CONSTANT_ASSERT(find(container(x, y), is(x)) == just(x));
            BOOST_HANA_CONSTANT_ASSERT(find(container(x, y), is(y)) == just(y));
            BOOST_HANA_CONSTANT_ASSERT(find(container(x, y), is(z)) == nothing);
        }
    });
}