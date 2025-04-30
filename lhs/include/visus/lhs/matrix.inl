// <copyright file="matrix.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * LHS_DETAIL_NAMESPACE::matrix<TValue, Layout>::column
 */
template<class TValue, LHS_DETAIL_NAMESPACE::matrix_layout Layout>
template<LHS_DETAIL_NAMESPACE::matrix_layout L>
LHS_DETAIL_NAMESPACE::matrix<TValue, L>&
LHS_DETAIL_NAMESPACE::matrix<TValue, Layout>::column(
        _Inout_ matrix<TValue, L>& dst,
        _In_ const std::size_t column) const {
    assert(dst.columns() == 1);
    assert(dst.rows() == this->rows());
    assert(column < this->columns());


    if ((Layout == matrix_layout::column_major)
            && (L == matrix_layout::column_major)) {
        std::copy(this->_elements.begin() + index(0, column),
            this->_elements.begin() + index(0, column + 1),
            dst._elements.begin());
    } else {
        for (std::size_t r = 0; r < this->rows(); ++r) {
            dst._elements[r] = (*this)(r, column);
        }
    }

    return dst;
}

/*
 * LHS_DETAIL_NAMESPACE::matrix<TValue, Layout>::row
 */
template<class TValue, LHS_DETAIL_NAMESPACE::matrix_layout Layout>
template<LHS_DETAIL_NAMESPACE::matrix_layout L>
LHS_DETAIL_NAMESPACE::matrix<TValue, L>&
LHS_DETAIL_NAMESPACE::matrix<TValue, Layout>::row(
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
 * LHS_DETAIL_NAMESPACE::matrix<TValue, Layout>::operator ==
 */
template<class TValue, LHS_DETAIL_NAMESPACE::matrix_layout Layout>
bool LHS_DETAIL_NAMESPACE::matrix<TValue, Layout>::operator ==(
        _In_ const matrix& rhs) const noexcept {
    if (this->size() != rhs.size()) {
        return false;
    }

    if (this->_consecutive != rhs._consecutive) {
        return false;
    }

    return (std::memcmp(this->_elements.data(),
        rhs._elements.data(),
        this->_elements.size() * sizeof(value_type))
        == 0);
}
