// <copyright file="matrix.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * matrix<TValue, Layout>::diagonal
 */
template<class TValue, LHS_NAMESPACE::matrix_layout Layout>
constexpr LHS_NAMESPACE::matrix<TValue, Layout>
LHS_NAMESPACE::matrix<TValue, Layout>::diagonal(
        _In_ const std::size_t size,
        _In_ const value_type value) {
    matrix retval(size, size, static_cast<value_type>(0));

    for (std::size_t i = 0; i < size; ++i) {
        retval(i, i) = value;
    }

    return retval;
}


/*
 * LHS_NAMESPACE::matrix<TValue, Layout>::column
 */
template<class TValue, LHS_NAMESPACE::matrix_layout Layout>
template<LHS_NAMESPACE::matrix_layout L>
LHS_NAMESPACE::matrix<TValue, L>&
LHS_NAMESPACE::matrix<TValue, Layout>::column(
        _Inout_ matrix<TValue, L>& dst,
        _In_ const std::size_t column) const {
    assert(dst.columns() == 1);
    assert(dst.rows() == this->rows());
    assert(column < this->columns());


    if ((Layout == matrix_layout::column_major)
            && (L == matrix_layout::column_major)) {
        std::copy(this->_elements.begin() + this->index(0, column),
            this->_elements.begin() + this->index(0, column + 1),
            dst._elements.begin());
    } else {
        for (std::size_t r = 0; r < this->rows(); ++r) {
            dst._elements[r] = (*this)(r, column);
        }
    }

    return dst;
}


/*
 * LHS_NAMESPACE::matrix<TValue, Layout>::fill
 */
template<class TValue, LHS_NAMESPACE::matrix_layout Layout>
template<class TGenerator>
void LHS_NAMESPACE::matrix<TValue, Layout>::fill(
        _In_ const TGenerator& generator) {
    for (std::size_t r = 0, R = this->rows(); r < R; ++r) {
        for (std::size_t c = 0, C = this->columns(); c < C; ++c) {
            this->_elements[this->index(r, c)] = generator(r, c);
        }
    }
}


/*
 * LHS_NAMESPACE::matrix<TValue, Layout>::index
 */
template<class TValue, LHS_NAMESPACE::matrix_layout Layout>
bool LHS_NAMESPACE::matrix<TValue, Layout>::index(
        _Out_ std::size_t& row,
        _Out_ std::size_t& column,
        _In_ const std::size_t index) const noexcept {
    const auto cols = this->columns();
    const auto rows = this->rows();

    if (this->layout() == matrix_layout::row_major) {
        row = index / cols;
        column = index % cols;
    } else {
        column = index / rows;
        row = index % rows;
    }

    return ((row < rows) && (column < cols));
}


/*
 * LHS_NAMESPACE::matrix<TValue, Layout>::row
 */
template<class TValue, LHS_NAMESPACE::matrix_layout Layout>
template<LHS_NAMESPACE::matrix_layout L>
LHS_NAMESPACE::matrix<TValue, L>&
LHS_NAMESPACE::matrix<TValue, Layout>::row(
        _Inout_ matrix<TValue, L>& dst,
        _In_ const std::size_t row) const {
    assert(dst.rows() == 1);
    assert(dst.columns() == this->columns());
    assert(row < this->rows());

    if ((Layout == matrix_layout::row_major)
            && (L == matrix_layout::row_major)) {
        std::copy(this->_elements.begin() + index(row, 0),
            this->_elements.begin() + index(row + 1, 0),
            dst._elements.begin());
    } else {
        for (std::size_t c = 0; c < this->columns(); ++c) {
            dst._elements[c] = (*this)(row, c);
        }
    }

    return dst;
}


/*
 * LHS_NAMESPACE::matrix<TValue, Layout>::operator ==
 */
template<class TValue, LHS_NAMESPACE::matrix_layout Layout>
bool LHS_NAMESPACE::matrix<TValue, Layout>::operator ==(
        _In_ const matrix& rhs) const noexcept {
    if (this->size() != rhs.size()) {
        return false;
    }

    if (this->_stride != rhs._stride) {
        return false;
    }

    return (std::memcmp(this->_elements.data(),
        rhs._elements.data(),
        this->_elements.size() * sizeof(value_type))
        == 0);
}
