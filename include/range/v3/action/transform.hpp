/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2013-present
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_ACTION_TRANSFORM_HPP
#define RANGES_V3_ACTION_TRANSFORM_HPP

#include <range/v3/range_fwd.hpp>

#include <range/v3/action/action.hpp>
#include <range/v3/algorithm/transform.hpp>
#include <range/v3/functional/bind_back.hpp>
#include <range/v3/functional/identity.hpp>
#include <range/v3/iterator/concepts.hpp>
#include <range/v3/iterator/traits.hpp>
#include <range/v3/utility/static_const.hpp>

#include <range/v3/detail/disable_warnings.hpp>

namespace ranges
{
    /// \addtogroup group-actions
    /// @{
    namespace actions
    {
        struct transform_fn
        {
            template<typename F, typename P = identity>
            constexpr auto CPP_fun(operator())(F fun, P proj = P{})(const //
                                                                    requires (!range<F>))
            {
                return make_action_closure(
                    bind_back(transform_fn{}, std::move(fun), std::move(proj)));
            }

            CPP_template(typename Rng, typename F, typename P = identity)( //
                requires input_range<Rng> && copy_constructible<F> &&
                    writable<iterator_t<Rng>,
                             indirect_result_t<F &, projected<iterator_t<Rng>, P>>>) //
            auto operator()(Rng && rng, F fun, P proj = P{}) const -> Rng
            {
                ranges::transform(rng, begin(rng), std::move(fun), std::move(proj));
                return static_cast<Rng &&>(rng);
            }
        };

        /// \relates actions::transform_fn
        RANGES_INLINE_VARIABLE(transform_fn, transform)
    } // namespace actions
    /// @}
} // namespace ranges

#include <range/v3/detail/reenable_warnings.hpp>

#endif
