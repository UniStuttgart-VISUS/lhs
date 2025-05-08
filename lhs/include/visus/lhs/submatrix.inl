// <copyright file="submatrix.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * LHS_NAMESPACE::submatrix<TMatrix>::move
 */
template<class TMatrix>
LHS_NAMESPACE::submatrix<TMatrix>::submatrix(
        _In_ TMatrix &matrix,
        _In_ const std::size_t row,
        _In_ const std::size_t column,
        _In_ const std::size_t rows,
        _In_ const std::size_t columns)
        : _columns(columns), _matrix(matrix), _rows(rows) {
    if (row + rows > this->_matrix.rows()) {
        throw std::range_error("The row range exceeds the number of rows of "
            "the underlying matrix.");
    }
    if (column + columns > this->_matrix.columns()) {
        throw std::range_error("The column range exceeds the number of columns "
            "of the underlying matrix.");
    }

    this->_offset = this->_matrix.index(row, column);
}


/*
 * LHS_NAMESPACE::submatrix<TMatrix>::operator ==
 */
template<class TMatrix>
bool LHS_NAMESPACE::submatrix<TMatrix>::operator ==(
        _In_ const submatrix& rhs) const noexcept {
    return (this->_columns == rhs._columns)
        && (std::addressof(this->_matrix) == std::addressof(rhs._matrix))
        && (this->_offset == rhs._offset)
        && (this->_rows == rhs._rows);
}


/*
 * LHS_NAMESPACE::submatrix<TMatrix>::operator TMatrix
 */
template<class TMatrix>
LHS_NAMESPACE::submatrix<TMatrix>::operator TMatrix(void) const {
    TMatrix retval(this->rows(), this->columns());
    retval.fill([this](const std::size_t r, const std::size_t c) {
        return (*this)(r, c);
    });
    return retval;
}


/*
 * LHS_NAMESPACE::submatrix<TMatrix>::index
 */
template<class TMatrix>
std::size_t LHS_NAMESPACE::submatrix<TMatrix>::index(
        _In_ const std::size_t row,
        _In_ const std::size_t column) const noexcept {
    assert(row < this->_rows);
    assert(column < this->_columns);
    const auto index = (detail::layout_v<TMatrix> == matrix_layout::row_major)
        ? (row * this->_matrix.stride() + column)
        : (column * this->_matrix.stride() + row);
    return this->_offset + index;

}


/*
 * LHS_NAMESPACE::submatrix<TMatrix>::index
 */
template<class TMatrix>
std::size_t LHS_NAMESPACE::submatrix<TMatrix>::index(
        _In_ const std::size_t index) const noexcept {
    assert(index < this->size());
    if (this->layout() == matrix_layout::row_major) {
        return this->index(index / this->_columns, index % this->_columns);
    } else {
        return this->index(index % this->_rows, index / this->_rows);
    }
}
