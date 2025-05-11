// <copyright file="scale.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * LHS_DETAIL_NAMESPACE::scale
 */
template<class TValue>
std::enable_if_t<std::is_floating_point_v<TValue>, std::size_t>
LHS_DETAIL_NAMESPACE::scale(_In_ const TValue value,
        _In_ const std::size_t cnt) {
    static constexpr auto half = static_cast<TValue>(0.5);

    if ((value < 0.0f) || (value > 1.0f)) {
        throw std::invalid_argument("The sample value must be within [0, 1].");
    }

    if (cnt < 0) {
        throw std::invalid_argument("The list of parameter expressions must be "
            "greater than zero.");
    }

    const auto end = static_cast<TValue>(cnt - 1);
    const auto retval = static_cast<std::size_t>(end + half);
    assert(retval >= 0);
    assert(retval < cnt);
    return retval;
}


/*
 * LHS_DETAIL_NAMESPACE::scale
 */
template<class TIterator, LHS_NAMESPACE::matrix_layout Layout>
std::enable_if_t<LHS_DETAIL_NAMESPACE::is_range_v<
        typename std::iterator_traits<TIterator>::value_type>
    && std::is_floating_point_v<
        typename std::iterator_traits<TIterator>::value_type::value_type>,
    LHS_NAMESPACE::matrix<
        typename std::iterator_traits<TIterator>::value_type::value_type,
        Layout>&>
LHS_DETAIL_NAMESPACE::scale(_Inout_ matrix<typename
        std::iterator_traits<TIterator>::value_type::value_type, Layout>& lhs,
        _In_ const TIterator begin,
        _In_ const TIterator end) {
    assert(std::distance(begin, end) == lhs.columns());

    // Scale the samples to the ranges defined by the parameters like suggested
    // in https://stat.ethz.ch/pipermail/r-help/2007-January/124143.html.
    for (std::size_t r = 0, n = lhs.rows(); r < n; ++r) {
        std::size_t c = 0;

        for (auto it = begin; it != end; ++it, ++c) {
            lhs(r, c) = it->begin() + it->distance() * lhs(r, c);
        }
    }

    return lhs;
}


/*
 * LHS_DETAIL_NAMESPACE::scale
 */
template<class TIterator, LHS_NAMESPACE::matrix_layout Layout, class TElement>
std::enable_if_t< LHS_DETAIL_NAMESPACE::is_range_v<
        typename std::iterator_traits<TIterator>::value_type>
    && std::is_integral_v<
        typename std::iterator_traits<TIterator>::value_type::value_type>
    && std::is_floating_point_v<TElement>,
    LHS_NAMESPACE::matrix<
        typename std::iterator_traits<TIterator>::value_type::value_type,
        Layout>>
LHS_DETAIL_NAMESPACE::scale(_In_ const matrix<TElement, Layout>& lhs,
        _In_ const TIterator begin,
        _In_ const TIterator end) {
    typedef TElement float_type;
    typedef typename std::iterator_traits<TIterator>::value_type range_type;
    typedef typename range_type::value_type int_type;

    constexpr auto half = static_cast<float_type>(0.5);
    const auto n = lhs.rows();
    const auto k = std::distance(begin, end);
    assert(k == lhs.columns());

    matrix<int_type> retval(n, k);

    // Scale the cube to the the specified ranges.
    std::size_t c = 0;
    for (auto it = begin; it != end; ++it, ++c) {
        for (std::size_t r = 0; r < n; ++r) {
            assert(lhs(r, c) >= 0.0f);
            assert(lhs(r, c) <= 1.0f);
            auto value
                = static_cast<float_type>(it->begin())
                + static_cast<float_type>(it->distance()) * lhs(r, c);
            value += half;
            retval(r, c) = static_cast<int_type>(value);
        }
    }

    return retval;
}


/*
 * LHS_DETAIL_NAMESPACE::scale
 */
template<class TIterator, LHS_NAMESPACE::matrix_layout Layout, class TElement>
std::enable_if_t<std::is_integral_v<
        typename std::iterator_traits<TIterator>::value_type>
    && std::is_floating_point_v<TElement>,
    LHS_NAMESPACE::matrix<
        typename std::iterator_traits<TIterator>::value_type, Layout>>
LHS_DETAIL_NAMESPACE::scale(_In_ const matrix<TElement, Layout>& lhs,
        _In_ const TIterator begin,
        _In_ const TIterator end) {
    typedef TElement float_type;
    typedef typename std::iterator_traits<TIterator>::value_type int_type;

    constexpr auto half = static_cast<float_type>(0.5);
    const auto n = lhs.rows();
    const auto k = std::distance(begin, end);
    assert(k == lhs.columns());

    matrix<int_type> retval(n, k);

    std::size_t c = 0;
    for (auto it = begin; it != end; ++it, ++c) {
        const auto cnt = (*it != 0) ? (*it - 1) : *it;

        for (std::size_t r = 0; r < n; ++r) {
            assert(lhs(r, c) >= 0.0f);
            assert(lhs(r, c) <= 1.0f);
            auto value = static_cast<float_type>(cnt) * lhs(r, c);
            value += half;
            retval(r, c) = static_cast<int_type>(value);
        }
    }

    return retval;
}
