/*!
@file
Defines `boost::hana::lockstep`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_LOCKSTEP_HPP
#define BOOST_HANA_FUNCTIONAL_LOCKSTEP_HPP

#include <boost/hana/basic_tuple.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


namespace boost { namespace hana { inline namespace v1 {
    //! @ingroup group-functional
    //! Invoke a function with the result of invoking other functions on its
    //! arguments, in lockstep.
    //!
    //! Specifically, `lockstep(f)(g1, ..., gN)` is a function such that
    //! @code
    //!     lockstep(f)(g1, ..., gN)(x1, ..., xN) == f(g1(x1), ..., gN(xN))
    //! @endcode
    //!
    //! Since each `g` is invoked on its corresponding argument in lockstep,
    //! the number of arguments must match the number of `g`s.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/lockstep.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto lockstep = [](auto&& f, auto&& ...g) {
        return [perfect-capture](auto&& ...x) -> decltype(auto) {
            return forwarded(f)(forwarded(g)(forwarded(x))...);
        };
    };
#else
    template <typename Indices, typename F, typename ...G>
    struct lockstep_t;

    template <typename F>
    struct pre_lockstep_t;

    struct make_pre_lockstep_t {
        struct secret { };
        template <typename F>
        constexpr pre_lockstep_t<typename std::decay<F>::type> operator()(F&& f) const {
            return {static_cast<F&&>(f)};
        }
    };

    template <std::size_t ...n, typename F, typename ...G>
    struct lockstep_t<std::index_sequence<n...>, F, G...> {
        template <typename ...T>
        constexpr lockstep_t(make_pre_lockstep_t::secret, T&& ...t)
            : storage_{static_cast<T&&>(t)...}
        { }

        basic_tuple<F, G...> storage_;

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const& {
            return hana::get_impl<0>(storage_)(
                hana::get_impl<n+1>(storage_)(static_cast<X&&>(x))...
            );
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) & {
            return hana::get_impl<0>(storage_)(
                hana::get_impl<n+1>(storage_)(static_cast<X&&>(x))...
            );
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) && {
            return static_cast<F&&>(hana::get_impl<0>(storage_))(
                static_cast<G&&>(hana::get_impl<n+1>(storage_))(static_cast<X&&>(x))...
            );
        }
    };

    template <typename F>
    struct pre_lockstep_t {
        F f;

        template <typename ...G>
        constexpr lockstep_t<std::make_index_sequence<sizeof...(G)>, F,
                             typename std::decay<G>::type...>
        operator()(G&& ...g) const& {
            return {make_pre_lockstep_t::secret{}, this->f, static_cast<G&&>(g)...};
        }

        template <typename ...G>
        constexpr lockstep_t<std::make_index_sequence<sizeof...(G)>, F,
                             typename std::decay<G>::type...>
        operator()(G&& ...g) && {
            return {make_pre_lockstep_t::secret{}, static_cast<F&&>(this->f),
                                                   static_cast<G&&>(g)...};
        }
    };

    constexpr make_pre_lockstep_t lockstep{};
#endif
}}} // end namespace boost::hana::v1

#endif // !BOOST_HANA_FUNCTIONAL_LOCKSTEP_HPP
