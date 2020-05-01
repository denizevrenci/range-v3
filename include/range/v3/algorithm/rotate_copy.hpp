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
#ifndef RANGES_V3_ALGORITHM_ROTATE_COPY_HPP
#define RANGES_V3_ALGORITHM_ROTATE_COPY_HPP

#include <functional>

#include <range/v3/range_fwd.hpp>

#include <range/v3/algorithm/copy.hpp>
#include <range/v3/algorithm/result_types.hpp>
#include <range/v3/functional/identity.hpp>
#include <range/v3/iterator/concepts.hpp>
#include <range/v3/iterator/traits.hpp>
#include <range/v3/range/access.hpp>
#include <range/v3/range/concepts.hpp>
#include <range/v3/range/dangling.hpp>
#include <range/v3/range/traits.hpp>
#include <range/v3/utility/static_const.hpp>

#include <range/v3/detail/disable_warnings.hpp>

namespace ranges
{
    /// \addtogroup group-algorithms
    /// @{
    template<typename I, typename O>
    using rotate_copy_result = detail::in_out_result<I, O>;

    RANGES_FUNC_BEGIN(rotate_copy)

        /// \brief function template \c rotate_copy
        CPP_template(typename I, typename S, typename O, typename P = identity)( //
            requires forward_iterator<I> && sentinel_for<S, I>  && //
            weakly_incrementable<O> && indirectly_copyable<I, O>) //
        auto RANGES_FUNC(rotate_copy)(I first, I middle, S last, O out) //
            -> rotate_copy_result<I, O>
        {
            auto res = ranges::copy(middle, std::move(last), std::move(out));
            return {std::move(res.in),
                    ranges::copy(std::move(first), middle, std::move(res.out)).out};
        }

        /// \overload
        CPP_template(typename Rng, typename O, typename P = identity)( //
            requires range<Rng> && weakly_incrementable<O>  && //
            indirectly_copyable<iterator_t<Rng>, O>) //
        auto RANGES_FUNC(rotate_copy)(Rng && rng, iterator_t<Rng> middle, O out) //
            -> rotate_copy_result<safe_iterator_t<Rng>, O>
        {
            return (*this)(begin(rng), std::move(middle), end(rng), std::move(out));
        }

    RANGES_FUNC_END(rotate_copy)

    namespace cpp20
    {
        using ranges::rotate_copy;
        using ranges::rotate_copy_result;
    } // namespace cpp20
    /// @}
} // namespace ranges

#include <range/v3/detail/reenable_warnings.hpp>

#endif
