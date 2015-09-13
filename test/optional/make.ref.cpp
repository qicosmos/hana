/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/assert.hpp>
#include <boost/hana/optional.hpp>

#include <functional>
namespace hana = boost::hana;


int main() {
    {
        int i = 0;
        auto ref = hana::just(std::ref(i));

        int& i_ref = *ref;
        BOOST_HANA_RUNTIME_CHECK(&i_ref == &i);

        i_ref = 3;
        BOOST_HANA_RUNTIME_CHECK(i == 3);
    }

    {
        int const i = 4;
        auto ref = hana::just(std::cref(i));

        int const& i_ref = *ref;
        BOOST_HANA_RUNTIME_CHECK(&i_ref == &i);
        BOOST_HANA_RUNTIME_CHECK(i == 4);
    }
}
