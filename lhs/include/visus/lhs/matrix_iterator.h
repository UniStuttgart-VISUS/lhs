// <copyright file="matrix_iterator.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_LHS_MATRIX_ITERATOR_H)
#define _LHS_MATRIX_ITERATOR_H
#pragma once

#include <cassert>
#include <cstdlib>
#include <iterator>
#include <vector>

#include "visus/lhs/matrix_layout.h"


LHS_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// An iterator for rows or columns of a matrix.
/// </summary>
/// <typeparam name="TValue">The type used to store a scalar.</typeparam>
/// <typeparam name="Layout">The memory layout used by the matrix</typeparam>
template<class TValue, matrix_layout Layout, matrix_layout Order>
class matrix_iterator final {

public:

private:

    std::size_t _consecutive;
    std::vector<value_type>& _elements;
    std::size_t _position;

};

LHS_DETAIL_NAMESPACE_BEGIN

#endif /* !defined(_LHS_MATRIX_ITERATOR_H) */
