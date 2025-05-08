// <copyright file="matrix_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <CppUnitTest.h>

#include "visus/lhs/layout.h"
#include "visus/lhs/matrix.h"
#include "visus/lhs/submatrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace visus::lhs;


namespace test {

    TEST_CLASS(matrix_test) {

        TEST_METHOD(test_dimensions) {
            {
                matrix<float, matrix_layout::row_major> m(3, 4);
                Assert::AreEqual(static_cast<std::size_t>(3), m.rows(), L"rows", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(4), m.columns(), L"columns", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(12), m.size(), L"size", LINE_INFO());
                Assert::IsFalse(m.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(m.columns(), m.stride(), L"stride", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::row_major> m(4, 3);
                Assert::AreEqual(static_cast<std::size_t>(4), m.rows(), L"rows", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(3), m.columns(), L"columns", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(12), m.size(), L"size", LINE_INFO());
                Assert::IsFalse(m.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(m.columns(), m.stride(), L"stride", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> m(3, 4);
                Assert::AreEqual(static_cast<std::size_t>(3), m.rows(), L"rows", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(4), m.columns(), L"columns", LINE_INFO());
                Assert::AreEqual(static_cast<std::size_t>(12), m.size(), L"size", LINE_INFO());
                Assert::IsFalse(m.empty(), L"empty", LINE_INFO());
                Assert::AreEqual(m.rows(), m.stride(), L"stride", LINE_INFO());
            }
        }

        TEST_METHOD(test_index) {
            {
                matrix<float, matrix_layout::row_major> m(3, 3);
                Assert::AreEqual(std::size_t(0), m.index(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(1), m.index(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(2), m.index(0, 2), L"0, 1", LINE_INFO());

                Assert::AreEqual(std::size_t(3), m.index(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(4), m.index(1, 1), L"1, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(5), m.index(1, 2), L"1, 1", LINE_INFO());

                Assert::AreEqual(std::size_t(6), m.index(2, 0), L"2, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(7), m.index(2, 1), L"2, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(8), m.index(2, 2), L"2, 1", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> m(3, 3);
                Assert::AreEqual(std::size_t(0), m.index(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(1), m.index(1, 0), L"1, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(2), m.index(2, 0), L"2, 1", LINE_INFO());

                Assert::AreEqual(std::size_t(3), m.index(0, 1), L"1, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(4), m.index(1, 1), L"1, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(5), m.index(2, 1), L"2, 1", LINE_INFO());

                Assert::AreEqual(std::size_t(6), m.index(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(std::size_t(7), m.index(1, 2), L"1, 2", LINE_INFO());
                Assert::AreEqual(std::size_t(8), m.index(2, 2), L"2, 2", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::row_major> m(3, 4);
                Assert::AreEqual(std::size_t(0), m.index(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(1), m.index(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(4), m.index(1, 0), L"1, 0", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::row_major> m(4, 3);
                Assert::AreEqual(std::size_t(0), m.index(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(1), m.index(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(3), m.index(1, 0), L"1, 0", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> m(3, 4);
                Assert::AreEqual(std::size_t(0), m.index(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(std::size_t(3), m.index(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(std::size_t(1), m.index(1, 0), L"1, 0", LINE_INFO());
            }
        }

        TEST_METHOD(test_reverse_index) {
            {
                matrix<float, matrix_layout::row_major> m(3, 4);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(0), row, L"row 1", LINE_INFO());
                    Assert::AreEqual(std::size_t(1), col, L"column 1", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 4);
                    Assert::AreEqual(std::size_t(1), row, L"row 4", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 4", LINE_INFO());
                }
            }

            {
                matrix<float, matrix_layout::row_major> m(4, 3);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(0), row, L"row 1", LINE_INFO());
                    Assert::AreEqual(std::size_t(1), col, L"column 1", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 3);
                    Assert::AreEqual(std::size_t(1), row, L"row 3", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 3", LINE_INFO());
                }
            }

            {
                matrix<float, matrix_layout::column_major> m(3, 4);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(1), row, L"row 1", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 1", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 3);
                    Assert::AreEqual(std::size_t(0), row, L"row 3", LINE_INFO());
                    Assert::AreEqual(std::size_t(1), col, L"column 3", LINE_INFO());
                }
            }

            {
                matrix<float, matrix_layout::row_major> m(1, 3);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(1), col, L"column 1", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 2);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(2), col, L"column 2", LINE_INFO());
                }
            }

            {
                matrix<float, matrix_layout::column_major> m(1, 3);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(1), col, L"column 1", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 2);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(2), col, L"column 2", LINE_INFO());
                }
            }

            {
                matrix<float, matrix_layout::row_major> m(3, 1);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(1), row, L"row 1", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 2);
                    Assert::AreEqual(std::size_t(2), row, L"row 2", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }
            }

            {
                matrix<float, matrix_layout::column_major> m(3, 1);

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 0);
                    Assert::AreEqual(std::size_t(0), row, L"row 0", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 1);
                    Assert::AreEqual(std::size_t(1), row, L"row 1", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }

                {
                    std::size_t row = 0;
                    std::size_t col = 0;
                    m.index(row, col, 2);
                    Assert::AreEqual(std::size_t(2), row, L"row 2", LINE_INFO());
                    Assert::AreEqual(std::size_t(0), col, L"column 0", LINE_INFO());
                }
            }
        }

        TEST_METHOD(test_indexers_row_major) {
            matrix<float, matrix_layout::row_major> m(3, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(2.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(2.1f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(2.2f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(2.3f, m(2, 3), L"2, 3", LINE_INFO());

            Assert::AreEqual(int(matrix_layout::row_major), int(m.layout()), L"Matrix layout", LINE_INFO());

            Assert::AreEqual(0.0f, m[0], L"0", LINE_INFO());
            Assert::AreEqual(0.1f, m[1], L"1", LINE_INFO());
            Assert::AreEqual(0.2f, m[2], L"2", LINE_INFO());
            Assert::AreEqual(0.3f, m[3], L"3", LINE_INFO());

            Assert::AreEqual(1.0f, m[4], L"4", LINE_INFO());
            Assert::AreEqual(1.1f, m[5], L"5", LINE_INFO());
            Assert::AreEqual(1.2f, m[6], L"6", LINE_INFO());
            Assert::AreEqual(1.3f, m[7], L"7", LINE_INFO());

            Assert::AreEqual(2.0f, m[8], L"8", LINE_INFO());
            Assert::AreEqual(2.1f, m[9], L"9", LINE_INFO());
            Assert::AreEqual(2.2f, m[10], L"10", LINE_INFO());
            Assert::AreEqual(2.3f, m[11], L"11", LINE_INFO());
        }

        TEST_METHOD(test_indexers_colum_major) {
            matrix<float, matrix_layout::column_major> m(3, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            Assert::AreEqual(0.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.1f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.2f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.3f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(1.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.1f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(1.2f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(1.3f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(2.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(2.1f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(2.2f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(2.3f, m(2, 3), L"2, 3", LINE_INFO());

            Assert::AreEqual(int(matrix_layout::column_major), int(m.layout()), L"Matrix layout", LINE_INFO());

            Assert::AreEqual(0.0f, m[0], L"0", LINE_INFO());
            Assert::AreEqual(1.0f, m[1], L"1", LINE_INFO());
            Assert::AreEqual(2.0f, m[2], L"2", LINE_INFO());

            Assert::AreEqual(0.1f, m[3], L"3", LINE_INFO());
            Assert::AreEqual(1.1f, m[4], L"4", LINE_INFO());
            Assert::AreEqual(2.1f, m[5], L"5", LINE_INFO());

            Assert::AreEqual(0.2f, m[6], L"6", LINE_INFO());
            Assert::AreEqual(1.2f, m[7], L"7", LINE_INFO());
            Assert::AreEqual(2.2f, m[8], L"8", LINE_INFO());

            Assert::AreEqual(0.3f, m[9], L"9", LINE_INFO());
            Assert::AreEqual(1.3f, m[10], L"10", LINE_INFO());
            Assert::AreEqual(2.3f, m[11], L"11", LINE_INFO());
        }

        TEST_METHOD(test_fill) {
            matrix<float> m(3, 4);
            m.fill(42.0f);

            Assert::AreEqual(42.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(42.0f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(42.0f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(42.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(42.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(42.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(42.0f, m(2, 3), L"2, 3", LINE_INFO());

            m.fill([&m](const std::size_t r, const std::size_t c) {
                return static_cast<float>(m.index(r, c));
            });

            Assert::AreEqual(0.0f, m[0], L"0", LINE_INFO());
            Assert::AreEqual(1.0f, m[1], L"1", LINE_INFO());
            Assert::AreEqual(2.0f, m[2], L"2", LINE_INFO());
            Assert::AreEqual(3.0f, m[3], L"3", LINE_INFO());

            Assert::AreEqual(4.0f, m[4], L"4", LINE_INFO());
            Assert::AreEqual(5.0f, m[5], L"5", LINE_INFO());
            Assert::AreEqual(6.0f, m[6], L"6", LINE_INFO());
            Assert::AreEqual(7.0f, m[7], L"7", LINE_INFO());

            Assert::AreEqual(8.0f, m[8], L"8", LINE_INFO());
            Assert::AreEqual(9.0f, m[9], L"9", LINE_INFO());
            Assert::AreEqual(10.0f, m[10], L"10", LINE_INFO());
            Assert::AreEqual(11.0f, m[11], L"11", LINE_INFO());
        }

        TEST_METHOD(test_equality) {
            matrix<float> m1(3, 4);
            m1.fill(42.0f);

            matrix<float> m2(3, 4);
            Assert::IsFalse(m1 == m2, L"m1 == m2", LINE_INFO());

            m2 = m1;
            Assert::IsTrue(m1 == m2, L"m1 == m2", LINE_INFO());

            matrix<float> m3(4, 3);
            m3.fill(42.0f);
            Assert::IsFalse(m1 == m3, L"m1 == m3", LINE_INFO());
        }

        TEST_METHOD(test_row) {
            matrix<float> m(3, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            {
                matrix<float> r(1, 4);
                m.row(r, 0);
                Assert::AreEqual(0.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(0.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(0.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(0.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                matrix<float> r(1, 4);
                m.row(r, 1);
                Assert::AreEqual(1.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(1.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(1.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> r(1, 4);
                m.row(r, 0);
                Assert::AreEqual(0.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(0.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(0.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(0.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> r(1, 4);
                m.row(r, 1);
                Assert::AreEqual(1.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(1.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(1.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                auto r = m.row(0);
                Assert::AreEqual(0.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(0.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(0.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(0.3f, r(0, 3), L"0, 3", LINE_INFO());
            }

            {
                auto r = m.row(1);
                Assert::AreEqual(1.0f, r(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, r(0, 1), L"0, 1", LINE_INFO());
                Assert::AreEqual(1.2f, r(0, 2), L"0, 2", LINE_INFO());
                Assert::AreEqual(1.3f, r(0, 3), L"0, 3", LINE_INFO());
            }
        }

        TEST_METHOD(test_column) {
            matrix<float> m(3, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            {
                matrix<float> c(3, 1);
                m.column(c, 0);
                Assert::AreEqual(0.0f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.0f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.0f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                matrix<float> c(3, 1);
                m.column(c, 1);
                Assert::AreEqual(0.1f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.1f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> c(3, 1);
                m.column(c, 0);
                Assert::AreEqual(0.0f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.0f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.0f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> c(3, 1);
                m.column(c, 1);
                Assert::AreEqual(0.1f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.1f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                auto c = m.column(0);
                Assert::AreEqual(0.0f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.0f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.0f, c(2, 0), L"2, 2", LINE_INFO());
            }

            {
                auto c = m.column(1);
                Assert::AreEqual(0.1f, c(0, 0), L"0, 0", LINE_INFO());
                Assert::AreEqual(1.1f, c(1, 0), L"1, 0", LINE_INFO());
                Assert::AreEqual(2.1f, c(2, 0), L"2, 2", LINE_INFO());
            }
        }

        TEST_METHOD(test_diagonal) {
            auto m = matrix<float>::diagonal(4, 42.0f);
            Assert::AreEqual(42.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(42.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(3, 0), L"3, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(3, 1), L"3, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(3, 2), L"3, 2", LINE_INFO());
            Assert::AreEqual(42.0f, m(3, 3), L"3, 3", LINE_INFO());
        }

        TEST_METHOD(test_identity) {
            auto m = matrix<float>::identity(4);
            Assert::AreEqual(1.0f, m(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 2), L"0, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(0, 3), L"0, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(1.0f, m(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 2), L"1, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(1, 3), L"1, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(2, 0), L"2, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 1), L"2, 1", LINE_INFO());
            Assert::AreEqual(1.0f, m(2, 2), L"2, 2", LINE_INFO());
            Assert::AreEqual(0.0f, m(2, 3), L"2, 3", LINE_INFO());

            Assert::AreEqual(0.0f, m(3, 0), L"3, 0", LINE_INFO());
            Assert::AreEqual(0.0f, m(3, 1), L"3, 1", LINE_INFO());
            Assert::AreEqual(0.0f, m(3, 2), L"3, 2", LINE_INFO());
            Assert::AreEqual(1.0f, m(3, 3), L"3, 3", LINE_INFO());
        }

        TEST_METHOD(test_layout) {
            {
                typedef matrix<float, matrix_layout::row_major> type;
                type m;
                Assert::AreEqual(int(matrix_layout::row_major), int(m.layout()), L"get", LINE_INFO());
                Assert::AreEqual(int(matrix_layout::row_major), int(detail::layout_v<type>), L"traits", LINE_INFO());
            }
            {
                typedef matrix<float, matrix_layout::column_major> type;
                type m;
                Assert::AreEqual(int(matrix_layout::column_major), int(m.layout()), L"get", LINE_INFO());
                Assert::AreEqual(int(matrix_layout::column_major), int(detail::layout_v<type>), L"traits", LINE_INFO());
            }
            {
                typedef matrix<float, matrix_layout::row_major> base_type;
                typedef submatrix<base_type> type;
                base_type m(10, 10);
                type s(m, 0, 0, 5, 5);
                Assert::AreEqual(int(matrix_layout::row_major), int(s.layout()), L"get", LINE_INFO());
                Assert::AreEqual(int(matrix_layout::row_major), int(detail::layout_v<type>), L"traits", LINE_INFO());
            }
            {
                typedef matrix<float, matrix_layout::column_major> base_type;
                typedef submatrix<base_type> type;
                base_type m(10, 10);
                type s(m, 0, 0, 5, 5);
                Assert::AreEqual(int(matrix_layout::column_major), int(s.layout()), L"get", LINE_INFO());
                Assert::AreEqual(int(matrix_layout::column_major), int(detail::layout_v<type>), L"traits", LINE_INFO());
            }
        }

        TEST_METHOD(test_row_iterator) {
            {
                matrix<float, matrix_layout::row_major> m(3, 4);

                m(0, 0) = 0.0f;
                m(0, 1) = 0.1f;
                m(0, 2) = 0.2f;
                m(0, 3) = 0.3f;

                m(1, 0) = 1.0f;
                m(1, 1) = 1.1f;
                m(1, 2) = 1.2f;
                m(1, 3) = 1.3f;

                m(2, 0) = 2.0f;
                m(2, 1) = 2.1f;
                m(2, 2) = 2.2f;
                m(2, 3) = 2.3f;

                auto cnt = 0;
                for (auto it = m.row_begin(); it != m.row_end(); ++it, ++cnt) {
                    auto row = *it;
                    Assert::AreEqual(std::size_t(1), row.rows(), L"rows", LINE_INFO());
                    Assert::AreEqual(std::size_t(4), row.columns(), L"columns", LINE_INFO());
                    Assert::AreEqual(cnt + 0.0f, row[0], L"0", LINE_INFO());
                    Assert::AreEqual(cnt + 0.1f, row[1], L"1", LINE_INFO());
                    Assert::AreEqual(cnt + 0.2f, row[2], L"2", LINE_INFO());
                    Assert::AreEqual(cnt + 0.3f, row[3], L"2", LINE_INFO());
                }
                Assert::AreEqual(3, cnt, L"# of rows", LINE_INFO());
            }

            {
                const matrix<float, matrix_layout::row_major> m(3, 4);
                auto cnt = 0;
                for (auto it = m.row_begin(); it != m.row_end(); ++it, ++cnt);
                Assert::AreEqual(3, cnt, L"# of rows", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> m(3, 4);

                m(0, 0) = 0.0f;
                m(0, 1) = 0.1f;
                m(0, 2) = 0.2f;
                m(0, 3) = 0.3f;

                m(1, 0) = 1.0f;
                m(1, 1) = 1.1f;
                m(1, 2) = 1.2f;
                m(1, 3) = 1.3f;

                m(2, 0) = 2.0f;
                m(2, 1) = 2.1f;
                m(2, 2) = 2.2f;
                m(2, 3) = 2.3f;

                auto cnt = 0;
                for (auto it = m.row_begin(); it != m.row_end(); ++it, ++cnt) {
                    auto row = *it;
                    Assert::AreEqual(std::size_t(1), row.rows(), L"rows", LINE_INFO());
                    Assert::AreEqual(std::size_t(4), row.columns(), L"columns", LINE_INFO());
                    Assert::AreEqual(cnt + 0.0f, row[0], L"0", LINE_INFO());
                    Assert::AreEqual(cnt + 0.1f, row[1], L"1", LINE_INFO());
                    Assert::AreEqual(cnt + 0.2f, row[2], L"2", LINE_INFO());
                    Assert::AreEqual(cnt + 0.3f, row[3], L"2", LINE_INFO());
                }
                Assert::AreEqual(3, cnt, L"# of rows", LINE_INFO());
            }

            {
                const matrix<float, matrix_layout::column_major> m(3, 4);
                auto cnt = 0;
                for (auto it = m.row_begin(); it != m.row_end(); ++it, ++cnt);
                Assert::AreEqual(3, cnt, L"# of rows", LINE_INFO());
            }
        }

        TEST_METHOD(test_column_iterator) {
            {
                matrix<float, matrix_layout::row_major> m(3, 4);

                m(0, 0) = 0.0f;
                m(0, 1) = 0.1f;
                m(0, 2) = 0.2f;
                m(0, 3) = 0.3f;

                m(1, 0) = 1.0f;
                m(1, 1) = 1.1f;
                m(1, 2) = 1.2f;
                m(1, 3) = 1.3f;

                m(2, 0) = 2.0f;
                m(2, 1) = 2.1f;
                m(2, 2) = 2.2f;
                m(2, 3) = 2.3f;

                auto cnt = 0;
                for (auto it = m.column_begin(); it != m.column_end(); ++it, ++cnt) {
                    auto col = *it;
                    Assert::AreEqual(std::size_t(3), col.rows(), L"rows", LINE_INFO());
                    Assert::AreEqual(std::size_t(1), col.columns(), L"columns", LINE_INFO());
                    Assert::AreEqual(0.0f + 0.1f * cnt, col[0], L"0", LINE_INFO());
                    Assert::AreEqual(1.0f + 0.1f * cnt, col[1], L"1", LINE_INFO());
                    Assert::AreEqual(2.0f + 0.1f * cnt, col[2], L"2", LINE_INFO());
                }
                Assert::AreEqual(4, cnt, L"# of columns", LINE_INFO());
            }

            {
                const matrix<float, matrix_layout::row_major> m(3, 4);
                auto cnt = 0;
                for (auto it = m.column_begin(); it != m.column_end(); ++it, ++cnt);
                Assert::AreEqual(4, cnt, L"# of columns", LINE_INFO());
            }

            {
                matrix<float, matrix_layout::column_major> m(3, 4);

                m(0, 0) = 0.0f;
                m(0, 1) = 0.1f;
                m(0, 2) = 0.2f;
                m(0, 3) = 0.3f;

                m(1, 0) = 1.0f;
                m(1, 1) = 1.1f;
                m(1, 2) = 1.2f;
                m(1, 3) = 1.3f;

                m(2, 0) = 2.0f;
                m(2, 1) = 2.1f;
                m(2, 2) = 2.2f;
                m(2, 3) = 2.3f;

                auto cnt = 0;
                for (auto it = m.column_begin(); it != m.column_end(); ++it, ++cnt) {
                    auto col = *it;
                    Assert::AreEqual(std::size_t(3), col.rows(), L"rows", LINE_INFO());
                    Assert::AreEqual(std::size_t(1), col.columns(), L"columns", LINE_INFO());
                    Assert::AreEqual(0.0f + 0.1f * cnt, col[0], L"0", LINE_INFO());
                    Assert::AreEqual(1.0f + 0.1f * cnt, col[1], L"1", LINE_INFO());
                    Assert::AreEqual(2.0f + 0.1f * cnt, col[2], L"2", LINE_INFO());
                }
                Assert::AreEqual(4, cnt, L"# of columns", LINE_INFO());
            }

            {
                const matrix<float, matrix_layout::column_major> m(3, 4);
                auto cnt = 0;
                for (auto it = m.column_begin(); it != m.column_end(); ++it, ++cnt);
                Assert::AreEqual(4, cnt, L"# of columns", LINE_INFO());
            }
        }

        TEST_METHOD(test_submatrix) {
            matrix<float, matrix_layout::row_major> m(4, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            m(3, 0) = 3.0f;
            m(3, 1) = 3.1f;
            m(3, 2) = 3.2f;
            m(3, 3) = 3.3f;

            submatrix<decltype(m)> sm(m, 1, 1, 2, 3);

            Assert::AreEqual(std::size_t(2), sm.rows(), L"rows", LINE_INFO());
            Assert::AreEqual(std::size_t(3), sm.columns(), L"columns", LINE_INFO());
            Assert::AreEqual(std::size_t(6), sm.size(), L"size", LINE_INFO());

            Assert::AreEqual(1.1f, sm(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(1.2f, sm(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(1.3f, sm(0, 2), L"0, 2", LINE_INFO());

            Assert::AreEqual(2.1f, sm(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(2.2f, sm(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(2.3f, sm(1, 2), L"1, 2", LINE_INFO());

            sm(0, 0) = 42.0f;
            Assert::AreEqual(42.0f, sm(0, 0), L"modified 0, 0", LINE_INFO());
            Assert::AreEqual(42.0f, m(1, 1), L"affected 1, 1", LINE_INFO());
        }

        TEST_METHOD(test_submatrix_to_matrix) {
            matrix<float, matrix_layout::row_major> m(4, 4);

            m(0, 0) = 0.0f;
            m(0, 1) = 0.1f;
            m(0, 2) = 0.2f;
            m(0, 3) = 0.3f;

            m(1, 0) = 1.0f;
            m(1, 1) = 1.1f;
            m(1, 2) = 1.2f;
            m(1, 3) = 1.3f;

            m(2, 0) = 2.0f;
            m(2, 1) = 2.1f;
            m(2, 2) = 2.2f;
            m(2, 3) = 2.3f;

            m(3, 0) = 3.0f;
            m(3, 1) = 3.1f;
            m(3, 2) = 3.2f;
            m(3, 3) = 3.3f;

            submatrix<decltype(m)> sm(m, 1, 1, 2, 3);

            auto m2 = static_cast<decltype(m)>(sm);

            Assert::AreEqual(std::size_t(2), m2.rows(), L"rows", LINE_INFO());
            Assert::AreEqual(std::size_t(3), m2.columns(), L"columns", LINE_INFO());
            Assert::AreEqual(std::size_t(6), m2.size(), L"size", LINE_INFO());

            Assert::AreEqual(1.1f, m2(0, 0), L"0, 0", LINE_INFO());
            Assert::AreEqual(1.2f, m2(0, 1), L"0, 1", LINE_INFO());
            Assert::AreEqual(1.3f, m2(0, 2), L"0, 2", LINE_INFO());

            Assert::AreEqual(2.1f, m2(1, 0), L"1, 0", LINE_INFO());
            Assert::AreEqual(2.2f, m2(1, 1), L"1, 1", LINE_INFO());
            Assert::AreEqual(2.3f, m2(1, 2), L"1, 2", LINE_INFO());
        }
    };

}
