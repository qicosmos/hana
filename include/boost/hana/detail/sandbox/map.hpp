/*!
@file
Defines `boost::hana::sandbox::map`.

@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_SANDBOX_MAP_HPP
#define BOOST_HANA_DETAIL_SANDBOX_MAP_HPP

#include <boost/hana/detail/constexpr.hpp>
#include <boost/hana/foldable.hpp>
#include <boost/hana/list.hpp>
#include <boost/hana/logical.hpp>
#include <boost/hana/maybe.hpp>


namespace boost { namespace hana {
    namespace sandbox {
        struct Map;

        BOOST_HANA_CONSTEXPR_LAMBDA auto pair = [](auto x, auto y) {
            return [=](auto f) { return f(x, y); };
        };

        BOOST_HANA_CONSTEXPR_LAMBDA auto second = [](auto p) {
            return p([](auto x, auto y) { return y; });
        };

        BOOST_HANA_CONSTEXPR_LAMBDA auto first = [](auto p) {
            return p([](auto x, auto y) { return x; });
        };

        namespace map_detail {
            BOOST_HANA_CONSTEXPR_LAMBDA auto replace = [](auto pred, auto new_val, auto xs) {
                auto go = [=](auto x) { return if_(pred(x), new_val, x); };
                return fmap(go, xs);
            };

            template <typename Hash, typename Pairs>
            struct bucket;

            BOOST_HANA_CONSTEXPR_LAMBDA auto make_bucket = [](auto h, auto pairs) {
                return bucket<decltype(h), decltype(pairs)>{h, pairs};
            };

            template <typename Hash, typename Pairs>
            struct bucket {
                Hash hash;
                Pairs pairs; // a list of (key, value) pairs

                template <typename H1, typename P1, typename H2, typename P2>
                friend constexpr auto operator==(bucket<H1, P1> b1, bucket<H2, P2> b2)
                { return b1.hash == b2.hash && b1.pairs == b2.pairs; }

                template <typename Key, typename Value>
                constexpr auto insert(Key k, Value v) const {
                    auto iskey = [=](auto pair) { return first(pair) == k; };
                    return eval_if(any(iskey, pairs),
                        [=](auto _) {
                            auto new_pairs = _(replace)(iskey, pair(k, v), pairs);
                            return make_bucket(hash, new_pairs);
                        },
                        [=](auto _) {
                            return make_bucket(hash, _(cons)(pair(k, v), pairs));
                        }
                    );
                }

                template <typename Key>
                constexpr auto lookup(Key key) const {
                    return fmap(
                        second,
                        find([=](auto p) { return first(p) == key; }, pairs)
                    );
                }
            };

            template <typename Buckets>
            struct map {
                Buckets buckets; // a list of buckets
                using hana_datatype = Map;
            };
        }

        //! @todo Create a `Hashable` type class.
        BOOST_HANA_CONSTEXPR_LAMBDA auto hash = [](auto x) {
            return x;
        };

        BOOST_HANA_CONSTEXPR_LAMBDA auto insert = [](auto key, auto value, auto map) {
            auto h = hash(key);
            // This should be O(1), but for now it'll do.
            auto bucket = find([=](auto b) { return b.hash == h; }, map.buckets);

            auto insert_in_bucket = [=](auto bucket) {
                auto new_buckets = replace(_ == bucket, bucket.insert(key, value), map.buckets);
                map_detail::map<decltype(new_buckets)> new_map{new_buckets};
                return new_map;
            };

            auto insert_new_bucket = [=] {
                auto new_bucket = map_detail::make_bucket(h, list()).insert(key, value);
                auto buckets = cons(new_bucket, map.buckets);
                map_detail::map<decltype(buckets)> new_map{buckets};
                return new_map;
            };

            // we should not need to evaluate insert_new_bucket.
            return maybe(insert_new_bucket(), insert_in_bucket, bucket);
        };

        BOOST_HANA_CONSTEXPR_LAMBDA auto map = [](auto ...pairs) {
            map_detail::map<decltype(list())> empty_map{list()};
            auto ins = [](auto map, auto pair) { return insert(first(pair), second(pair), map); };
            return foldl(ins, empty_map, list(pairs...));
        };

        BOOST_HANA_CONSTEXPR_LAMBDA auto lookup = [](auto key, auto map) {
            auto h = hash(key);
            auto bucket = find([=](auto b) { return b.hash == h; }, map.buckets);
            return maybe(nothing,
                [=](auto bucket) { return bucket.lookup(key); }
            , bucket);
        };
    } // end namespace sandbox

    template <>
    struct Foldable::instance<sandbox::Map> : Foldable::lazy_foldr_mcd {
        template <typename F, typename State, typename Map>
        static constexpr auto lazy_foldr_impl(F f, State s, Map m) {
            auto f_ = [=](auto bucket, auto s) {
                return lazy_foldr(f, s(), fmap(sandbox::second, bucket().pairs));
            };
            return lazy_foldr(f_, s, m.buckets);
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_SANDBOX_MAP_HPP